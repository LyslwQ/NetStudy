#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//线程函数参数类型，以结构体传入，便于后期扩展
struct func_argvs
{
  int    m_thread_id;
};
typedef struct func_argvs func_argvs_t;

void   handle_error(const char* str, int exitNum);
void   load_data(const char* dataFile);
void*  thread_func(void *argv);

int    g_sumNum = 0;          //数据个数总数
float  *g_arr   = NULL;       //存储数据的数组
int    g_threadNum = 0;       //线程个数
pthread_t  *threadArr = NULL; //用于存储线程id
double     *g_tmp   = NULL;       
pthread_mutex_t g_mutex_mainToWorker;
pthread_mutex_t g_mutex_workerToMain;
pthread_cond_t  g_cond_mainToWorker;
pthread_cond_t  g_cond_workerToMain;
int     g_sentry_mainToWorker = 0;
int     g_sentry_workerToMain = 0;


/*
 * input: 数据文件，线程个数
 */ 
int main(int argc, char* argv[])
{ 
  time_t t = time(NULL);
  if(argc < 3)
      handle_error("Usage: dataFile  threadNum", 1);
  
  load_data(argv[1]);
  //创建工作线程 
  g_threadNum = atoi(argv[2]);
  if(g_sumNum < g_threadNum)
      g_threadNum = g_sumNum;
  g_tmp = (double*)malloc(sizeof(double)*g_threadNum);
  pthread_t *threadArr = (pthread_t*)malloc( sizeof(pthread_t) * g_threadNum );
  func_argvs_t *argvs  = (func_argvs_t*)malloc( sizeof(func_argvs_t) * g_threadNum );
  int i = 0;
  for(i = 0; i < g_threadNum; ++i){
      argvs[i].m_thread_id = i;
      pthread_create(&threadArr[i], NULL, thread_func,(void*)&argvs[i]);
  }
   
  //通知并等待工作线程完成第一步骤
  pthread_mutex_lock(&g_mutex_mainToWorker);
  g_sentry_mainToWorker = 1;
  g_sentry_workerToMain = g_threadNum;
  pthread_mutex_init(&g_mutex_workerToMain, NULL);
  pthread_cond_init(&g_cond_workerToMain, NULL);
  pthread_mutex_unlock(&g_mutex_mainToWorker);
  pthread_cond_broadcast(&g_cond_mainToWorker);

  pthread_mutex_lock(&g_mutex_workerToMain);
  while(g_sentry_workerToMain != 0)
      pthread_cond_wait(&g_cond_workerToMain, &g_mutex_workerToMain); //调用wait时会自动解锁，返回时又会加锁
  pthread_mutex_unlock(&g_mutex_workerToMain);

  for(i = 1; i < g_threadNum; ++i)
      g_tmp[i] = g_tmp[i-1] + g_tmp[i];

  //通知并等待工作线程完成第二步骤
  pthread_mutex_lock(&g_mutex_mainToWorker);
  g_sentry_mainToWorker = 0;
  pthread_mutex_unlock(&g_mutex_mainToWorker);
  pthread_cond_broadcast(&g_cond_mainToWorker);

  for(i = 0; i < g_threadNum; ++i){
      pthread_join(threadArr[i], NULL);
  }
  
  printf("process over, the work time is %d\n", time(NULL) - t);
  printf("the result as follow...\n");
  /*for(i = 0; i < g_sumNum; ++i)
      printf("g_arr[%d] = %f\n", i, g_arr[i]);
  */
  printf("the last iterm g_arr[%d] = %f\n", g_sumNum-1, g_arr[g_sumNum-1]);
  return 0;
}


//工作线程函数
void*  thread_func(void *argv)
{
  //等待主线程的开始通知
  pthread_mutex_lock(&g_mutex_mainToWorker);
  while(g_sentry_mainToWorker == 0)
      pthread_cond_wait(&g_cond_mainToWorker, &g_mutex_mainToWorker);
  pthread_mutex_unlock(&g_mutex_mainToWorker);

  func_argvs_t* argvs = (func_argvs_t*)argv;
  int id = argvs->m_thread_id;
  printf("start process, id = %d....\n", id);
  int start = g_sumNum/g_threadNum * id;
  int end = 0;
  if(id == g_threadNum-1)
      end = g_sumNum;
  else
      end   = start + g_sumNum/g_threadNum;
  int i = start+1;
  for(; i < end; ++i)
      g_arr[i] = g_arr[i-1] + g_arr[i];
  g_tmp[id] = g_arr[i-1]; 
  //printf("g_arr[%d] = %f\n", i-1, g_arr[i-1]);
  //通知主线程
  pthread_mutex_lock(&g_mutex_workerToMain);
  --g_sentry_workerToMain;
  pthread_mutex_unlock(&g_mutex_workerToMain);
  pthread_cond_signal(&g_cond_workerToMain);
  //等待主线程通知并开始第二步骤
  pthread_mutex_lock(&g_mutex_mainToWorker);
  while(g_sentry_mainToWorker == 1)
      pthread_cond_wait(&g_cond_mainToWorker, &g_mutex_mainToWorker);
  pthread_mutex_unlock(&g_mutex_mainToWorker);
  
  if( id != 0){
      i = start;
      for(; i < end; ++i)
          g_arr[i] += g_tmp[id-1];
  }

  /*//通知主线程
  pthread_mutex_lock(&g_mutex_workerToMain);
  ++g_sentry_mainToWorker;
  pthread_cond_signal(&g_cond_workerToMain);
  pthread_mutex_unlock(&g_mutex_workerToMain);
  printf("thread id = %d, exiting...\n", id);
  pthread_exit(NULL);*/
}

//从文件中加载数据到内存中
void load_data(const char* dataFile)
{ 
  FILE *pf = fopen(dataFile, "r");
  if( pf == NULL)
      handle_error("fopen", -1);

  /*将数据读进内存*/
  fscanf(pf, "%d", &g_sumNum);
  printf("the sumNum is: %d\n", g_sumNum);
  g_arr = (float *)malloc(sizeof(float)*g_sumNum);
  int i = 0;
  while(i < g_sumNum){
      fscanf(pf, "%f", &g_arr[i]);
      ++i;
  }
  close(pf);
}


void handle_error(const char* str, int exitNum)
{
  perror(str);
  exit(exitNum);
}

/*
 * description: 并行算法：求和
 * note:  该方案使用fscanf将数据格式化读进内存，
 *        会导致io调用过于频繁，使用内存映射更好？？？
 * */

#include <stdio.h>
#include <stdlib.h>

void   handle_error(const char* str, int exitNum);
void*  thread_func(void *argvs);

struct func_argvs
{
  float  m_sum;
  int    m_thread_id;
};
typedef struct func_argvs func_argvs_t;

int        g_sumNum = 0;
float      *g_arr = NULL;
int        g_threadNum = 0;



int main(int argc, char* argv[])
{
  if(argc < 3)
      handle_error("Usage: dataFile  threadNum", 1);
 
  FILE *pf = fopen(argv[1], "r");
  if( pf == NULL)
      handle_error("fopen", -1);

  /*将数据读进内存*/
  fscanf(pf, "%d", &g_sumNum);
  printf("the sumNum is: %d\n", g_sumNum);
  g_arr = (float *)malloc(sizeof(float)*g_sumNum);
  int i = 0;
  while(i < g_sumNum){
      fscanf(pf, "%f", &g_arr[i]);
      printf("i = %d\n", g_arr[i]);
      ++i;
  }

//开始启动工作线程，计算总和 
  g_threadNum = atoi(argv[2]);
  pthread_t *threadArr = (pthread_t*)malloc( sizeof(pthread_t) * g_threadNum );
  func_argvs_t *argvs = (func_argvs_t*)malloc( sizeof(func_argvs_t) * g_threadNum );
  for(i = 0; i < g_threadNum; ++i){
      argvs[i].m_thread_id = i;
      argvs[i].m_sum       = 0;
      pthread_create(&threadArr[i], NULL, thread_func,(void*)&argvs[i]);
  }

//等待工作线程结束，求最终结果。
  float      sum_result = 0.0;

  for(i = 0; i < g_threadNum; ++i){
      pthread_join(threadArr[i], NULL);
      sum_result += argvs[i].m_sum;
  }

  free(g_arr);
  free(threadArr);
  free(argvs);
  printf("the sum result is%f\n", sum_result);
  return 0;
}

void* thread_func(void *argvs)
{  
  printf("start process....\n");
  func_argvs_t* argv = (func_argvs_t*)argvs;
  int i = argv->m_thread_id;
  float sum = 0.0;
  int num = 0;
  while(i < g_sumNum){
      sum += g_arr[i];
      i += g_threadNum;
      ++num;
  } 
  argv->m_sum = sum;
  printf("thread%d   sum = %f  num = %d\n", argv->m_thread_id, argv->m_sum, num);
  return NULL;
}

void handle_error(const char* str, int exitNum)
{
  perror(str);
  exit(exitNum);
}

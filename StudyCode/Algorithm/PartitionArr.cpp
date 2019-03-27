 /*************************************************************************
 > File Name: PartitionArr.cpp
 > Author: Ys
 > Created Time: 2019年03月16日 星期六 17时18分05秒
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int getSum(const vector<int>& arr)
{
	int sum = 0;
	for(int i = 0; i < arr.size(); ++i){
		sum += arr[i];
	}
	return sum;
}

bool coreFunc(const vector<int>& arr
			  , int curIndex
			  , int curSum
			  , int desSum
			  , vector<int>& arr01)
{
	for(int i = curIndex; i < arr.size(); ++i){
		if(curSum + arr[i] <= desSum){
			arr01.push_back(i);
			if(curSum + arr[i] == desSum)
				return true;
			else
				if(coreFunc(arr, curIndex+1, curSum+arr[i], desSum, arr01))
					return true;
				else
					arr01.pop_back();
		}
	}
	return false;
}

bool partitionArr(const vector<int>& arr, vector<int>& arr01, vector<int>& arr02)
{
	if(arr.size() < 2)
		return false;
	int sum = getSum(arr);
	if(sum%2 != 0)
		return false;
	sum /= 2;
	return coreFunc(arr, 0, 0, sum, arr01);
}

int main(void)
{
	vector<int>	arr {1,4,2,3}, arr01, arr02;
	
	if(partitionArr(arr, arr01, arr02))
		cout << "partitionArr success!!!" << endl;
	else
		cout << "partitionArr error" << endl;

	cout << "arr01 = " << endl;
	for(int i = 0; i < arr01.size(); ++i)
		cout << arr[arr01[i]] << ", ";
	cout << endl;
    return 0;
}

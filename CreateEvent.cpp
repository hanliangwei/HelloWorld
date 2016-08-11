/*
常用设置一个全局event，用SetEvent使得句柄有信号，ResetEvent使句柄无信号，线程中用WaitForSingleObject来等待event。

函数原型：
HANDLE CreateEvent(

  LPSECURITY_ATTRIBUTES lpEventAttributes,   // 安全属性,如果lpEventAttributes是NULL，此句柄不能被继承。

  BOOL bManualReset,   // 复位方式如果是TRUE，那么必须用ResetEvent函数来手工将事件的状态复原到无信号状态。如果设置为FALSE，当事件被一个等待
  线程释放以后，系统将会自动将事件状态复原为无信号状态。

  BOOL bInitialState,   // 初始状态,如果为TRUE，初始状态为有信号状态；否则为无信号状态。

  LPCTSTR lpName   // 对象名称,指定事件的对象的名称，是一个以0结束的字符串指针。名称的字符格式限定在MAX_PATH之内。名字是对大小写敏感的。

);

*/
#include "iostream"

#include "windows.h"

using namespace std;

DWORD WINAPI ThreadProc1(LPVOID lpParam);

DWORD WINAPI ThreadProc2(LPVOID lpParam);

HANDLE hEvent = NULL;

HANDLE hThread1 = NULL;

HANDLE hThread2 = NULL;

int main(int argc, char *args[])

{
	hEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //使用手动重置为无信号状态，初始化时有信号状态
	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc1, NULL, 0, NULL);
	Sleep(200);
	hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc2, NULL, 0, NULL);
	Sleep(200);
	if (NULL == hThread1 || NULL == hThread2)
	{
		cout << "create thread fail!";
	}
		//DWORD dCount = ResumeThread(hThread);
	system("pause");
	return 0;

}

DWORD WINAPI ThreadProc1(LPVOID lpParam)

{
	cout << "in thread1@!" << endl;
	DWORD dReturn = WaitForSingleObject(hEvent, INFINITE);
	if (WAIT_OBJECT_0 == dReturn)
	{
		cout << " thread1 signaled ! " << endl;
	}
	cout << "in thread1 --signal" << endl;
//	ResetEvent(hEvent);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	cout << "in thread2@!" << endl;
	DWORD dReturn = WaitForSingleObject(hEvent, INFINITE);
	if (WAIT_OBJECT_0 == dReturn)
	{
		cout << "thread2 signaled ! " << endl;
	}

	cout << "in thread2--signal" << endl;
	
	return 0;

}
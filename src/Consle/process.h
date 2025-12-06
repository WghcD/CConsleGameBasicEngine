#include<windows.h>
#include<cstdio>
#include<string>
#include<fstream>
#pragma comment(lib, "Kernel32.lib")
#include <TlHelp32.h>  
#include <psapi.h>
#include <vector>
#define GetProcess getProcess
#define GetPid getPid

using namespace std;

bool getProcess(const char *procressName)                //此函数用于检查进程是否存在 进程名不区分大小写
{
    char pName[MAX_PATH];                                //和PROCESSENTRY32结构体中的szExeFile字符数组保持一致，便于比较
    strcpy(pName,procressName);                            //拷贝数组
    CharLowerBuff(pName,MAX_PATH);                        //将名称转换为小写
    PROCESSENTRY32 currentProcess;                        //存放快照进程信息的一个结构体
    currentProcess.dwSize = sizeof(currentProcess);        //在使用这个结构之前，先设置它的大小
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//给系统内的所有进程拍一个快照

    if (hProcess == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot()调用失败!\n");
        return false;
    }

    bool bMore=Process32First(hProcess,&currentProcess);        //获取第一个进程信息
    while(bMore)
    {
        CharLowerBuff(currentProcess.szExeFile,MAX_PATH);        //将进程名转换为小写
        if (strcmp(currentProcess.szExeFile,pName)==0)            //比较是否存在此进程
        {
            CloseHandle(hProcess);                                //清除hProcess句柄
            return true;
        }
        bMore=Process32Next(hProcess,&currentProcess);            //遍历下一个
    }

    CloseHandle(hProcess);    //清除hProcess句柄
    return false;//进程不存在
}

DWORD getPid(const char *name)  //获取指定影响名的进程pid
{
    HANDLE  hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hsnapshot == INVALID_HANDLE_VALUE) 
    {   
        printf("CreateToolhelp32Snapshot Error!\n");
        return 0;  
    }
    
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    int flag = Process32First(hsnapshot, &pe);

    while (flag != 0)
    {
        if (strcmp(pe.szExeFile, name) == 0)
        {
            return pe.th32ProcessID;
        }
        flag = Process32Next(hsnapshot, &pe);
    }

    CloseHandle(hsnapshot);

    return 0;
}



void ShowWindowsByPID(DWORD pid) {
    HWND hWnd = NULL;
    while ((hWnd = FindWindowEx(NULL, hWnd, NULL, NULL))) {
        DWORD lpdwProcessId;
        GetWindowThreadProcessId(hWnd, &lpdwProcessId);
        if (lpdwProcessId == pid) {
            ShowWindow(hWnd, SW_SHOW);
        }
    }
}

void HideWindowsByPID(DWORD pid) {
    HWND hWnd = NULL;
    while ((hWnd = FindWindowEx(NULL, hWnd, NULL, NULL))) {
        DWORD lpdwProcessId;
        GetWindowThreadProcessId(hWnd, &lpdwProcessId);
        if (lpdwProcessId == pid) {
            ShowWindow(hWnd, SW_HIDE);
        }
    }
}
 


DWORD GetProcessFromMainWindow() {//返回当前顶层窗口进程PID
	HWND hwnd = GetForegroundWindow();
    DWORD lpdwProcessId;
    DWORD threadId = GetWindowThreadProcessId(hwnd, &lpdwProcessId);
    return lpdwProcessId;
}
int MinimizeWindowsByPid(DWORD processID ){
    int n=0;
    HWND hwnd = FindWindowEx(NULL, NULL, NULL, NULL); // 遍历所有窗口，实际应用中可能需要更精确的查找方式
    while (hwnd != NULL) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == processID) {
            // 找到对应的窗口，最小化它
            ShowWindow(hwnd, SW_MINIMIZE);
            n++;
        }
        hwnd = FindWindowEx(NULL, hwnd, NULL, NULL); // 继续查找下一个窗口
    }
    return n;
}
#pragma once

void MaximizeConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow == NULL) return;
    
    // 获取工作区尺寸(排除任务栏)
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    
    // 计算最大化尺寸(留5像素边框)
    int width = workArea.right - workArea.left - 10;
    int height = workArea.bottom - workArea.top - 10;
    
    // 设置窗口位置和大小
    SetWindowPos(consoleWindow, HWND_TOP, 
                workArea.left + 5, workArea.top + 5,
                width, height, 
                SWP_SHOWWINDOW);
    
    // 禁用最大化按钮防止进入全屏
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    SetWindowLong(consoleWindow, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
}

void ConsleQuit(){
	KeyInput.Stop();
	TerminateProcess(GetCurrentProcess(), 0); 
}
BOOL WINAPI ConsoleHandler(DWORD signal) {
    switch(signal) {
    case CTRL_CLOSE_EVENT:  // 点击关闭按钮时触发
		Log("Programm exit by CTRL_CLOSE_EVENT");
		
		Log("Programm will self-kill");
		ConsleQuit();
        return true;  // 返回TRUE表示已处理，阻止默认关闭行为
        
    case CTRL_C_EVENT:      // Ctrl+C
		Log("Programm exit by CTRL_C_EVENT");
		ConsleQuit();
		return true;
    case CTRL_BREAK_EVENT:  // Ctrl+Break
		Log("Programm exit by CTRL_BREAK_EVENT");
		ConsleQuit();
        return true;       
    }
    return FALSE;
}
void NoEdit(){
	HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;
	mode&=~ENABLE_INSERT_MODE;
	mode&=~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin,mode);
}
void SetTitle(string title){
	string a="title ";
    string commond=a+title;
    system(commond.c_str());
}
bool ConsleInit(){
	conhandle=GetStdHandle(STD_OUTPUT_HANDLE);
	MaximizeConsoleWindow();
	NoEdit();

	SetTitle(TITLE);
	if(!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {//高帧率必须要注册拦截窗口关闭   否则windows会爆程序未正常终止
        std::cout << "无法注册控制台处理器" << std::endl; PAUSE   return false;
    }
	printf("If you can see this massage clearly,it means that you have been in trouble :(");
	system("cls");
	return true;
}
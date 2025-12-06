#pragma once
#include <windows.h>
#include <queue>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <mutex>

unordered_map<char,bool> KeyState;
bool KeyInputState=false;
class MouseState{
	Point pos;
	bool isClick;
};



char ProcessVkToChar(int Vk){
	char result='N';
	if(Vk>=65&&Vk<=65+26){result='a'+Vk-65;}
	else if(Vk>=161&&Vk<=161+26){result='a'+Vk-161;}//统一为小写
	else if(Vk>=48&&Vk<=48+9){result='0'+Vk-48;}
	else if(Vk>=96&&Vk<=96+9){result='0'+Vk-96;}
	return result;
}

class KeyBoardMonitor {
    HHOOK hHook;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION) {
            KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
				//Log(to_string(p->vkCode));
				KeyState[ProcessVkToChar(p->vkCode)]=true;
            }
			else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
				//Log(to_string(p->vkCode));
				KeyState[ProcessVkToChar(p->vkCode)]=false;
			}	
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }



    void Run() {
		Log("KeyMonitor Thread Started");
		KeyInputState=true;
        hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0) && IsRunning) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        

    }

public:
    static KeyBoardMonitor& GetInstance() {
        static KeyBoardMonitor instance;
        return instance;
    }
    void Start() {
        thread KeyInputThread(&KeyBoardMonitor::Run, this);
        KeyInputThread.detach();
    }
    void Stop() {
		
    }

    
};



KeyBoardMonitor KeyInput;


bool getKey(char TargetKey){//某键是否按下或抬起
	if(TargetKey>='A'&&TargetKey<='Z'){TargetKey='a'+TargetKey-'A';}
	if(!KeyInputState){KeyInput.Start();return 'N';}
	//Log(to_string(TargetKey));
	return KeyState[TargetKey];
}

#pragma once
#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测鼠标的点击事件

#include"head.h"
int cursor_y() {
		POINT p;
		int x, y;
		CONSOLE_FONT_INFO a;
		GetCursorPos(&p);
		ScreenToClient(GetForegroundWindow(), &p);
		GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &a);
		x = p.x / a.dwFontSize.X;
		y = p.y / a.dwFontSize.Y;
		return y;
}

int cursor_x() {
		POINT p;
		int x, y;
		CONSOLE_FONT_INFO a;
		GetCursorPos(&p);
		ScreenToClient(GetForegroundWindow(), &p);
		GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &a);
		x = p.x / a.dwFontSize.X;
		y = p.y / a.dwFontSize.Y;
		return x;
}
int key_down() {
		if (KEYDOWN(VK_LBUTTON)) {              //鼠标左键按下
			return 1;
		}
		else{
			return 0;
		}
}
#pragma once
#include<windows.h>
#include<iostream>
using namespace std;

char GetConsoleChar(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) {
        std::cerr << "获取控制台句柄失败" << std::endl;
        return '\0';
    }

    // 获取控制台屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        std::cerr << "获取控制台缓冲区信息失败" << std::endl;
        return '\0';
    }

    // 检查坐标是否在有效范围内
    if (x < 0 || x >= csbi.dwSize.X || y < 0 || y >= csbi.dwSize.Y) {
        std::cerr << "坐标超出缓冲区范围" << std::endl;
        return '\0';
    }

    // 读取字符
    CHAR_INFO charInfo;
    COORD bufSize = {1, 1};  // 要读取的区域大小（1x1）
    COORD bufCoord = {0, 0}; // 缓冲区起始坐标
    SMALL_RECT readRegion = {x, y, x, y}; // 要读取的区域

    if (!ReadConsoleOutput(hStdout, &charInfo, bufSize, bufCoord, &readRegion)) {
        std::cerr << "读取控制台输出失败" << std::endl;
        return '\0';
    }

    return charInfo.Char.AsciiChar;
}
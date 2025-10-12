#pragma once

#include"../Map/map.h"



std::vector<point> getLinepoints(int x0,int y0,int x1,int y1) {//返回指定线段每个点的坐标
	point p1(x0,y0);point p2(x1,y1);
    std::vector<point> points;

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    // 计算步数，取x和y方向的最大差值
    int steps = std::max(std::abs(dx), std::abs(dy));

    // 如果两点重合，直接返回其中一个点
    if (steps == 0) {
        points.push_back(p1);
        return points;
    }

    // 计算x和y的增量
    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = p1.x;
    float y = p1.y;

    // 生成线段上的点
    for (int i = 0; i <= steps; ++i) {
        points.push_back({static_cast<int>(std::round(x)), static_cast<int>(std::round(y))});
        x += xIncrement;
        y += yIncrement;
    }

    return points;
}
std::vector<point> getLinepoints(point p1, point p2) {//返回指定线段每个点的坐标
    std::vector<point> points;

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    // 计算步数，取x和y方向的最大差值
    int steps = std::max(std::abs(dx), std::abs(dy));

    // 如果两点重合，直接返回其中一个点
    if (steps == 0) {
        points.push_back(p1);
        return points;
    }

    // 计算x和y的增量
    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = p1.x;
    float y = p1.y;

    // 生成线段上的点
    for (int i = 0; i <= steps; ++i) {
        points.push_back({static_cast<int>(std::round(x)), static_cast<int>(std::round(y))});
        x += xIncrement;
        y += yIncrement;
    }

    return points;
}

bool line(int x0,int y0,int x1,int y1,int color,char look){
	if(!(x0<0&&y0<0&&x0>CONHIGH&&y0>CONWIDE&&x1<0&&y1<0&&x1>CONHIGH&&y1>CONWIDE)){return false;}
	vector<point> pointList=getLinepoints(x0,y0,x1,y1);
	for(point p:pointList){
		gto(p.x,p.y);printf("%c",look);
	}
	return true;
}

void set_character_size(int x,int y){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);
    fontInfo.dwFontSize.X = x;
    fontInfo.dwFontSize.Y = y;
    SetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);
}


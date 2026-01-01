#pragma once

//仅为world.cpp所包含与使用

#include"../Include/object_base.h"
#include <vector>
#include <functional>


class _GraphicsGenerater{
public:
_GraphicsGenerater(){;}
// 生成两点间直线的所有坐标点 (Bresenham算法)
vector<Point> Line(Point p1, Point p2) {
    vector<Point> points;
    int dx = abs(p2.x - p1.x), dy = abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = dx - dy;

    while (true) {
        points.push_back({p1.x, p1.y});
        if (p1.x == p2.x && p1.y == p2.y) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; p1.x += sx; }
        if (e2 < dx)  { err += dx; p1.y += sy; }
    }
    return points;
}


// 生成圆的所有坐标点 (参数方程法，适配控制台宽高比)
vector<Point> Circle(Point center, int radius) {
    set<Point> points;
    

    const double aspectRatio = 2; // 字符宽高比(宽:高=1:2)
    const double step = 0.01;       // 角度步长(弧度)
    
    for (double angle = 0; angle < 2 * M_PI; angle += step) {
        int x = round(center.x + radius * cos(angle));
        int y = round(center.y + radius * sin(angle) * aspectRatio);
        points.insert({x, y});
    }
    

    return vector<Point>(points.begin(), points.end());
}
}GraphicsGenerater;


class GE_Base : public ObjectBase
{
public:
	int lastUpdate,updateSpeed;
	vector<Point> image;
	GE_Base(){
		putUpdate();
		get_uuid(EFFECT_TYPE);
	}
	int last_time;
	virtual void destory(){
		
	}
	virtual void update(){
		if(!canUpdate())return;
		putUpdate();
	}
	void putUpdate(){BackObjectUpdateQueue.push(std::bind(&GE_Base::update, this));}
	bool canUpdate(){if(clock()-lastUpdate>updateSpeed){lastUpdate=clock();return true;}else{return false;}}
	
};


class Circle1 : public GE_Base
{
public:
	Circle1(){
		image=GraphicsGenerater.Circle({10,10},5);
	}
	void update(){
		if(!canUpdate())return;
		putUpdate();

		for(Point now:image){
		buffer.write(uuid,now.x,now.y);

		
		}

	}
};

class Line1 : public GE_Base
{
public:
	Line1(){
		
	}
};
























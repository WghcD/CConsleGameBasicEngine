#pragma once

//仅为world.cpp所包含与使用

#include"../Include/object_base.h"
#include <vector>
#include <functional>





class _GraphicsGenerater{
public:
_GraphicsGenerater(){}





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
    const double step = 0.01;       // 角度步长(弧度)  可以调大减少重复
    
    for (double angle = 0; angle < 2 * M_PI; angle += step) {
        int x = round(center.x + radius * cos(angle));
        int y = round(center.y + radius * sin(angle) * aspectRatio);
        points.insert({x, y});
    }
    

    return vector<Point>(points.begin(), points.end());
}







// 重整圆点为顺时针顺序（O(n log n)）
std::vector<Point> reorderCircle(const std::vector<Point>& points) //利用了分层的特殊性质
{
    vector<Point> result;result.push_back(points[0]);Point lastPoint=points[0];
    for(int i=1;i<points.size();i++){
		if(points[i].x==lastPoint.x){lastPoint=points[i];result.push_back(lastPoint);continue;}
		else{
			for(int j=i+1;;j++){
				
			}
		}
	}
    return result;
}

}GraphicsGenerater;


class GE_Base : public ObjectBase
{
public:

	vector<Point> image;
	GE_Base(){
		
		get_uuid(EFFECT_TYPE);
	}
	int last_time;
	
	virtual void update(){
		
		
	}

	
};


class Circle1 : public GE_Base
{
public:
	Circle1(){
		image=GraphicsGenerater.Circle({5,10},5);
	}
	void update(){
		
		

		for(Point now:image){
		buffer.write(uuid,now.x,now.y);

		
		}

	}
};

class Line1 : public GE_Base
{
public:
	Line1(){
		image=GraphicsGenerater.Line({5,10},{5,20});
	}
	void update(){
		
		

		for(Point now:image){
		buffer.write(uuid,now.x,now.y);
		}
	}
};


class ClockSample : public GE_Base
{
public:
	int r=10,sx=20,sy=60;
	int i=0;
	vector<Point> circle,line;
	ClockSample(){
		sx=Rand(maxX);sy=Rand(maxY);
		circle=GraphicsGenerater.Circle({sx,sy},r);
		updateSpeed=100;
	}
	void update(){
		

		
		line=GraphicsGenerater.Line({sx,sy},circle[i]);
		i++;if(i>=circle.size()){i=0;}
		for(Point now:line){
		buffer.write(uuid,now.x,now.y);
		}
		for(Point now:circle){
		buffer.write(uuid,now.x,now.y);
		
		}
	}
};


class FireworkSample : public GE_Base
{
public:
	int r=10,sx=20,sy=60,linesCount=0,i=0;
	vector<Point> circle;
	vector<vector<Point>> lines;
	FireworkSample(){
		sx=Rand(maxX);sy=Rand(maxY);
		circle=GraphicsGenerater.Circle({sx,sy},r);
		updateSpeed=150;
		for(Point now:circle){
			vector<Point> newLine=GraphicsGenerater.Line({sx,sy},now);
			lines.push_back(newLine);
			linesCount++;
		}
	}
	void update(){
		
		bool flag=1;
		for(int k=0;k<linesCount;k++){
			if(lines[k].size()>i){buffer.write(uuid,lines[k][i].x,lines[k][i].y,random(15));flag=0;}
		}
		if(flag)i=0;else i++;
		
		for(Point now:circle){
		buffer.write(uuid,now.x,now.y);
		}
	}
};























#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
#define WL WriteLog
bool WriteLog(string l){
	ofstream Log;
	Log.open("CommonLog.log", std::ios_base::app);
	Log<<"["<<to_string(clock())<<"] "<<l<<"\n";
	Log.close();
	return true;
}

bool WriteLog(string l,string fileName){
	ofstream Log;
	Log.open(fileName.c_str(), std::ios_base::app);
	Log<<"["<<to_string(clock())<<"] "<<l<<"\n";
	Log.close();
	return true;
}
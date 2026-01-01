#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
#define WL WriteLog
#define Log WriteLog
ofstream TMDC;
bool WriteLog(const string& l){

	
	
	TMDC<<"["<<to_string(clock())<<"] "<<l<<"\n";

	return true;
}

bool WriteLog(int n){
	return WriteLog(to_string(n));
}

bool WriteLog(const string& l,const string& fileName){
	ofstream og;
	og.open(fileName.c_str(), std::ios_base::app);
	og<<"["<<to_string(clock())<<"] "<<l<<"\n";
	og.close();
	return true;
}

void LogInit(){
	TMDC.open("CommonLog.log", std::ios_base::app);
}
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
#define WL WriteLog
#define Log WriteLog
bool WriteLog(const string& l){
	if(l==" SSCC"||l==" OK"||l=="rogramm will exit with ExitCode"||l=="Posision: ")return false;
	ofstream Log;
	Log.open("CommonLog.log", std::ios_base::app);
	Log<<"["<<to_string(clock())<<"] "<<l<<"\n";
	Log.close();
	return true;
}

bool WriteLog(int n){
	return WriteLog(to_string(n));
}

bool WriteLog(const string& l,const string& fileName){
	ofstream Log;
	Log.open(fileName.c_str(), std::ios_base::app);
	Log<<"["<<to_string(clock())<<"] "<<l<<"\n";
	Log.close();
	return true;
}
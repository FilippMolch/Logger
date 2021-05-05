#pragma once

#ifndef LOGGER
#define LOGGER

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <thread>
#include <fstream>
#include <queue>

using namespace std;

enum logType
{
	INFO,
	WARN,
	ERROR,
};

namespace Logger{
	queue<string> logs;
	ofstream file;
	bool ready = false;
	

	string getTimeLog(){
		time_t t = time(nullptr);
		tm tm = *localtime(&t);
		stringstream time;
		time << put_time(&tm, "%Y-%m-%d %X");
		return time.str();
	}
	
	string getTimeLog(bool file) {
		time_t t = time(nullptr);
		tm tm = *localtime(&t);
		stringstream time;
		time << put_time(&tm, "%Y-%m-%d");
		return time.str();
	}

	void mainLoop(){
		ready = false;

		while (!logs.empty())
		{
			file << logs.front() << endl;
			logs.pop();
		}

		
		file.close();
		ready = true;
	}

	bool logReady(){
		return (ready && logs.empty());
	}

	void init(string path){

		file.open(path + "log" + getTimeLog(true) + ".txt");
	}

	void write(){
		ready = false;
		thread writeThread(mainLoop);
		writeThread.detach();
	}

	void addLog(string text, logType type){
		switch (type)
		{

		case INFO:
			cout << "[" << getTimeLog() << "]" << "[";
			printf("\x1B[34mINFO\033[0m");
			cout << "]" << "-->" << text << endl;
			logs.push("[" + getTimeLog() + "]" + "[" + "INFO" + "]" + "-->" + text);
			break;
		case WARN:
			cout << "[" << getTimeLog() << "]" << "[";
			printf("\x1B[33mWARN\033[0m");
			cout << "]" << "-->" << text << endl;
			logs.push("[" + getTimeLog() + "]" + "[" + "WARN" + "]" + "-->" + text);
			break;
		case ERROR:
			cout << "[" << getTimeLog() << "]" << "[";
			printf("\x1B[31mERORR\033[0m");
			cout << "]" << "-->" << text << endl;
			logs.push("[" + getTimeLog() + "]" + "[" + "ERROR" + "]" + "-->" + text);
			break;
		default:
			break;
		}
	}

	void deinit(){
		file.close();
	}
};

#endif // !LOGGER

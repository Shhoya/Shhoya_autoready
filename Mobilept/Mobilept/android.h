#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <io.h>
using namespace std;

class Android
{

public:
	void and_logo()
	{
		system("cls");
		cout << "  =========================================== " << endl;
		cout << "|   ___              _              _      _  |" << endl;
		cout << "|  / _ \\            | |            (_)    | | |" << endl;
		cout << "| / /_\\ \\ _ __    __| | _ __  ___   _   __| | |" << endl;
		cout << "| |  _  || '_ \\  / _` || '__|/ _ \\ | | / _` | |" << endl;
		cout << "| | | | || | | || (_| || |  | (_) || || (_| | |" << endl;
		cout << "| \\_| |_/|_| |_| \\__,_||_|   \\___/ |_| \\__,_| |" << endl;
		cout << "|                                             |" << endl;
		cout << "  ============================================ " << endl;
		cout << endl;
	}
	
	void Android_s(); // Select menu
	void AndroidMenu(); // Print menu
	void a_Decompile(); //APK Decompile
	void a_Data(); // APP Data extraction
	void appList(); // apk list extraction
	void appDownload(string); //APK Download
	void memdump(); // APP Memory dump
	void app_build(); // APK Build
	void exec_t(char*); // Shell execute function, SW_SHOW
	void exec_h(char*); // Shell execute function, SW_HIDE
	void suspicious_str(); // Search for Rooting detection string 
	int exception_D(); // error exception
	void Search(); // Search for APK , DATA name
	
};


#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
using namespace std;

class Android
{

public:
	void and_logo()
	{
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
	
	void Android_s();
	void AndroidMenu();
	void a_Decompile();
	void a_Data();
	void appList();
	void appDownload(string);
	void memdump();
	void app_build();

	
};
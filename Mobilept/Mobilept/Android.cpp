#pragma once
#include <iostream>
#include "android.h"

using namespace std;

/*****************************************************************/
/* Android App List, APK Download, Decompile and Data extraction */
/*****************************************************************/

HINSTANCE shell = ShellExecute(NULL, "find", "adb", NULL, NULL, SW_SHOW);
const int len = 100;

void Android::AndroidMenu()
{
	system("cls");
	and_logo();
	cout << "[1] APK Download" << endl;
	cout << "[2] APK Decompile " << endl;
	cout << "[3] App Data Download " << endl;
	cout << "[4] Back" << endl;
	cout << "[5] Exit" << endl;
}

void Android::Android_s()
{
	int select;
	if (shell == (HINSTANCE)ERROR_FILE_NOT_FOUND)
	{
		cout << endl;
		cout << "[!] Could not found ADB " << endl;
		system("pause");
		cout << endl;
		return;
	}
	while (1)
	{
		AndroidMenu();
		cout << "\n[*] Select Menu: "; cin >> select;
		switch (select)
		{
		case 1:
			appList();
			break;
		case 2:
			a_Decompile();
			break;

		case 3:
			a_Data();
			break;

		case 4:
			system("cls");
			return;

		case 5:
			cout << "Thank you ;)" << endl;
			//system("pause");
			exit(0);

		default:
			cout << "\n[!] INPUT ERROR, Check input number!" << endl;
			system("pause");
			exit(0);

		}

	}

}
/*********************************/
/* Print app list & app download */
/*********************************/

void Android::appList()
{
	string app_list = "app_list.txt";
	string line;
	int i = 0;
	string appnm[100];
	system("adb shell su -c 'ls /data/app' > app_list.txt");
	cout << endl;
	cout << "[+] Save app_list.txt" << endl;
	Sleep(1000);
	system("cls");
	ifstream openFile(app_list.data());
	while (getline(openFile, line))
	{
		if (line == "")
		{
			break;
		}
		appnm[i] = line;
		cout << i + 1 << ". " << appnm[i] << endl;
		i++;
	}
	cout << "[*] Download Number : ";
	cin >> i;
	appDownload(appnm[i - 1]);

}

void Android::appDownload(string appName)
{

	const char *nm = appName.c_str();
	char pull[len] = "/c adb pull /data/app/";
	strcat(pull, nm);
	ShellExecute(NULL, "open", "cmd", pull, NULL, SW_HIDE);
	system("cls");
	and_logo();
	cout << endl << endl << "[+] Downloading " << nm << endl;
	Sleep(4000);
	cout << "[+] Complete" << endl;
	system("pause");

}

/*****************/
/* APK Decompile */
/*****************/

void Android::a_Decompile()
{
	char *decompile = "/c java -jar apktools d base.apk";
	ShellExecute(NULL, "open", "cmd", decompile, NULL, SW_HIDE);
	system("cls");
	and_logo();
	cout << endl << endl << "[+] Decompiling APK.." << endl;
	Sleep(5000);
	cout << "[+] Complete" << endl;
	system("pause");

	/* Loading apply 
	SHELLEXECUTEINFO dec_info;
	ZeroMemory(&dec_info, sizeof(dec_info));
	dec_info.cbSize = sizeof(dec_info);
	dec_info.lpVerb = "open";
	dec_info.lpFile = "cmd";
	dec_info.lpParameters = "/c java -jar apktools d base.apk";
	dec_info.fMask = SEE_MASK_FLAG_NO_UI || SEE_MASK_NOCLOSEPROCESS;
	dec_info.nShow = SW_HIDE;
	int run = (int)ShellExecuteEx(&dec_info);
	WaitForSingleObject(dec_info.hProcess, INFINITY);
	cout << "[+] Decompile Complete, Enj0y Rev3rs1ng" << endl;
*/

	/*system("adb devices > ./adb_log.txt");
	ifstream openFile(log.data());
	if (openFile.is_open())
	{
		string line;
		while (getline(openFile, line)) {
			cout << line << endl;
		}
		openFile.close();
	}*/

}

void Android::a_Data()
{
	cout << "a_Data() Call" << endl;
}
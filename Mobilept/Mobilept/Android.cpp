#pragma once
#include <iostream>
#include "android.h"

using namespace std;

/*****************************************************************/
/* Android App List, APK Download, Decompile and Data extraction */
/*****************************************************************/

HINSTANCE shell = ShellExecute(NULL, "find", "adb", NULL, NULL, SW_SHOW);
const int len = 300;
char decompile[len] = "/c java -jar ./tools/apktools.jar d base.apk";
char build[len] = "/c java -jar ./tools/apktools.jar b base -o build.apk";
char sign[len] = "/c java -jar ./tools/signapk.jar ./tools/testkey.x509.pem ./tools/testkey.pk8 build.apk cyb3r1.apk";

void Android::AndroidMenu()
{
	system("cls");
	and_logo();
	cout << "[1] APK Download & Decompile" << endl;
	cout << "[2] Only Decompile " << endl;
	cout << "[3] App Data Download " << endl;
	cout << "[4] App Memory Dump " << endl;
	cout << "[5] App Build " << endl;
	cout << "[6] Back" << endl;
	cout << "[0] Exit" << endl;
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
			memdump();
			break;

		case 5:
			app_build();
			break;
		case 6:
			system("cls");
			return;

		case 0:
			cout << "Thank you ;)" << endl;
			system("pause");
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
	string appnm[1000];
	system("adb shell su -c 'ls /data/app' > app_list.txt");
	cout << endl;
	cout << "[+] Save app_list.txt" << endl;
	Sleep(1000);
	system("cls");
	ifstream openFile(app_list.data());
	while (getline(openFile, line))
	{
		appnm[i] = line;
		cout << i + 1 << ". " << appnm[i] << endl;
		i++;
	}
	cout << "[*] Download Number : ";
	cin >> i;
	openFile.close();
	appDownload(appnm[i - 1]);


}

void Android::appDownload(string appName)
{
	system("cls");
	and_logo();
	const char *nm = appName.c_str();
	char pull[len] = "/c adb pull /data/app/";
	strcat(pull, nm);
	cout << endl<<"[+] Downloading ..." << endl;
	exec_h(pull);
	cout << "[+] Download Complete" << endl;
	cout << "[*] Next Decompile ;)"<<endl;
	system("pause");
	a_Decompile();
}

/*****************/
/* APK Decompile */
/*****************/

void Android::a_Decompile()
{
	system("cls");
	and_logo();
	cout << endl << "[+] Decompiling..." << endl;;
	exec_t(decompile);
	cout << "[+] Decompile Complete, Enj0y Rev3rs1ng" << endl;
	system("pause");
}

/*********************/
/* App Data Download */
/*********************/
void Android::a_Data()
{
	string app_list = "data_list.txt";
	string line;
	int i = 0;
	string appnm[1000];
	char pull[1000] = "/c adb pull /sdcard/Download/Autoready/data/";
	system("adb shell su -c 'ls /data/data' > data_list.txt");
	cout << endl;
	cout << "[+] Save data_list.txt" << endl;
	system("adb shell su -c 'mkdir /sdcard/Download/Autoready'");
	ShellExecute(NULL, "open", "adb", "shell su -c 'cp -R /data/data /sdcard/Download/Autoready/'", NULL, SW_HIDE);
	cout << "[+] Wait a minute plz ;)";
	Sleep(5000);
	system("cls");
	ifstream openFile(app_list.data());
	while (getline(openFile, line))
	{
		appnm[i] = line;
		cout << i + 1 << ". " << appnm[i] << endl;
		i++;
	}
	cout << "[*] Download Number : ";
	cin >> i;
	const char* nm = appnm[i - 1].c_str();
	strcat(pull, nm);
	cout << endl << "[+] Data Downloading..." << endl;
	exec_h(pull);
	system("adb shell su -c 'rm -rf /sdcard/Download/Autoready'");
	cout << "[+] Complete, Honeyjam ;) " << endl;
	openFile.close();
	system("pause");
}

/*******************************/
/* App Memory Dump via fridump */
/*******************************/
void Android::memdump()
{
	system("cls");
	and_logo();
	char app_id[1000];
	char memdump[1000] = "/c python ./tools/fridump.py -us ";
	system("frida-ps -Ua");
	Sleep(1000);
	cout << "[*] Check App identifier" << endl;
	cout << "[*] Input App Identifier : ";
	cin >> app_id;
	strcat(memdump, app_id);
	cout << "[+] fridump start, Wait a minute plz ;) " << endl;
	Sleep(1300);
	exec_t(memdump);
	cout << endl << "[+] Dump complete, Honeyjam ;) " << endl;
	system("pause");
	
}

/********************/
/* APK Build & Sign */
/********************/
void Android::app_build()
{
	system("cls");
	and_logo();
	exec_h(build);
	cout << "[+] Building Complete" << endl;
	cout << "[*] Sign Process Start" << endl;
	exec_h(sign);
	system("del build.apk");
	cout << "[+] Complete, Honeyjam ;) " << endl;
	system("pause");
	
}

void Android::exec_h(char* param)
{
	SHELLEXECUTEINFO build_info;
	ZeroMemory(&build_info, sizeof(build_info));
	build_info.cbSize = sizeof(build_info);
	build_info.lpVerb = "open";
	build_info.lpFile = "cmd.exe";
	build_info.lpParameters = param;
	build_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	build_info.nShow = SW_HIDE;
	ShellExecuteEx(&build_info);
	cout << endl;
	WaitForSingleObject(build_info.hProcess, INFINITE);
}

void Android::exec_t(char* param)
{

	SHELLEXECUTEINFO build_info;
	ZeroMemory(&build_info, sizeof(build_info));
	build_info.cbSize = sizeof(build_info);
	build_info.lpVerb = "open";
	build_info.lpFile = "cmd.exe";
	build_info.lpParameters = param;
	build_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	build_info.nShow = SW_SHOWNA;
	ShellExecuteEx(&build_info);
	cout << endl;
	WaitForSingleObject(build_info.hProcess, INFINITE);
	
}
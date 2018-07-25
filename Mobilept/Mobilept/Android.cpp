#pragma once
#include <iostream>
#include "android.h"

using namespace std;

/*****************************************************************/
/* Android App List, APK Download, Decompile and Data extraction */
/*****************************************************************/

HINSTANCE shell = ShellExecute(NULL, "find", "adb", NULL, NULL, SW_SHOW);
const int len = 300;

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
	string appnm[1000];
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
	and_logo();
	const char *nm = appName.c_str();
	char pull[len] = "/c adb pull /data/app/";
	strcat(pull, nm);
	//ShellExecute(NULL, "open", "cmd", pull, NULL, SW_HIDE);
	//system("cls");
	//and_logo();
	//cout << endl << endl << "[+] Downloading " << nm << endl;
	//Sleep(4000);
	//cout << "[+] Complete" << endl;
	//system("pause");
	SHELLEXECUTEINFO dl_info;
	ZeroMemory(&dl_info, sizeof(dl_info));
	dl_info.cbSize = sizeof(dl_info);
	dl_info.lpVerb = "open";
	dl_info.lpFile = "cmd.exe";
	dl_info.lpParameters = pull;
	dl_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	dl_info.nShow = SW_HIDE;
	int run = (int)ShellExecuteEx(&dl_info);
	if (run != NULL)
	{
		cout << endl;
		cout << "[+] Downloading " << nm << endl;
		WaitForSingleObject(dl_info.hProcess, INFINITE);
	}
	cout << endl;
	cout << "[+] Download Complete" << endl;
	cout << "[*] Next Decompile ;)";
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
	/* Loading apply */
	SHELLEXECUTEINFO dec_info;
	ZeroMemory(&dec_info, sizeof(dec_info));
	dec_info.cbSize = sizeof(dec_info);
	dec_info.lpVerb = "open";
	dec_info.lpFile = "cmd.exe";
	dec_info.lpParameters = "/c java -jar apktools.jar d base.apk";
	dec_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	dec_info.nShow = SW_HIDE;
	ShellExecuteEx(&dec_info);
	cout << endl;
	cout << "[+] Decompiling APK. . ." << endl;
	WaitForSingleObject(dec_info.hProcess, INFINITE);
	cout << "[+] Decompile Complete, Enj0y Rev3rs1ng" << endl;
	system("pause");
}

/*********************/
/* App Data Download */
/*********************/
void Android::a_Data()
{
	/*
	char pull[len] = "/c adb shell su -c \"cp -R /data/data/";
	char pull2[] = " /storage/emulated/0/Download/\"";
	char pull3[len] = "/c adb pull /storage/emulated/0/Download/";
	string data_list = "data_list.txt";
	string line;
	int i = 0;
	string appnm[1000];
	system("adb shell su -c 'ls /data/data' > data_list.txt");
	cout << endl;
	cout << "[+] Save data_list.txt" << endl;
	Sleep(1000);
	system("cls");
	ifstream openFile(data_list.data());
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
	const char *nm = appnm[i - 1].c_str();
	strcat(pull, nm);
	cout << pull << endl;


	system("pause");
	SHELLEXECUTEINFO cp_info;
	ZeroMemory(&cp_info, sizeof(cp_info));
	cp_info.cbSize = sizeof(cp_info);
	cp_info.lpVerb = "open";
	cp_info.lpFile = "cmd.exe";
	cp_info.lpParameters = pull;
	cp_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	cp_info.nShow = SW_HIDE;
	ShellExecuteEx(&cp_info);
	WaitForSingleObject(cp_info.hProcess, INFINITE);
	SHELLEXECUTEINFO dl_info;
	ZeroMemory(&dl_info, sizeof(dl_info));
	dl_info.cbSize = sizeof(dl_info);
	dl_info.lpVerb = "open";
	dl_info.lpFile = "cmd.exe";
	dl_info.lpParameters = pull;
	dl_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	dl_info.nShow = SW_HIDE;
	ShellExecuteEx(&dl_info);
	cout << endl;
	cout << "[+] Downloading " << nm << endl;
	WaitForSingleObject(dl_info.hProcess, INFINITE);
	cout << endl;
	cout << "[+] Download Complete" << endl;
	system("pause");
	*/
}

void Android::memdump()
{
	cout << "memdump() Call" << endl;

}


/********************/
/* APK Build & Sign */
/********************/
void Android::app_build()
{
	system("cls");
	and_logo();
	SHELLEXECUTEINFO build_info;
	ZeroMemory(&build_info, sizeof(build_info));
	build_info.cbSize = sizeof(build_info);
	build_info.lpVerb = "open";
	build_info.lpFile = "cmd.exe";
	build_info.lpParameters = "/c java -jar apktools.jar b base -o build.apk";
	build_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	build_info.nShow = SW_SHOWNA;
	ShellExecuteEx(&build_info);
	cout << endl;
	WaitForSingleObject(build_info.hProcess, INFINITE);
	cout << "[+] Building Complete" << endl;
	cout << "[*] Sign Process Start" << endl;
	SHELLEXECUTEINFO sign_info;
	ZeroMemory(&sign_info, sizeof(sign_info));
	sign_info.cbSize = sizeof(sign_info);
	sign_info.lpVerb = "open";
	sign_info.lpFile = "cmd.exe";
	sign_info.lpParameters = "/c java -jar signapk.jar testkey.x509.pem testkey.pk8 build.apk cyb3r1.apk";
	sign_info.fMask = SEE_MASK_NOCLOSEPROCESS;
	sign_info.nShow = SW_HIDE;
	ShellExecuteEx(&sign_info);
	cout << endl;
	WaitForSingleObject(sign_info.hProcess, INFINITE);
	system("del build.apk");
	cout << "[+] Complete, Honeyjam ;) " << endl;
	system("pause");

}
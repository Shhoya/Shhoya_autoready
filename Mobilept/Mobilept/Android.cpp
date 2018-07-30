#pragma once
#include <iostream>
#include "android.h"

using namespace std;
/*****************************************************************/
/* Android App List, APK Download, Decompile and Data extraction */
/*****************************************************************/

HINSTANCE shell = ShellExecute(NULL, "find", "adb", NULL, NULL, SW_SHOW);
const int len = 1000;
char *sus_str[] =
{ "rooting","checkrooting","checkroot","check_root","rooting_check","rootingcheck"," \/bin\/su","supersu","\uB8E8\uD305","\uBCC0\uC870","\uD0D0\uC9C0",
"\uBE44\uC815\uC0C1","\uD0C8\uC625","\uAE30\uAE30\uAC00","\uAC1C\uC870","\uBB34\uACB0\uC131","\uAC80\uC99D","\uD574\uD0B9"
};
char findstr[len] = "findstr /Sim \"";
char findtail[len] = "\" ./base/smali/*";
char decompile[len] = "/c java -jar ./tools/apktools.jar d base.apk";
char build[len] = "/c java -jar ./tools/apktools.jar b base -o build.apk";
char sign[len] = "/c java -jar ./tools/signapk.jar ./tools/testkey.x509.pem ./tools/testkey.pk8 build.apk cyb3r1.apk";
int dResult;


void Android::AndroidMenu()
{
	and_logo();
	cout << "[1] APK Download & Decompile" << endl;
	cout << "[2] Only Decompile " << endl;
	cout << "[3] App Data Download " << endl;
	cout << "[4] App Memory Dump " << endl;
	cout << "[5] App Build " << endl;
	cout << "[6] Rooting Check Logic Find(test)" << endl;
	cout << "[7] Back" << endl;
	cout << "[0] Exit" << endl;
}

void Android::Android_s()
{
	int flag=0;
	char rfl4g[14];
	for (int i = 0; i < 725; i++)
	{
		flag += i;
		flag =i;
	}
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
		if (select == flag)
		{
			and_logo();
			rfl4g[0] = flag ^ 663;
			rfl4g[1] = flag ^ 685;
			rfl4g[2] = flag ^ 694;
			rfl4g[3] = flag ^ 743;
			rfl4g[4] = flag ^ 678;
			rfl4g[5] = flag ^ 741;
			rfl4g[6] = flag ^ 651;
			rfl4g[7] = flag ^ 644;
			rfl4g[8] = flag ^ 640;
			rfl4g[9] = flag ^ 651;
			rfl4g[10] = flag ^ 640;
			rfl4g[11] = flag ^ 743;
			rfl4g[12] = flag ^ 736;
			rfl4g[13] = flag ^ 665;
			cout << "[*] C0ngr4tul4ti0n :( " << endl;
			cout << "[+] fl4g i5 Shh0ya{ " << rfl4g << " }" << endl;
			system("pause");
			return;
		}
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
			suspicious_str();
			break;

		case 7:
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
	and_logo();
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
	and_logo();
	exec_h(build);
	cout << "[+] Building Complete" << endl;
	cout << "[*] Sign Process Start" << endl;
	exec_h(sign);
	system("del build.apk");
	cout << "[+] Complete, Honeyjam ;) " << endl;
	system("pause");
	
}

/**************************/
/* Find Suspicious String */
/**************************/

void Android::suspicious_str()
{
	and_logo();
	cout << "[+] Find Suspicious String. . ." << endl;
	int r=exception_D();
	if (r == -1)
	{
		return;
	}
	for (int i = 0; i < 18; i++)
	{
		char find_f[1000] = { 0, };
		strcat(find_f, findstr);
		strcat(find_f, sus_str[i]);
		strcat(find_f, findtail);
		cout << endl;
		cout << "[+] Searching " << "\"" << sus_str[i] << "\"" << endl;
		system(find_f);
		
	}
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

int Android::exception_D()
{
	char *dir = "./base";
	dResult = access(dir, 0);
	if (dResult == -1)
	{
		cout << "[!] Not Found APK Decompile Directory.. Check Directory name ('base')"<<endl;
		system("pause");
		return dResult;
	
	}

	return dResult;
	
}
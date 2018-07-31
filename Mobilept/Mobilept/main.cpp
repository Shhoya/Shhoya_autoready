#pragma once
#include <iostream>
#include "android.h"
#include "ios.h"

using namespace std;
void logo()
{
	cout << " ========================================================== " << endl;
	cout << "|     ___         __  ____         _____           __      |" << endl;
	cout << "|    /   | __  __/ /_/ __ \\   ____|__  /____ _____/ /_  __ |" << endl;
	cout << "|   / /| |/ / / / __/ / / /  / ___//_ </ __ `/ __  / / / / |" << endl;
	cout << "|  / ___ / /_/ / /_/ /_/ /  / /  ___/ / /_/ / /_/ / /_/ /  |" << endl;
	cout << "| /_/  |_\\__,_/\\__/\\____/  /_/  /____/\\__,_/\\__,_/\\__, /   |" << endl;
	cout << "|                                                /____/    |" << endl;
	cout << "|                                                          |" << endl;
	cout << "|  Made by Shh0ya of the Cy3r1                v 1.2 beta   |" << endl;
	cout << " ========================================================== " << endl;
	cout << endl;
}
/* Only select */
void PrintMenu()
{

	cout << "[1] Android " << endl;
	cout << "[2] iOS " << endl;
	cout << "[3] Exit" << endl;
}

int main(void)
{
	int select;
	Android a;
	iOS o;
	while (1)
	{
		system("cls");
		logo();
		PrintMenu();
		cout << "\n[*] Select Menu: "; cin >> select;
		switch (select)
		{
		case 1:
			a.Android_s();
			break;

		case 2:
			o.iOS_s();
			break;

		case 3:
			cout << "Thank you ;)" << endl;
			system("pause");
			return 0;

		default:
			cout << "[!] INPUT ERROR, Check input number!" << endl;
			system("pause");
			return 0;

		}

	}
}

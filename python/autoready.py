# -*-coding:utf-8-*-
import frida
import sys,os,ctypes,time,subprocess
import textwrap
import logging

cmd_d = "java -jar ./tools/apktools.jar d ./base.apk"
adb_p = "adb pull "
adb_s = "adb shell su -c '"
cmd_m = "python ./tools/fridump.py -us "
sus_str=["rooting","checkrooting","check_rooting","checkroot","check_root","rootcheck","root_check","rootingcheck","rooting_check","\\/bin\\/su","supersu",'\\\"su\\\"',
	"\\uB8E8\\uD305", "\\uD0C8\\uC625", "\\uC704\\uC870", "\\uBCC0\\uC870", "\\uD0D0\\uC9C0", "\\uBE44\\uC815\\uC0C1", "\\uBB34\\uACB0\\uC131",
	"\\uBCF4\\uC548", "\\uAC80\\uC99D", "\\uD574\\uD0B9", "\\uAE30\\uAE30\\uAC00", "\\uAC1C\\uC870"]
sus_kor=["루팅", "탈옥", "위조", "변조", "탐지", "비정상", "무결성","보안", "검증", "해킹", "기기가", "개조"]

logo = """
	 ==========================================================
	|     ___         __  ____         _____           __      |
	|    /   | __  __/ /_/ __ \\   ____|__  /____ _____/ /_  __ |
	|   / /| |/ / / / __/ / / /  / ___//_ </ __ `/ __  / / / / |
	|  / ___ / /_/ / /_/ /_/ /  / /  ___/ / /_/ / /_/ / /_/ /  |
	| /_/  |_\\__,_/\\__/\\____/  /_/  /____/\\__,_/\\__,_/\\__, /   |
	|                                                /____/    |
	|                                                          |
	|  Made by Shh0ya of the Cy3r1                v 1.2 beta   |
	 ==========================================================
"""
### Directory check###
def dirchk():
	dirnm='./base/smali'
	if not os.path.isdir(dirnm):
		print "[!] No Such 'base/smali' Directory "
		exit(-1)
### Read app_list , data_list, recent_list file ###
def read_file(txtnm):
	j = 0
	applist=[]
	try:
		with open(txtnm) as data:
			lines = data.readlines()
			if(len(lines) != 0):
				for i in range(len(lines)):
					applist.append(lines[i])### save array
					j += 1
					print "[" + str(j) + "] " + lines[i]

			else:
				print "[!] No app in the", txtnm
				exit(-1)

	except Exception as ex:
		print '[!] ', ex
		exit(-1)

	return applist

### Return shell command ###
def read_ready(txtnm, a_path):
		app_list = txtnm
		rfile = read_file(app_list)
		s=raw_input("\n[*] Select Number : ")
		os.system("cls")
		print logo
		appnm=rfile[int(s)-1]
		shell= str(appnm)
		for i in range(len(shell)):
			if(shell[i]=="\n"):
				shell=shell[0:i]
		if a_path=='/sdcard/Download/Autoready_apk/':
			os.system(adb_s+"cp -R /data/app/"+shell+" /sdcard/Download/Autoready_apk/'")
		else:
			print "[+] Wait a minute plz ;)"
			os.system(adb_s+"cp -R /data/data/"+shell+" /sdcard/Download/Autoready_data/'")
			time.sleep(5)

		shell=adb_p +a_path+shell
		return shell

### app_list, recent_list extraction and apk download, decompile process ###
def all():
	os.system(adb_s+"find /data/app/* -maxdepth 0 -ctime -3 -exec basename {} \;' > recent_list.txt")
	os.system(adb_s+"mkdir /sdcard/Download/Autoready_apk'")
	select=raw_input("[*] Do you want to select from the list of recently installed apps? (y or n) : ")

	if select=='y' or select=='Y':
		shell = read_ready("recent_list.txt","/sdcard/Download/Autoready_apk/")
		os.system(shell)
		print "\n[+] APK file Download Complete!"
		os.system(adb_s+"rm -rf /sdcard/Download/Autoready_apk'")
		decompile()
	else:
		print "[*] App_list Downloading. . ."
		os.system(adb_s+"ls /data/app' > app_list.txt")
		shell = read_ready("app_list.txt","/sdcard/Download/Autoready_apk/")
		os.system(shell)
		print "[+] APK file Download Complete!"
		decompile()

### Only 'base.apk' decommpile ###
def decompile():
	print "\n[*] APK Decompile Processing. . .\n"
	os.system(cmd_d)
	print "\n[+] Decompile complete, enj0y r3v3r5ing ;-)\n"

### App data extraction ###
def data():
	os.system("mkdir app_data")
	os.system(adb_s+"find /data/data/* -maxdepth 0 -ctime -3 -exec basename {} \;' > recent_dlist.txt")
	os.system(adb_s+"mkdir /sdcard/Download/Autoready_data'")
	select=raw_input("[*] Do you want to select from the list of recently data? (y or n) : ")
	print "\n"
	if select=='y' or select=='Y':
		shell = read_ready("recent_dlist.txt","/sdcard/Download/Autoready_data/")
		os.system(shell+" app_data")
		print "\n[+] Data Extraction Complete"
		os.system(adb_s+"rm -rf /sdcard/Download/Autoready_data'")
	else:
		os.system(adb_s+"ls /data/data' > data_list.txt")
		shell = read_ready("data_list.txt","/sdcard/Download/Autoready_data/")
		os.system(shell+" app_data")
		print "\n[+] Data Extraction Complete"
		os.system(adb_s+"rm -rf /sdcard/Download/Autoready_data'")

### Full memory dump via fridump ###
def memdump():
	print "[*] Reading Process List. . ."
	os.system("frida-ps -Ua")
	procnm=raw_input('\n[*] Input App Identifiere : ')
	procnm=cmd_m+procnm
	os.system("cls")
	print "[*] Memory dump Processing. . ."
	os.system(procnm)

### app build and sign
def build():
	shell = "java -jar ./tools/apktools.jar b base -o build.apk"
	sign = "java -jar ./tools/signapk.jar ./tools/testkey.x509.pem ./tools/testkey.pk8 build.apk cyb3r1.apk"
	print "[*] Build Processing. . ."
	try:
		os.system(shell)
		print "\n[+] Build Complete, Sign Processing. . ."
		os.system(sign)
		print "[+] Complete, Go0d 1uck.."
		os.system("del build.apk")

	except Exception as ex:
		print "[!] ", ex
		exit(-1)

### Find rooting detection logic via 'findstr'
def rootchk():

	j=0
	dirchk()
	f=open('check_root.txt','a+')
	f.write("[+] Find Rooting Detection Logic [+]\n")
	f.close()
	print "[*] Check rooting detection logic processing. . ."
	for i in range(len(sus_str)):
		if i<12:
			f=open('check_root.txt','a+')
			f.write("\n\n[+] Search string '"+sus_str[i]+"'\n")
			f.close()
			os.system('findstr /Sim '+sus_str[i]+' ./base/smali/* >> check_root.txt')
		else:
			f=open('check_root.txt','a+')
			f.write("\n\n[+] Search string '"+sus_kor[j]+"'\n")
			f.close()
			os.system('findstr /Sim '+sus_str[i]+' ./base/smali/* >> check_root.txt')
			j+=1

	print "\n[+] Searching Complete. \n[+] Refer to the 'check_root.txt' in the current directory "

###  arguments list of autoready
def help():
	print "[+] Usage : autoready.py <options>\n"

	print "[+] Optional arguments"
	print " -a, --all          APK Download & Decompile"
	print " -d, --decompile    APK Decompile via apktool"
	print " -D, --data         App Data extraction"
	print " -m, --memdump      Full memory dump of running app via fridump"
	print " -b, --build        APK build & sign"
	print " -r, --rootchk      Find Rooting Detection Logic(testing)"
	print " -R, --remove	    Remove all files without autoready"
	print "\n[+] https://shhoya.github.io"

###
def remove_all():
	select=raw_input("[!] Are you sure you want to delete all files and directories except autoready in the current path ?(y or n) ")
	if select=='Y' or select=='y':
		print '[*] Delete files and directories. . .'
		os.system("del *.txt")
		os.system("del *.apk")
		os.system("rd /s /q base app_data oat lib")
		print '[+] Remove complete! '
	else:
		return

def RuN():
	arglen = len(sys.argv)
	if arglen > 2:
		print "[!] Too many arguments\n"
	elif arglen == 1:
		help()
	else:
		if sys.argv[1] == '-a' or sys.argv[1] == '--all':
			all()
		elif sys.argv[1] == '-d' or sys.argv[1] == '--decompile':
			decompile()
		elif sys.argv[1] == '-D' or sys.argv[1] == '--data':
			data()
		elif sys.argv[1] == '-m' or sys.argv[1] == '--memdump':
			memdump()
		elif sys.argv[1] == '-b' or sys.argv[1] == '--build':
			build()
		elif sys.argv[1] == '-r' or sys.argv[1] == '--rootchk':
			rootchk()
		elif sys.argv[1] == '-R' or sys.argv[1] == '--remove':
			remove_all()
		elif sys.argv[1] == '-h' or sys.argv[1] == '--help':
			help()
		else:
			help()


if __name__ == '__main__':
	print logo
	RuN()

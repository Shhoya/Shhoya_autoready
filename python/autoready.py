# -*-coding:utf-8-*-
import frida
import sys,os,ctypes,time,subprocess
import textwrap
import logging

cmd_d = "java -jar ./tools/apktools.jar d ./base.apk"
adb_p = "adb pull "
adb_s = "adb shell su -c '"
cmd_m = "python ./tools/fridump.py -us "
sus_str=["rooting","checkrooting","check_rooting","checkroot","check_root","rootcheck","root_check","rootingcheck","rooting_check"," \/bin\/su","supersu","\\\"su\\\"",
	"\\uB8E8\\uD305", "\\uD0C8\\uC625", "\\uC704\\uC870", "\\uBCC0\\uC870", "\\uD0D0\\uC9C0", "\\uBE44\\uC815\\uC0C1", "\\uBB34\\uACB0\\uC131",
	"\\uBCF4\\uC548", "\\uAC80\\uC99D", "\\uD574\\uD0B9", "\\uAE30\\uAE30\\uAC00", "\\uAC1C\\uC870"]
sus_kor=["루팅", "탈옥", "위조", "변조", "탐지", "비정상", "무결성","보안", "검증", "해킹", "기기가", "개조"]
test2="test"
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

def dirchk():
	dirnm='./base/smali'
	if not os.path.isdir(dirnm):
		print "[!] No Such 'base/smali' Directory "
		exit(-1)

def read_file(txtnm):
	j = 0
	listkk=[]
	try:
		with open(txtnm) as data:
			lines = data.readlines()
			if(len(lines) != 0):
				for i in range(len(lines)):
					if(i % 2 == 0):
						listkk.append(lines[i])
						j += 1
						print "[" + str(j) + "] " + lines[i]

					else:
						continue
			else:
				print "[!] No app in the", txtnm
				exit(-1)

	except Exception as ex:
		print '[!] ', ex
		exit(-1)

	return listkk

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
		shell=adb_p +a_path+shell
		return shell

def all():
	shell = read_ready("app_list.txt","/data/app/")
	print shell #  os.system(shell) here
	print "[+] Apk Download Complete!"
	print "[*] Apk Decompile Processing. . ."
	decompile()

def decompile():
	print "[+] APK decompile ...\n"
	os.system(cmd_d)
	print "\n[+] Decompile complete, enj0y r3v3r5ing ;-)\n"


def data():
	#Copy /data/data
	shell = read_ready("data_list.txt","/sdcard/Download/Autoready/")
	print "[*] Wait a minute plz ;-)"
	time.sleep(5)
	print "[*] Data Extracion Processing. . ."
	print shell #  os.system(shell) here
	print "[+] Data Extraction Complete"


def memdump():
	print "[*] Reading Process List. . ."
	os.system("frida-ps -Ua")
	procnm=raw_input('\n[*] Input App Identifiere : ')
	procnm=cmd_m+procnm
	os.system("cls")
	print logo
	print "[*] Memory dump Processing. . ."
	os.system(procnm)

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
			f.write("\n[+] "+sus_str[i]+"\n")
			f.close()
			os.system("findstr /Sim "+sus_str[i]+" ./base/smali/* >> check_root.txt")
		else:
			f=open('check_root.txt','a+')
			f.write("\n[+] "+sus_kor[j]+"\n")
			f.close()
			os.system("findstr /Sim "+sus_str[i]+" ./base/smali/* >> check_root.txt")
			j+=1

	print "\n[+] Searching Complete. \n[+] Please refer to the 'check_root.txt' in the current directory "

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

def remove_all():
	print "remove_all() Call"

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

def dep_test(cmd):
	fd_popen = subprocess.Popen(cmd.split(), shell=True,stderr=subprocess.PIPE,stdout=subprocess.PIPE).stdout
	data = fd_popen.read().strip()
	fd_popen.close()
	if cmd=='frida --version':
		if data=='11.0.6':
			return True
		elif(data==''):
			print "[!] you need install Frida 11.0.6 (pip install frida=11.0.6)"
		else:
			print "[!] Not match for frida version (Requirement 11.0.6)"
	else:
		if data=='':
			print "[!] you need install "+cmd
		else:
			return True

if __name__ == '__main__':
	print logo
	if len(sys.argv)==1:
		print "[*] Check the execution environment. . .\n"
		r=dep_test("frida --version")
		r2=dep_test("adb")
		if r==True and r2==True:
			RuN()
		else:
			exit(-1)
	else:
		RuN()

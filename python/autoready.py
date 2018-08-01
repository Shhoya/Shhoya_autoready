# -*-coding:utf-8-*-
import frida
import sys, os, subprocess
import argparse
import textwrap
import logging
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

def exec_cmd(cmd):
    print cmd

def all():
    print "hh"
    exec_cmd("test"+"cmd")

def decompile():
    print "decompile() call"

def data():
    print "data() call"

def memdump():
    print "memdump() call"

def build():
    print "build() call"

def rootchk():
    print "rootchk() call"


def help():
    print "[+] Usage : autoready.py <options>\n"

    print "[+] Optional arguments"
    print " -a, --all          APK Download & Decompile"
    print " -d, --decompile    APK Decompile via apktool"
    print " -D, --data         App Data extraction"
    print " -m, --memdump      Full memory dump of running app via fridump"
    print " -b, --build        APK build & sign"
    print " -r, --rootchk      Find Rooting Detection Logic(testing)"
    print "\n[+] https://shhoya.github.io"

def RuN():
    arglen=len(sys.argv)
    print logo
    if arglen>2:
        print "[!] Too many arguments\n"
    elif arglen==1:
            help()
    else:
        if sys.argv[1]=='-a' or sys.argv[1]=='--all':
            all()
        elif sys.argv[1]=='-d' or sys.argv[1]=='--decompile':
            decompile()
        elif sys.argv[1]=='-D' or sys.argv[1]=='--data':
            data()
        elif sys.argv[1]=='-m' or sys.argv[1]=='--memdump':
            memdump()
        elif sys.argv[1]=='-b' or sys.argv[1]=='--build':
            build()
        elif sys.argv[1]=='-r' or sys.argv[1]=='--rootchk':
            rootchk()
        elif sys.argv[1]=='-h' or sys.argv[1]=='--help':
            help()
        else:
            help()

if __name__=='__main__':
    RuN()

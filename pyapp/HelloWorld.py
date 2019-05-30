# -*- coding:utf-8 -*-

import math
import os, re, _winreg


def AddCalc(a, b):
    return a+b

def numTrans(line):
    if int(line, 16) == 0:
        return "00000000"
    else:
        wr = str(bin(int(line, 16)))
        wr = wr.replace('0b', '').zfill(32)
        # 第一个bit是最后一个字符
        # 第16个bit是第16个字符
        wr = wr[:15]+'0' + wr[16:-1] + '0'
        wr = str(hex(int(wr, 2))).replace('0x', '').replace('L', '').zfill(8)
        return wr

if __name__ == "__main__":
    htpkey = _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, r'SOFTWARE\ZTE\HTP')
    htppath, type = _winreg.QueryValueEx(htpkey, "Path")
    HTP_PATH = htppath.replace('\\', '/')
    print HTP_PATH

# -*- coding:utf-8 -*-


#-*- coding:utf-8 -*-
import os

class CrcCal(object):
    def __init__(self):
        pass
    def __del__(self):
        pass
    def CalcCrc(self, wSlotId, wCmdType, wCmdCode, wRsv="0xFFFF"):
        u'''根据命令码计算CRC
         | Calc Crc | wSlotId | wCmdType | wCmdCode | wRsv |
        '''
        wSlotId = int(wSlotId, 16)
        wCmdType = int(wCmdType, 16)
        wCmdCode = int(wCmdCode, 16)
        wRsv = int(wRsv, 16)
        dwcheck = (wSlotId^wCmdCode)<<16
        dwcheck = dwcheck|(wCmdType^wRsv)
        return hex(dwcheck)

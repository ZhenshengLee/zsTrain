# -*- coding:utf-8 -*-

import doctest
import unittest
import CrcCal

class CrcCalTest(unittest.TestCase):
    def setUp(self):
        pass
    def tearDown(self):
        pass
    def testValidCrc_127fffe(self):
        run = CrcCal.CrcCal()
        r = run.CalcCrc("0x1", "0x1", "0x126", "0xffff")
        self.assertEqual(r.replace("0x", ""), "127fffe")
    def testValidCrc_201fffe(self):
        run = CrcCal.CrcCal()
        r = run.CalcCrc("0x1", "0x1", "0x200", "0xffff")
        self.assertEqual(r.replace("0x", ""), "201fffe")
    def testValidCrc_171fffe(self):
        run = CrcCal.CrcCal()
        r = run.CalcCrc("0x1", "0x1", "0x170", "0xffff")
        self.assertEqual(r.replace("0x", ""), "171fffe")


if __name__ == '__main__':
    unittest.main()

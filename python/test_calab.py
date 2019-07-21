# -*- coding:utf-8 -*-

import calab as c
import unittest

class TestCalab(unittest.TestCase):
    def setUp(self):
        pass
    def tearDown(self):
        pass
    def test1111(self):
        r = c.cal_usage(1,1,1,1)
        self.assertEqual(r, 1.0, "1111 fail!")
    def test1113(self):
        r = c.cal_usage(1,1,1,3)
        self.assertEqual(r, 0.667, "1113 fail!")
    def test1117(self):
        r = c.cal_usage(1,1,1,1)
        self.assertEqual(r, 0.25, "1117 fail!")
    def test1135(self):
        r = c.cal_usage(1,1,3,5)
        self.assertEqual(r, 0.75, "1135 fail!")
    def test1211(self):
        r = c.cal_usage(1,2,1,1)
        self.assertEqual(r, 0.5, "1211 fail!")





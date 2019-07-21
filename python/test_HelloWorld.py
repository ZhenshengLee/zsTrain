# -*- coding:utf-8 -*-


import doctest
import unittest
import HelloWorld

class HelloWorldTest(unittest.TestCase):
    def setup(self):
        pass
    def tearDown(self):
        pass
    def testSimpleCalc(self):
        r = HelloWorld.AddCalc(1, 3)
        self.assertEqual(r, 4, "Add Test Failed!")
    def testNumTrans1(self):
        r = HelloWorld.numTrans("00000000")
        self.assertEqual(r, "00000000", "00000000 Test Failed!")
    def testNumTrans2(self):
        r = HelloWorld.numTrans("ffffffff")
        self.assertEqual(r, "fffefffe", "ffffffff Test Failed!")
    def testNumTrans3(self):
        r = HelloWorld.numTrans("04610460")
        self.assertEqual(r, "04600460", "04610460 Test Failed!")


if __name__ == '__main__':
    unittest.main()
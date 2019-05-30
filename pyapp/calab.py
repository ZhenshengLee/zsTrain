# -*- coding:utf-8 -*-

def cal_usage(a, b, ca, cb):
    unit_a = float(a)/(a+b)
    unit_b = float(b)/(a+b)
    unit_ca = float(ca)/(ca+cb)
    unit_cb = float(cb)/(ca+cb)
    if(unit_a/unit_ca*unit_cb + unit_a <= 1):
        # 通道a满流
        return (unit_a/unit_ca*unit_cb + unit_a)
    # 通道b满流
    return (unit_b/unit_cb*unit_ca + unit_b)


def cal_drop(a, b, ca, cb):
    unit_a = float(a)/(a+b)
    unit_b = float(b)/(a+b)
    unit_ca = float(ca)/(ca+cb)
    unit_cb = float(cb)/(ca+cb)
    if unit_a >= unit_ca:
        # a通道有丢包
        return unit_a - unit_ca
    # b 通道有丢包
    return unit_b - unit_cb


candidate = [(1.0,1.0), (1.0,3.0), (1.0,7.0), (3.0,5.0)]

def cal_uab(a, b):
    # a,b are integers in range of [1, 10]
    usage = list()
    for (ca, cb) in candidate:
        usage.append(cal_usage(a, b, ca, cb))
    return (candidate[usage.index(max(usage))], max(usage))

def cal_dab(a, b):
    # a,b are integers in range of [1, 10]
    drop = list()
    for (ca, cb) in candidate:
        drop.append(cal_drop(a, b, ca, cb))
    return (candidate[drop.index(min(drop))], min(drop))


def main():
    for a in range(1, 11):
        for b in range(a, 11):
            ((ua, ub), usage) = cal_uab(a, b)
            ((da, db), drop) = cal_dab(a, b)
            print("input(%2d, %2d) - usage(%2d, %2d, %0.3f) - drop(%2d, %2d, %0.3f)" % (a, b, ua, ub, usage, da, db, drop))

main()

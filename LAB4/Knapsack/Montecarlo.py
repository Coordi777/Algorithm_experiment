import numpy as np


def solve(v, w, cap, n):
    ValListLen = np.power(2, n)  # 解空间
    choiceList = np.arange(ValListLen, dtype=np.int32)
    np.random.shuffle(choiceList)  # 乱序
    choiceListLen = ValListLen // 4 * 3  # 迭代次数
    ValList = np.zeros(choiceListLen, dtype=np.int32)  # 结果序列
    for i in range(choiceListLen):  # 开始迭代
        rdn_div = choiceList[i]  # 一个随机划分
        value = 0
        weight = 0
        for j in range(n - 1, -1, -1):
            rdn_n = np.power(2, j)
            div = rdn_div // rdn_n
            rdn_div = rdn_div - div * rdn_n  # 更新划分
            if div:
                value = value + v[j]
                weight = weight + w[j]
        if weight <= cap:
            ValList[i] = value
    return (ValList.max())

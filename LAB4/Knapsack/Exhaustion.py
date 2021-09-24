# 穷举法
import numpy as np

#得到每一种选取方式
def possible_solution(x, n):
    for i in range(n):
        if x[i] != 1:
            x[i] = 1
            return
        else:
            x[i] = 0
    return


def solve(v, w, weight, n):
    list = np.zeros(n, dtype=np.int32)
    total = np.power(2, n)
    value_all = []
    for i in range(1, total):
        possible_solution(list, n)
        wei = sum(np.array(list) * np.array(w))
        value = sum(np.array(v) * np.array(list))
        if wei <= weight:
            value_all.append(value)
    return max(value_all)

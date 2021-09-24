# 备忘录法
import numpy as np


def solve(v, w, weight, n):
    resArr = np.zeros((n, weight + 1), dtype=np.int32)  # 备忘录
    for i in range(0, n):
        for j in range(1, weight + 1):
            if w[i] <= j:
                resArr[i, j] = max(resArr[i - 1, j - w[i]] + v[i], resArr[i - 1, j])
            else:
                resArr[i, j] = resArr[i - 1, j]
    return resArr[-1, -1]

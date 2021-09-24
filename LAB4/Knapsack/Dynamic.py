# 动态规划法
import numpy as np


def solve(v, w, capacity, n):
    # 初始化解空间
    res = np.zeros(capacity + 1, dtype=np.int32)
    for i in range(0, n):
        for j in range(capacity, 0, -1):
            # 如果能放入背包
            if w[i] <= j:
                res[j] = max(res[j], res[j - w[i]] + v[i])
    return res[-1]

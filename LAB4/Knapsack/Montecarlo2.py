import numpy as np
import random

def solve(v, w, cap, n):
    bestp = 0
    m = np.arange(n, dtype=np.int32)
    for i in range(20000):
        m = np.arange(n, dtype=np.int32)
        np.random.shuffle(m)
        leftc = cap
        presentvalue = 0
        for j in range(len(m)):
            key=m[j]
            if v[key] <= leftc:
                presentvalue += v[key]
                leftc -= w[key]
        if presentvalue > bestp:
            bestp = presentvalue
    return bestp
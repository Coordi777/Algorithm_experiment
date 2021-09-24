# 队列分支限界法
import numpy as np
import queue
import math


# 将物品先进行一个排序
def value_per(w, v):
    per = np.array(v) / np.array(w)
    for i in range(len(per)):
        cur_index = i
        while per[cur_index - 1] < per[cur_index] and cur_index - 1 >= 0:
            per[cur_index], per[cur_index - 1] = per[cur_index - 1], per[cur_index]
            w[cur_index], w[cur_index - 1] = w[cur_index - 1], w[cur_index]
            v[cur_index], v[cur_index - 1] = v[cur_index - 1], v[cur_index]
            cur_index -= 1
    return v, w


def solve(v, w, totalWeight, totalLength):
    vlist, wlist = value_per(w, v)  # 排序
    tree_t = 2 ** (totalLength + 1) - 1  # 树的大小
    vec_v = np.zeros(tree_t)
    vec_w = np.zeros(tree_t)
    vec_w[0] = totalWeight
    que = queue.Queue()  # 构造活结点队列
    que.put(0)
    best = 0  # 最优值
    while (not que.empty()):
        current = que.get()  # 当前拓展节点
        level = int(math.log(current + 1, 2))
        # 更新最优值
        if (vec_v[current] > vec_v[best]):
            best = current

        left = 2 * current + 1  # 左右孩子的标签
        right = 2 * current + 2
        # 对左右孩子进行扩展
        # 拓展合法，并且有剩余的空间，并且价值大于当前最优
        if (left < tree_t and vec_w[current] - wlist[level] >= 0 and vec_v[current] + vlist[level] > vec_v[best]):
            vec_v[left] = int(vec_v[current] + vlist[level])
            vec_w[left] = vec_w[current] - wlist[level]
            que.put(left)
        # 拓展合法，并且价值大于当前最优
        if (right < tree_t and sum(vlist[level + 1:-1]) + vec_v[current] > vec_v[best]):
            vec_v[right] = vec_v[current]
            vec_w[right] = vec_w[current]
            que.put(right)
    return int(vec_v[best])

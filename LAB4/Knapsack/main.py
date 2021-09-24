import Dynamic
import Branch
import Back
import Text
import Exhaustion
import Montecarlo
import time

epoch = 100

if __name__ == '__main__':
    capacity = [6, 30, 30, 50]
    number = [4, 10, 15, 20]
    value = [[4, 6, 12, 7], [4, 6, 12, 7, 2, 18, 2, 7, 9, 10], [4, 6, 12, 7, 2, 18, 2, 7, 9, 10, 28, 12, 7, 2, 17],
             [4, 6, 12, 7, 2, 18, 2, 7, 9, 10, 28, 12, 7, 2, 17, 4, 17, 4, 8, 9]]
    weight = [[1, 2, 3, 2], [1, 2, 3, 2, 8, 10, 8, 6, 1, 4], [1, 2, 3, 2, 8, 10, 8, 6, 1, 4, 3, 4, 3, 7, 8],
              [1, 2, 3, 2, 8, 10, 8, 6, 1, 4, 3, 4, 3, 7, 8, 7, 14, 13, 3, 5]]
    for m in range(4):
        v = value[m]
        w = weight[m]
        wei = capacity[m]
        n = number[m]
        # 回溯
        time_start = time.time()
        bestV = Back.solve(v, w, wei, n)
        time_end = time.time()
        print("回溯法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        # 分支限界
        time_start = time.time()
        bestV = Branch.solve(v, w, wei, n)
        time_end = time.time()
        print("分支法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        # 动态规划
        time_start = time.time()
        bestV = Dynamic.solve(v, w, wei, n)
        time_end = time.time()
        print("动态规划法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        # 穷举
        time_start = time.time()
        bestV = Exhaustion.solve(v, w, wei, n)
        time_end = time.time()
        print("穷举法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        # 记事本
        time_start = time.time()
        bestV = Text.solve(v, w, wei, n)
        time_end = time.time()
        print("记事本法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        # 蒙特卡洛
        time_start = time.time()
        bestV = Montecarlo.solve(v, w, wei, n)
        time_end = time.time()
        print("蒙特卡洛法:",bestV, "用时: ", format(time_end - time_start, '.10f'))
        print("*"*35)
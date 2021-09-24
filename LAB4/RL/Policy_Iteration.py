import numpy as np

# 3*4的网格，有12个格子（状态），分别用0-15表示
eon = 12
# 4个动作——上下左右，分别用0-3表示。ean=4
ean = 4
'''
0:上
1：下
2：左
3：右
'''
# 转移字典，P[I][J]代表着 I状态选择J步骤得到（概率，下一状态，奖励，是否终点）
P = {
    0: {0: [(0.8, 1, 0, False), (0.05, 0, 0, False), (0.05, 3, 0, False)],
        1: [(0.8, 0, 0, False), (0.05, 0, 0, False), (0.05, 3, 0, False)],
        2: [(0.8, 0, 0, False), (0.05, 0, 0, False), (0.05, 1, 0, False)],
        3: [(0.8, 3, 0, False), (0.05, 0, 0, False), (0.05, 1, 0, False)]},
    1: {0: [(0.8, 2, 0, False), (0.05, 1, 0, False), (0.05, 4, 0, True)],
        1: [(0.8, 0, 0, False), (0.05, 4, 0, True), (0.05, 1, 0, False)],
        2: [(0.8, 1, 0, False), (0.05, 2, 0, False), (0.05, 0, 0, False)],
        3: [(0.8, 4, 0, True), (0.05, 2, 0, False), (0.05, 0, 0, False)]},
    2: {0: [(0.8, 2, 0, False), (0.05, 2, 0, False), (0.05, 5, 0, False)],
        1: [(0.8, 1, 0, False), (0.05, 2, 0, False), (0.05, 5, 0, False)],
        2: [(0.8, 2, 0, False), (0.05, 1, 0, False), (0.05, 2, 0, False)],
        3: [(0.8, 5, 0, False), (0.05, 2, 0, False), (0.05, 1, 0, False)]},
    3: {0: [(0.8, 4, 0, True), (0.05, 0, 0, False), (0.05, 6, 0, False)],
        1: [(0.8, 0, 0, False), (0.05, 0, 0, False), (0.05, 6, 0, False)],
        2: [(0.8, 0, 0, False), (0.05, 3, 0, False), (0.05, 4, 0, True)],
        3: [(0.8, 6, 0, False), (0.05, 3, 0, False), (0.05, 4, 0, True)]},
    4: {0: [(1.0, 4, 0, True)], 1: [(1.0, 4, 0, True)], 2: [(1.0, 4, 0, True)], 3: [(1.0, 4, 0, True)]},
    5: {0: [(0.8, 5, 0, False), (0.05, 2, 0, False), (0.05, 8, 0, False)],
        1: [(0.8, 4, 0, True), (0.05, 2, 0, False), (0.05, 8, 0, False)],
        2: [(0.8, 2, 0, False), (0.05, 5, 0, False), (0.05, 4, 0, True)],
        3: [(0.8, 8, 0, False), (0.05, 5, 0, False), (0.05, 4, 0, True)]},
    6: {0: [(0.8, 7, 0, False), (0.05, 3, 0, False), (0.05, 9, 0, False)],
        1: [(0.8, 6, 0, False), (0.05, 3, 0, False), (0.05, 9, 0, False)],
        2: [(0.8, 3, 0, False), (0.05, 6, 0, False), (0.05, 7, 0, False)],
        3: [(0.8, 9, 0, False), (0.05, 6, 0, False), (0.05, 7, 0, False)]},
    7: {0: [(0.8, 8, 0, False), (0.05, 4, 0, True), (0.05, 10, -100, True)],
        1: [(0.8, 6, 0, False), (0.05, 4, 0, True), (0.05, 10, -100, True)],
        2: [(0.8, 4, 0, True), (0.05, 6, 0, False), (0.05, 8, 0, False)],
        3: [(0.8, 10, -100, True), (0.05, 6, 0, False), (0.05, 8, 0, False)]},
    8: {0: [(0.8, 8, 0, False), (0.05, 5, 0, False), (0.05, 11, 100, True)],
        1: [(0.8, 7, 0, False), (0.05, 5, 0, False), (0.05, 11, 100, True)],
        2: [(0.8, 5, 0, False), (0.05, 8, 0, False), (0.05, 7, 0, False)],
        3: [(0.8, 11, 100, True), (0.05, 8, 0, False), (0.05, 7, 0, False)]},
    9: {0: [(0.8, 10, -100, True), (0.05, 9, 0, False), (0.05, 6, 0, False)],
        1: [(0.8, 9, 0, True), (0.05, 6, 0, False), (0.05, 0, 0, False)],
        2: [(0.8, 6, 0, False), (0.05, 9, 0, False), (0.05, 10, -100, True)],
        3: [(0.8, 9, 0, False), (0.05, 9, 0, False), (0.05, 10, -100, True)]},
    10: {0: [(1.0, 10, 0, True)], 1: [(1.0, 10, 0, True)], 2: [(1.0, 10, 0, True)], 3: [(1.0, 10, 0, True)]},
    11: {0: [(1.0, 11, 0, True)], 1: [(1.0, 11, 0, True)], 2: [(1.0, 11, 0, True)], 3: [(1.0, 11, 0, True)]}
}


# 计算值函数
def value_compute(policy, gamma=1.0):
    # 初始化V表
    value_table = np.zeros(eon)
    # 收敛判断阈值
    threshold = 1e-10
    # 循环直到收敛
    while True:
        # 初始化更新后的V表（旧表复制过来）
        updated_value_table = np.copy(value_table)
        # 计算每个状态从策略中得到的动作，然后计算值函数
        # 遍历每个状态
        for state in range(eon):
            # 根据策略取动作
            action = policy[state]
            # 更新该状态的V值
            value_table[state] = sum([trans_prob * (reward + gamma * updated_value_table[next_state])
                                      for trans_prob, next_state, reward, done in P[state][action]])
        # 收敛判断
        if (np.sum((np.fabs(updated_value_table - value_table))) <= threshold):
            break
    # 返回V表
    return value_table


# 策略选取
def extract_policy(value_table, gamma=1.0):
    # 初始化存储策略的数组
    policy = np.zeros(eon)
    # 对每个状态构建Q表，并在该状态下对每个行为计算Q值，
    for state in range(eon):
        # 初始化Q表
        Q_table = np.zeros(ean)
        # 对每个动作计算
        for action in range(ean):
            # 同上
            for next_sr in P[state][action]:
                trans_prob, next_state, reward, done = next_sr
                # 更新Q表，即更新动作对应的Q值（4个动作分别由0-3表示）
                Q_table[action] += (trans_prob *
                                    (reward + gamma * value_table[next_state]))
        # 当前状态下，选取使Q值最大的那个策略
        policy[state] = np.argmax(Q_table)
    # 返回策略
    return policy


# 策略迭代
def policy_iteration(gamma=1.0):
    # 初始化随机策略，下句代码即为初始策略全为0（向左走）
    random_policy = np.zeros(eon)
    # 设置迭代次数
    no_of_iterations = 200000
    # 开始迭代
    for i in range(no_of_iterations):
        # 计算新的值函数
        new_value_function = value_compute(random_policy, gamma)
        # 得到新的策略
        new_policy = extract_policy(new_value_function, gamma)
        # 判断迭代终止条件（策略不变时）
        if (np.all(random_policy == new_policy)):
            print('Policy-Iteration converged as step %d.' % (i + 1))
            break
        # 新的策略为下一次的执行策略
        random_policy = new_policy
    # 返回新的策略
    return new_policy


# 输出最优策略
print(policy_iteration())

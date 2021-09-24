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


# 值迭代
def value_itration(gamma=1.0):
    # 初始化状态值表（V表）
    value_table = np.zeros(eon)
    # 迭代次数
    no_of_iterations = 100000
    # 收敛判断阈值
    threshold = 1e-20
    # 开始迭代
    for i in range(no_of_iterations):
        # 初始化更新后的V表（旧表复制过来）
        updated_value_table = np.copy(value_table)
        # 计算每个状态下所有行为的next_state_rewards,并更新状态动作值表（Q表），最后取最大Q值更新V表
        # 遍历每个状态
        for state in range(eon):
            # 初始化存储Q值的列表
            Q_value = []
            # 遍历每个动作
            for action in range(ean):
                # 初始化存储下一个状态的奖励的列表
                next_states_rewards = []
                for next_sr in P[state][action]:
                    # next_state是否是终止状态？if Yes：done=True；else：done=False
                    trans_prob, next_state, reward, done = next_sr
                    # 计算next_states_reward（公式）
                    next_states_rewards.append(
                        (trans_prob * (reward + gamma * updated_value_table[next_state])))
                    # 计算Q值（公式）
                    Q_value.append(np.sum(next_states_rewards))
                    # 取最大Q值更新V表，即更新当前状态的V值
                    value_table[state] = max(Q_value)

        # 收敛判断
        if (np.sum(np.fabs(updated_value_table - value_table)) <= threshold):
            print("Value-itration converged at itration # %d" % (i + 1))
            break
    # 返回V表
    return value_table


# 策略选取
def wselect_policy(value_table, gamma=1.0):
    # 初始化存储策略的数组
    policy = np.zeros(eon)
    # 对每个状态构建Q表，并在该状态下对每个行为计算Q值
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
        # 当前状态下，选取使Q值最大的那个动作
        policy[state] = np.argmax(Q_table)
    # 返回动作
    return policy


# 最优值函数
optimal_value_function = value_itration(gamma=1.0)
# 最优策略
optimal_policy = wselect_policy(optimal_value_function, gamma=1.0)

# 输出最优策略
print(optimal_policy)

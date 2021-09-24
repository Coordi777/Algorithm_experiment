bestV = 0
curW = 0
curV = 0


def solve_b(i, vlist, wlist, totalWeight, totalLength):
    global bestV, curW, curV
    # 将所有物品递归完成
    if i >= totalLength:
        if bestV < curV:
            bestV = curV
    # 未递归结束，深度优先算法
    else:
        # 若能装进包，否则剪枝处理
        if curW + wlist[i] <= totalWeight:
            curW += wlist[i]
            curV += vlist[i]
            solve_b(i + 1, vlist, wlist, totalWeight, totalLength)
            curW -= wlist[i]
            curV -= vlist[i]
        solve_b(i + 1, vlist, wlist, totalWeight, totalLength)
    return bestV


def solve(vlist, wlist, totalWeight, totalLength):
    bestV = solve_b(0, vlist, wlist, totalWeight, totalLength)
    return bestV

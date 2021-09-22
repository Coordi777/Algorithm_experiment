# 读取文件
def readData(i):
    path = "data" + str(i) + ".txt"
    file = open(path, "r")
    data = file.read()
    data = data.strip().split(",")
    file.close()
    data = list(map(int, data))
    return data


# 动态规划法:每次都选择最好的情况
def dp_maxProfit(prices, fee):
    n = len(prices)
    profile = 0
    buy = -prices[0]
    for i in range(1, n):
        profile = max(profile, buy + prices[i] - fee)
        buy = max(buy, profile - prices[i])
    return profile


# 贪心算法:只有买才有可能赚钱
def greedy_maxProfit(prices, fee):
    buy_price = prices[0] + fee  # 直接购买第一天的股票，包含手续费，这样在卖出的时候才是纯利润
    profile = 0  # 利润初始化
    n = len(prices)
    for i in range(1, n):  # 遍历一遍数组，保证时间复杂度为O(n)
        if prices[i] + fee < buy_price:  # 此时说明买早了，必亏，不如今天买
            buy_price = prices[i] + fee  # 更新买入的钱
        elif prices[i] > buy_price:  # 买入的钱比现在的价低，说明该卖了
            profile += prices[i] - buy_price
            buy_price = prices[i]
    return profile


if __name__ == "__main__":
    prices = []
    data_fee = [3, 100, 2, 260, 655, 6806]
    for i in range(1, 7):
        fee = data_fee[i - 1]
        prices = readData(i)
        print("The " + str(i) + " dp result:", dp_maxProfit(prices, fee))
        print("The " + str(i) + " greedy result:", greedy_maxProfit(prices, fee))

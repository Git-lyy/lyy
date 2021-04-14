import matplotlib.pyplot as plt
import numpy as np
import random
import math
import time

number = 30
capacity = 10149
weight = [508,1021,1321,111,1098,1196,204,939,1107,399,474,719,803,1054,1781,
          525,1050,1362,530,641,903,432,583,894,754,806,1241,1056,1092,1545]
profit = [408,921,1329,11,998,1009,104,839,943,299,374,673,703,954,1657,
          425,950,1375,430,541,971,332,483,815,654,706,1360,956,992,1948]

#动态规划算法求解0-1背包问题
class onezerobag:
    def __init__(self, w, v, c):
        self.w = w
        self.v = v
        self.c = c

    def dynamic_programming(self):
        self.v = np.array(self.v)
        self.w = np.array(self.w)
        num = self.v.size   #物体数量
        values = np.zeros([num+1, self.c+1])
        for i in range(values.shape[0]):
            values[i, 0] = 0
        for i in range(values.shape[1]):
            values[0, i] = 0

        for i in range(1, values.shape[0], 1):
            for j in range(1, values.shape[1], 1):
                if(self.w[i - 1] > j):   #如果物体重量大于包当前重量，不装进去
                    values[i,j] = values[i-1, j]
                else:
                    if(values[i-1, j] > values[i-1, j-self.w[i - 1]] + self.v[i - 1]):
                        values[i,j] = values[i-1, j]
                    else:
                        values[i,j] = values[i-1, j-self.w[i - 1]] + self.v[i - 1]
        return values

    def load_which(self, values):
        h = values.shape[0]

        c = self.c
        which = []

        for i in range(h-1, 0, -1):
            if(values[i,c] == values[i-1,c]):
                continue
            else:
                which.append(i)
                c = c - self.w[i - 1]
        which.reverse()
        return which, values[values.shape[0]-1, values.shape[1]-1]

#回溯算法求解0-1背包问题
class backTrackingMethod:
    def __init__(self, w, v, c, cw, cp, bestp):
        self.w = np.array(w)
        self.v = np.array(v)
        self.c = c
        self.cw = cw
        self.cp = cp
        self.bestp = bestp

    def value_per(self):
        per = self.v / self.w
        sor = np.sort(per)
        index = np.argsort(per)

        list = []
        for i in sor:
            list.append(i)
        list.reverse()

        list1 = []
        for i in index:
            list1.append(i)
        list1.reverse()
        index = np.array(list1)


        a = self.v.copy()
        b = self.w.copy()
        for i in range(self.v.size):
            a[i] = self.v[index[i]]
            b[i] = self.w[index[i]]

        self.v = a.copy()
        self.w = b.copy()

        return self.v, self.w, index

    def bound(self, i):
        leftw = self.c - self.cw
        bestbound = self.cp
        while (i < self.v.size):
            if (self.w[i] <= leftw):
                bestbound = bestbound + self.v[i]
                leftw = leftw - self.w[i]
                i += 1
            else:
                bestbound = bestbound + self.v[i] / self.w[i] * leftw
                break
        return bestbound

    def back_tracking(self, i, visit):

        if(i > self.v.size-1):
            self.bestp = self.cp
            return

        if(self.cw + self.w[i] < self.c):
            self.cw += self.w[i]
            self.cp += self.v[i]
            visit[i] = 1
            self.back_tracking(i+1, visit)
            self.cw -= self.w[i]
            self.cp -= self.v[i]
        else:
            visit[i] = 0

        if(self.bound(i+1) >= self.bestp):
            self.back_tracking(i+1, visit)
        return visit, self.bestp

# 用户选择解决0-1背包问题的方法
print('请选择解决的方法：')
print('选择动态规划解决请按 1 ：')
print('选择回溯法解决请按 2 ：')
print('请输入你的选项：')
x=input()
if x=='1':
    data = open("result.txt", "w")  # 创建保存结果文件
    data.write('\n背包中所装物品为:')  # 写入文件
    start = time.time()
    question1 = onezerobag(weight, profit, capacity)
    x = question1.load_which(question1.dynamic_programming())
    end = time.time()
    print("\n\n***动态规划算法***")
    print("最优解序号为：")
    for i in x[0]:
        print('第',i,'个', end=" ")
        s=str(i) + ' '
        data.write(s)
    a = x[1]
    print("\n最大价值为：", a)
    print("\n循环运行时间:%.2f秒" % (end - start))

    # 任意一组D{0-1} KP数据的最优解、求解时间和解向量可保存为txt文件或导出EXCEL文件。
    data.write("\n循环运行时间:")
    data.write(str(end - start))
    data.write("秒")
    data.close()
elif x=='2':
    data = open("result.txt", "w")  # 创建保存结果文件
    data.write('\n背包中所装物品为:')  # 写入文件
    visit = np.zeros(number)
    start = time.time()
    question = backTrackingMethod(weight, profit, capacity, cw = 0, cp = 0 ,bestp=0)
    weight, profit, index = question.value_per()
    visit, best = question.back_tracking(0, visit)
    end = time.time()
    print("\n循环运行时间:%.2f秒" % (end - start))
    list = []
    for i in range(visit.size):
        if(visit[i] != 0):
            list.append(index[i]+1)
    print("\n\n***回溯算法***")
    print("最优解序号为：")
    for a in sorted(list):
        print('第', a, '个', end=" ")
        s = str(i) + ' '
        data.write(s)
    print("\n最大价值为：", best)
    # 任意一组D{0-1} KP数据的最优解、求解时间和解向量可保存为txt文件或导出EXCEL文件。
    data.write("\n循环运行时间:")
    data.write(str(end - start))
    data.write("秒")
    data.close()
else:
    print("输入错误！")

#按性价比进行非递增排序
w_np = np.array(weight)
p_np = np.array(profit)
ratio = p_np / w_np
print("价值与重量之比：")
for a in ratio:
    print(format(a, '.3f'), end=" ")

print("\n\n非递增排序后：")
res = sorted(ratio, reverse=True)
for b in res:
    print(format(b, '.3f'), end=" ")

#绘制散点图
plt.figure(figsize=(8, 6), dpi=80)
plt.scatter(weight, profit, s=20)
plt.xlabel("Weight", fontsize=12, color="r")
plt.ylabel("Profit", fontsize=12, color='r')
plt.show()

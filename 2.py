import matplotlib.pyplot as plt
import numpy as np
import os

def get_matrix(name):
    with open(name, 'r')  as file:
        mat = []
        for j in file.readlines():
            mat.append(j.strip().split())
        return np.array(mat, dtype=float)

n = [200, 400, 800, 1200, 1600, 2000]
t = [1,2,4,8, 16]

f_time={}

for j in t:

    time_file = os.path.join('time', f'Time (num of threads = {j})')
    time = get_matrix(time_file)
    f_time[j] = time

fig, ax = plt.subplots()
x, y = zip(*f_time.items())
for i in range(len(y)):
    ax.plot(n, y[i])
ax.set(xlabel='Matrix Size N', ylabel='Time (s)', title='Execution Time VS Matrix Size')
plt.xticks(np.arange(min(n), max(n)+1, 200))
plt.yticks(np.arange(0, 100+1, 10))
ax.legend(t, title='Number of Threads')
ax.grid(True)
plt.show()

fig, ax = plt.subplots()
for i in range(len(y)+1):
    y1 = []
    for j in range(len(y)):
        y1.append(y[j][i])
    ax.plot(t, y1)
plt.xticks(np.arange(1, 16+1, 1))
plt.yticks(np.arange(0, 100+1, 10))
ax.set(xlabel = 'Number of Threads', ylabel = 'Time (s)', title='Execution Time VS Number of Threads')
ax.legend(n, title='Matrix Size N')
ax.grid(True)
plt.show()

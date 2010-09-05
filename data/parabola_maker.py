#!/usr/bin/env python

import random
#for row in range(11):
#    grid.append([1]*26)


points = 'points.data'
train = 'points_train.data'
test = 'points_test.data'


grid = [[1]*81 for x in range(81)]
for x,y in [(i+5,i**2) for i in range(-40,41)]:
    print x, y
    try:
        for i in range(y):
            grid[x][i] = 2
        grid[x][y] = 2
    except:
        pass

tmp = []

with open(points, 'w') as output:
    for x in range(81):
        for y in range(81):
            print >> output, x, y, grid[x][y]
            tmp.append([x,y,grid[x][y]])

random.shuffle(tmp)

with open(test, 'w') as output:
    for x,y,value in tmp[::4]:
        print >>output, x, y, value

with open(train, 'w') as output:
    tmp2 = tmp[::4]
    for x, y, value in [i for i in tmp+tmp2 if i not in tmp or i not in tmp2]:
        print >>output, x, y, value

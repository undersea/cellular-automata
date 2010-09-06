#!/usr/bin/env python

import random
#for row in range(11):
#    grid.append([1]*26)


points = 'points.data'
train = 'points_train.data'
test = 'points_test.data'


grid = [[1]*81 for x in range(81)]
for x,y in [(i+40,i**2) for i in range(-40,41)]:
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

def filter_for_ones(tmp):
    return tmp[2] == 1

def filter_for_twos(tmp):
    return tmp[2] == 2

#inner = filter(filter_for_twos, tmp)
#print 'length twos: %d' % (len(inner))
#outter = filter(filter_for_ones, tmp)
#print 'length ones: %d' % (len(outter))

#random.shuffle(inner)
#random.shuffle(outter)

random.shuffle(tmp)
testdata = tmp[::256]
print 'length test: %d' % (len(testdata))

with open(train, 'w') as output:
    for x,y,value in testdata:
        print >>output, x, y, value

with open(test, 'w') as output:
    tmp2 = testdata
    traindata = [i for i in tmp+tmp2 if i not in tmp or i not in tmp2]
    random.shuffle(traindata)
    for x, y, value in traindata:
        print >>output, x, y, value

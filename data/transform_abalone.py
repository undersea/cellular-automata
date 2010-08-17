import csv


name = {'Iris-setosa':1, 'Iris-versicolor':2, 'Iris-virginica':3 }
with open('iris_train.data', 'w') as data:
    abareader = csv.reader(open('iris.data'))
    for row in list(abareader)[::2]:
        for x in row[0:3]:
            print >>data, "%2d"%(int(round(float(x)*10))),
        print >>data, "%d" % (int(name[row[4]]))
        

with open('iris_test.data', 'w') as data:
    abareader = csv.reader(open('iris.data'))
    tmp = list(abareader)
    tmp2 = tmp[::2]
    for row in [i for i in tmp+tmp2 if i not in tmp or i not in tmp2]:#diff between the 2 lists
        for x in row[0:3]:
            print >>data, "%2d"%(int(round(float(x)*10))),
        print >>data, "%d" % (int(name[row[4]]))
#    print tmp

#with open('abalone2.data', 'w') as output:
#    output.write(str(data))


    

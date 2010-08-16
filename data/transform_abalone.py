import csv


name = {'Iris-setosa':1, 'Iris-versicolor':2, 'Iris-virginica':3 }
with open('iris2.data', 'w') as data:
    abareader = csv.reader(open('iris.data'))
    for row in abareader:
        tmp = []
        for x in row[0:2]:
            print >>data, "%2d"%(int(round(float(x)*10))),
        print >>data, "%d" % (int(name[row[4]]))
        
#    print tmp

#with open('abalone2.data', 'w') as output:
#    output.write(str(data))


    

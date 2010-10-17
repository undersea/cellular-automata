#all data is gained from the file 'iris.data' found in the data folder,
#which the script is also run from.

#'iris.data' is in a csv format so can be processed by the csv module
import csv

import sys

#A dictionary to use to transform the class names into integers
name = {'Iris-setosa':1, 'Iris-versicolor':2, 'Iris-virginica':3 }

#create the test data outputing to 'iris_test.data'
with open('iris_train.data', 'w') as data:
    abareader = csv.reader(open('iris.data'))
    #interate through a list comprising of every 4th item in the data list
    for row in list(abareader)[::int(sys.argv[1])]:
        #interate over the first 4 items in the row
        for x in row[0:4]:
            #transform the float values into integer values
            #by multiplying by 10 and discarding anything after decimal point
            print >>data, "%2d"%(int(round(float(x)*10))),
        #make the class name a integer
        print >>data, "%d" % (int(name[row[4]]))
        

#create the training data outputing to iris_train.data
with open('iris_test.data', 'w') as data:
    abareader = csv.reader(open('iris.data'))
    tmp = list(abareader)#the entire list
    tmp2 = tmp[::int(sys.argv[1])]#represents the testing data
    #interate over a diff between the 2 lists, tmp and tmp2
    for row in [i for i in tmp+tmp2 if i not in tmp or i not in tmp2]:
        for x in row[0:4]:
            print >>data, "%2d"%(int(round(float(x)*10))),
        print >>data, "%d" % (int(name[row[4]]))

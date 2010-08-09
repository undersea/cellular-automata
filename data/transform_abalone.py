import csv


sex = {'I':0, 'M':1, 'F':2 }
with open('abalone2.data', 'w') as data:
    abareader = csv.reader(open('abalone.data'))
    for row in abareader:
        tmp = []
        print >>data, sex[row[0]],
        for x in row[1:8]:
            print >>data, "%2d"%(int(round(float(x)*10))),
        print >>data, "%2d" % (int(row[8]))
        
#    print tmp

#with open('abalone2.data', 'w') as output:
#    output.write(str(data))


    

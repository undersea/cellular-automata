import csv


sex = {'I':0, 'M':1, 'F':2 }
with open('abalone2.data', 'w') as data:
    abareader = csv.reader(open('abalone.data'))
    for row in abareader:
        tmp = []
        print >>data, sex[row[0]],
        for x in row[1:7]:
            print >>data, int(round(float(x)*1000)),
        print >>data, int(row[8])
        
#    print tmp

#with open('abalone2.data', 'w') as output:
#    output.write(str(data))


    

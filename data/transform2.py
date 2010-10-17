import sys, csv, os

attrs = dict()
transvalue = dict()
transattr = dict()


datafilename = sys.argv[1][0:sys.argv[1].index('.data')]
train = '%s_train.txt' % (datafilename)
test = '%s_test.txt' % (datafilename)
definition = '%s_definition.txt' % (datafilename)

tmp = test
tmp2 = train

multiplier = int(sys.argv[3])

if len(sys.argv) > 4 and sys.argv[4] == 'train':
    tmp = train
    tmp2 = test

with open(tmp, 'w') as data:
    inputdata = csv.reader(open(sys.argv[1]))
    for row in list(inputdata)[::int(sys.argv[2])]:
        for i in range(1, len(row)-1):
            
            if i >= len(attrs):
                try:
                    float(row[i])
                except:
                    transvalue[i] = 1
                    transattr[row[i]] = transvalue[i]
                    attrs[i] = transattr[row[i]]
                else:
                    attrs[i] = int(round(float(row[i])*multiplier))
            else:
                try:
                    float(row[i])
                except:
                    if row[i] in transattr:
                        if attrs[i] < transattr[row[i]]:
                            attrs[i] = transattr[row[i]]
                    else:
                        try:
                            transvalue[i] += 1
                        except:
                            transvalue[i] = 1
                        transattr[row[i]] = transvalue[i]
                        if attrs[i] < transattr[row[i]]:
                            attrs[i] = transattr[row[i]]
                else:
                    if attrs[i] < int(round(float(row[i])*multiplier)):
                        attrs[i] = int(round(float(row[i])*multiplier))
            try:
                result = int(round(float(row[i])*multiplier))
                print >>data, '%2d' % (result),
            except:
                print >>data, '%2d' % (transattr[row[i]]),
       
        try:
            print >>data, '%d' % (int(row[len(row)-1]))
        except:
            if row[len(row)-1] in transattr:
                print >>data, '%d' % (transattr[row[len(row)-1]])
            else:
                if len(row)-1 in transvalue:
                    transvalue[len(row)-1] += 1
                else:
                    transvalue[len(row)-1] = 1
                transattr[row[len(row)-1]] = transvalue[len(row)-1]
                print >>data, '%d' % (transattr[row[len(row)-1]])


with open(tmp2, 'w') as data:
    inputdata = csv.reader(open(sys.argv[1]))
    tmp = list(inputdata)#the entire list
    tmp2 = tmp[::int(sys.argv[2])]#represents the testing data
    #interate over a diff between the 2 lists, tmp and tmp2
    for row in [i for i in tmp+tmp2 if i not in tmp or i not in tmp2]:
        for i in range(1, len(row)-1):
            #just time by 10 and hope for the best
            if i >= len(attrs):
                try:
                    float(row[i])
                except:
                    transvalue[i] = 1
                    transattr[row[i]] = transvalue[i]
                    attrs[i] = transattr[row[i]]
                else:
                    attrs[i] = int(round(float(row[i])*multiplier))
            else:
                try:
                    float(row[i])
                except:
                    if row[i] in transattr:
                        if attrs[i] < transattr[row[i]]:
                            attrs[i] = transattr[row[i]]
                    else:
                        transvalue[i] += 1
                        transattr[row[i]] = transvalue[i]
                        if attrs[i] < transattr[row[i]]:
                            attrs[i] = transattr[row[i]]
                else:
                    if attrs[i] < int(round(float(row[i])*multiplier)):
                        attrs[i] = int(round(float(row[i])*multiplier))

            try:
                print >>data, '%2d' % (int(round(float(row[i])*multiplier))),
            except:
                print >>data, '%2d' % (transattr[row[i]]),
        try:
            print >>data, '%d' % (int(row[len(row)-1]))
        except:
            if row[len(row)-1] in transattr:
                print >>data, '%d' % (transattr[row[len(row)-1]])
            else:
                if len(row)-1 in transvalue:
                    transvalue[len(row)-1] += 1
                else:
                    transvalue[len(row)-1] = 1
                transattr[row[len(row)-1]] = transvalue[len(row)-1]
                print >>data, '%d' % (transattr[row[len(row)-1]])

with open(definition, 'w') as data:
    print >>data, len(attrs), ' ',
    for x in attrs:
        print >>data, int(attrs[x]) + 1, ' ',

wd = os.getcwd()

print '%s/%s %s/%s %s/%s' % ( wd, definition, wd, train, wd, test)


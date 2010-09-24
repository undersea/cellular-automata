import pylab as pl

points = [i**2 for i in range(-40,41)]

pl.figure(1)

pl.fill(points, color='r')
pl.fill_between(range(81), points, color='k')
pl.grid(color='w')
pl.axis([0, 80, 0, 80])

pl.show()

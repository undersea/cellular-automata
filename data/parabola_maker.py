#!/usr/bin/env python

grid = ([1]*81)*81

for x in range(41):
    if x**2 < 81:
        for y in range(x**2, 81):
            grid[

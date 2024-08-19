#!/usr/bin/env python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
T = int(cmdlinearg('T'))
max_n = int(cmdlinearg('max_n'))
max_m = int(cmdlinearg('max_m'))
max_w = int(cmdlinearg('max_w'))

print(T)

for _ in range(T):
    edge_set = set()
    edges = []
    weights = []
    n = random.randint(5, max_n)
    m = random.randint(n-1, min(max_m, n*n-n))
    [s1, t1, s2, t2] = random.sample(range(0, n), 4)
    
    print(n, m)
    print(s1+1, t1+1, s2+1, t2+1)

    for i in range(0, m):
        i = random.randrange(0, n)
        j = random.randrange(0, n)
        while i == j or (i,j) in edge_set:
            i = random.randrange(0, n)
            j = random.randrange(0, n)
        edges.append((i, j))
        edge_set.add((i, j))
    
    for i in range(m):
        w = random.randint(1, max_w)
        print(edges[i][0]+1, edges[i][1]+1, w)

    
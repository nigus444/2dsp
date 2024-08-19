#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution heuristic.cpp

compile connected_undirected.py
compile gen_random.py

MAXN=1000
MAXM=2000
MAXT=10000

samplegroup
limits max_T=$MAXT max_n=$MAXN max_m=$MAXM
sample 1
sample 2

group group1 50
limits max_T=$MAXT max_n=20 max_m=60
tc 1
tc 2
tc g1-rand-1 gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-2 gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-3 gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-4 gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-5 gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-6 gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-7 gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-8 gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-9 gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-a gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-b gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-c gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-d gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-e gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-f gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-g gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-h gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-i gen_random T=$MAXT max_n=20 max_m=60 max_w=7

tc g1-rand-j gen_random T=$MAXT max_n=20 max_m=60 max_w=1
tc g1-rand-k gen_random T=$MAXT max_n=20 max_m=60 max_w=7

group group2 50
limits max_T=$MAXT max_n=20 max_m=60
tc g2-rand-1 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-2 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-3 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-4 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-5 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-6 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-7 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-8 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-9 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-10 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-11 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-12 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-13 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-14 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-15 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-16 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-17 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-18 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

tc g2-rand-19 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=1
tc g2-rand-20 connected_undirected T=$MAXT max_n=20 max_m=60 max_w=7

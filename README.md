## Two disjoint shortest paths for directed graphs with positive weights in O(n^3m)

This repo contains some work I did on an algorithm problem back in 2021. 
Thank you to Thore Husfeldt for introducing me to this problem.

### The problem

You are given a graph with two pairs of vertices $(s_1, t_1)$ and $(s_2, t_2)$. The 
goal is to find a pair of shortest paths, from $s_1$ to $t_1$ and from $s_2$ to $t_2$, that
do not intersect on any vertex. Let's call this the two disjoint shortest paths problem
(2DSP). This repo contains an algorithm for solving this problem on directed graphs
with positive edge weights in $O(n^3m)$. There is also an implementation of this algorithm, as well as some tests.

### Content

The file `2dsp_directed.pdf` explains how the algorithm works. 

The file `2dsp_undirected.pdf` is also based on work I did in 2021 and describes an algorithm for the undirected case that runs in $O(nm)$. However, this PDF is outdated (even as of writing this), as faster algorithms for solving this problem now exist.

The folder `2dsp` contains 
an implementation of the algorithm and a way to test it on $~10^5$ graphs. This folder is on the 
problemtools format (see https://github.com/Kattis/problemtools). To use it, first install 
problemtools. Then, run verifyproblem on the folder `2dsp`.

In `2dsp/submissions/accepted/` there are three files:

* `python_solution.py` is an implementation of 2DSP on directed graphs with positive edge
weights. It runs in $O(n^3m)$.

* `heuristic.cpp` is a solution that is exponential in the worst case, but fast on random
graphs. This is used as a reference solution to compare against. It first fixes a random
 shortest path between s1 and t1. It then finds any shortest path s2 and t2 that doesn't
  intersect the fixed one. This is repeated 100 times or until a solution is found. Since 
  the graphs are small and random, this heuristic is quite good at finding solutions if 
  they exist. Note that the output validator still checks correctness of solutions, so
  if the heuristic fails to find one while the other solution finds one, this would 
  result in a "judge error" which is different from "wrong answer".

* `main_solution.cpp` is an implementation of two disjoint shortest paths on undirected
graphs, with positive edge weights. In runs in $O(nm)$. 

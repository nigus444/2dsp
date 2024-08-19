#!/usr/bin/env python3
from heapq import heappop, heappush

# INPUT: 
# The first line of input contains an integer T, the number of test cases.
# Each test case starts with one line containing the integers N and M, the
# number of vertices and edges in the directed graph. The second line contains
# four integers s1, t1, s2, t2 - the start/end vertices of the 2DSP instance.
# The following M lines each contains three integers ui, vi, wi, indicating that
# a directed edge with weight wi goes from ui to vi. All vertices are 1-indexed.

# OUTPUT:
# For each test case, if a solution doesn't exist, print '-1'. If a solution does exist,
# print the solution on the following format:
# k1
# p1 p2 p3 ... p_k1
# k2
# q1 q2 q3 ... q_k2


INF = 10 ** 10
DONE = (-2, -2, -2, -2)
INVALID = (-1, -1, -1, -1)

class DAG:
    def __init__(self, n):
        self.adj = [[] for _ in range(n)]
    
    def add_edge(self, i, j):
        self.adj[i].append(j)

    def reversed(self):
        result = DAG(len(self.adj))
        for i in range(len(self.adj)):
            for j in self.adj[i]:
                result.add_edge(j, i)
        return result

    def topsort(self):
        n = len(self.adj)
        in_degree = [0] * n
        stack = []
        ans = []
        for i in range(n):
            for j in self.adj[i]:
                in_degree[j] += 1
        for i in range(n):
            if in_degree[i] == 0:
                stack.append(i)
        while len(stack) > 0:
            i = stack.pop()
            ans.append(i)
            for j in self.adj[i]:
                in_degree[j] -= 1
                if in_degree[j] == 0:
                    stack.append(j)
        return ans

class TwoDisjointPaths:
    """This class takes a DAG and gives 2-disjoint paths, using the standard O(nm) approach."""
    def __init__(self, dag):
        self.dag = dag
        self.order = dag.topsort()
        self.next_state = {}
    
    def dp(self, t1, t2):
        n = len(self.order)
        for i in reversed(range(n)):
            for j in reversed(range(n)):
                u = self.order[i]
                v = self.order[j]
                if u == v:
                    self.next_state[(u,v,t1,t2)] = INVALID
                elif u == t1 and v == t2:
                    self.next_state[(u,v,t1,t2)] = DONE
                elif u == t1 or (v != t2 and j < i):
                    # Advance v
                    self.next_state[(u,v,t1,t2)] = INVALID
                    for v2 in self.dag.adj[v]:
                        if self.next_state[(u,v2,t1,t2)] != INVALID:
                            self.next_state[(u,v,t1,t2)] = (u,v2,t1,t2)
                            break
                else:
                    # Advance u
                    self.next_state[(u,v,t1,t2)] = INVALID
                    for u2 in self.dag.adj[u]:
                        if self.next_state[(u2,v,t1,t2)] != INVALID:
                            self.next_state[(u,v,t1,t2)] = (u2,v,t1,t2)
                            break
    
    def get_paths(self, s1, s2, t1, t2):
        if (s1,s2,t1,t2) not in self.next_state:
            self.dp(t1,t2)
        if self.next_state[(s1, s2, t1, t2)] == INVALID:
            return -1
        state = (s1, s2)
        path1 = [s1]
        path2 = [s2]
        while True:
            (*state, _, _) = self.next_state[(*state, t1, t2)]
            if state[0] == -2:
                break
            if state[0] != path1[-1]:
                path1.append(state[0])
            if state[1] != path2[-1]:
                path2.append(state[1])
        return path1, path2


class Graph:
    def __init__(self, n):
        self.adj = [[] for _ in range(n)]
        self.dist = [[] for _ in range(n)]

    def add_edge(self, i, j, w):
        self.adj[i].append((j, w))

    def dijkstra(self, i):
        """ Runs a Dijkstra from i, putting values in self.dist[i]. """
        seen = [False] * len(self.adj)
        self.dist[i] = [INF] * len(self.adj)
        self.dist[i][i] = 0
        pq = []
        heappush(pq, (0, i))
        while len(pq) > 0:
            j = heappop(pq)[1]
            if not seen[j]:
                seen[j] = True
                for (k, w) in self.adj[j]:
                    if self.dist[i][k] > w + self.dist[i][j]:
                        self.dist[i][k] = w + self.dist[i][j]
                        heappush(pq, (self.dist[i][k], k))


    def get_shortest_path_dag(self, start):
        self.dijkstra(start)
        n = len(self.adj)
        dag = DAG(n)
        for i in range(n):
            for (j, w) in self.adj[i]:
                if self.dist[start][j] - self.dist[start][i] == w:
                    dag.add_edge(i, j)
        return dag

def get_two_disjoint_shortest_paths(graph, s1, t1, s2, t2):
    def psi(v):
        return graph.dist[s1][v] - graph.dist[s2][v]
    n = len(graph.adj)
    dag1 = graph.get_shortest_path_dag(s1)
    dag2 = graph.get_shortest_path_dag(s2)
    constant_dag = DAG(n) # The DAG consisting of edges u -> v where psi(u) = psi(v)
    for i in range(n):
        for j in dag1.adj[i]:
            if psi(i) == psi(j):
                constant_dag.add_edge(i, j)
    constant_paths = TwoDisjointPaths(constant_dag)
    dag2 = dag2.reversed()

    u_order = list(range(n))
    v_order = list(range(n))
    topsort_pos = {}
    topsort = constant_dag.topsort()
    for i in range(n):
        topsort_pos[topsort[i]] = i

    # Sort the vertices in such a way that we can solve the DP problem bottom up.
    # These orders are topsorts of dag1/dag2, but it is important that they are
    # sorted wrt psi(x) first so that the outer DP transitions happen in the right order.
    u_order.sort(key=lambda x: (psi(x), topsort_pos[x]))
    v_order.sort(key=lambda x: (psi(x), -topsort_pos[x]))
    
    # next_state maps a state to the state it leads to in the DP, so that
    # we can reconstruct the paths. If we have subproblem with u, v with
    # equal psi, then this will map to a list of states, representing two
    # disjoint paths on the constant_dag.
    next_state = {}

    # terminal_state maps a state (u, v) to a state (u', v') such that psi(u) == psi(v),
    # psi(u') != psi(u), and psi(v') != psi(u'), and (u', v') is a solution. In other
    # words, this map will map to another state if (u, v) is a 'terminal state'. This
    # is also used to reconstruct the paths, otherwise we would only need to save whether
    # a state is a terminal state or not.
    terminal_state = {}

    for i in reversed(range(n)):
        for j in reversed(range(n)):
            u = u_order[i]
            v = v_order[j]

            if u == v or graph.dist[s1][u] == INF or graph.dist[s2][v] == INF:
                next_state[(u, v)] = INVALID
            elif u == t1 and v == s2: 
                next_state[(u, v)] = DONE
            elif u == t1 or (v != s2 and psi(v) < psi(u)):
                # Advance v
                next_state[(u, v)] = INVALID
                for w in dag2.adj[v]:
                    if next_state[(u, w)] != INVALID:
                        next_state[(u, v)] = (u, w)
                        break
            elif v == s2 or (u != t1 and psi(u) < psi(v)):
                # Advance u
                next_state[(u, v)] = INVALID
                for w in dag1.adj[u]:
                    if next_state[(w, v)] != INVALID:
                        next_state[(u, v)] = (w, v)
                        break
            else:
                # Same psi - solve inner DAG disjoint paths problem
                next_state[(u, v)] = INVALID
                for up in range(n):
                    for vp in range(n):

                        # Filter out impossible up, vp
                        if psi(up) != psi(u) or psi(vp) != psi(u) or (up, vp) not in next_state:
                            continue

                        # Find out if (up, vp) is a terminal state, and where to go next
                        # Each pair (up, vp) will only enter this if-statement once, so this
                        # part takes O(nm). Right now it actually takes O(m^2)...
                        if (up, vp) not in terminal_state:
                            if up == t1 and vp == s2:
                                terminal_state[(up, vp)] = DONE
                            elif up == vp:
                                terminal_state[(up, vp)] = INVALID
                            else:
                                terminal_state[(up, vp)] = INVALID
                                for u3 in dag1.adj[up]:
                                    for v3 in dag2.adj[vp]:
                                        # ...these loops can be memoized to make it O(nm).
                                        if psi(u3) != psi(u) and psi(v3) != psi(v) and next_state[(u3, v3)] != INVALID:
                                            terminal_state[(up, vp)] = (u3, v3)
                                            break
                                if vp == s2:
                                    for u3 in dag1.adj[up]:
                                        if psi(u3) != psi(u) and next_state[(u3, vp)] != INVALID:
                                            terminal_state[(up, vp)] = (u3, vp)
                                            break
                                if up == t1:
                                    for v3 in dag2.adj[vp]:
                                        if psi(v3) != psi(v) and next_state[(up, v3)] != INVALID:
                                            terminal_state[(up, vp)] = (up, v3)
                                            break
                                            

                        # If (up, vp) is a terminal state, try to find disjoint paths.
                        if terminal_state[(up, vp)] != INVALID:
                            # get_paths runs an O(nm) DP for every pair (up, v).
                            # So this function call is the bottleneck, making
                            # the algorithm run in O(n^3m).
                            paths = constant_paths.get_paths(u, vp, up, v)
                            if paths != -1:
                                if u == up and v == vp:
                                    next_state[(u, v)] = terminal_state[(u, v)]
                                else:
                                    next_state[(u, v)] = (paths[0], paths[1][::-1])
    
    # Reconstruct the paths
    x, y = s1, t2
    if next_state[(x, y)] != INVALID:
        path1 = [x]
        path2 = [y]
        while next_state[(x, y)] != DONE:
            nxt = next_state[(x, y)]
            if isinstance(nxt[0], list):
                # next_state gave lists, so we need to follow the constant_dag paths
                # This part requires some care when reconstructing the paths, we have
                # to make sure the solution actually reaches the "terminal_state" of
                # this psi(u).
                for u in nxt[0]:
                    if u != x:
                        path1.append(u)
                for v in nxt[1]:
                    if v != y:
                        path2.append(v)
                x = path1[-1]
                y = path2[-1]
                nxt = terminal_state[(x, y)]
                if nxt == DONE:
                    break
                (x, y) = nxt
                if path1[-1] != x:
                    path1.append(x)
                if path2[-1] != y:
                    path2.append(y)
            else:
                # Different psi, just go to next_state and update the paths.
                (x, y) = nxt
                if path1[-1] != x:
                    path1.append(x)
                if path2[-1] != y:
                    path2.append(y)
        return (path1, path2[::-1])
    else:
        return -1


T = int(input())
for t in range(T):
    n, m = map(int, input().split())
    s1, t1, s2, t2 = map(int, input().split())
    s1 -= 1
    t1 -= 1
    s2 -= 1
    t2 -= 1
    graph = Graph(n)
    for _ in range(m):
        a, b, c = map(int, input().split())
        a -= 1
        b -= 1
        graph.add_edge(a, b, c)
    ans = get_two_disjoint_shortest_paths(graph, s1, t1, s2, t2)
    if ans == -1:
        print(-1)
    else:
        print(len(ans[0]))
        print(*[i+1 for i in ans[0]])
        print(len(ans[1]))
        print(*[i+1 for i in ans[1]])   
        
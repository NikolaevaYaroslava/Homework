#!/usr/bin/env python3

import os
import collections
import sys
from random import randint

def solve(graph, root, dest):

    visited, queue = set(), collections.deque([root])
    visited.add(root)

    dist = dict()
    for k in graph.keys():
        dist[k] = -1

    last_vertex = root
    while queue: 
        vertex = queue.popleft()
        dist[vertex] = dist[last_vertex] + 1
        for neighbour in graph[vertex]: 
            if neighbour not in visited: 
                visited.add(neighbour) 
                queue.append(neighbour) 

    return dist[dest]


argv = sys.argv

tests_dir = "./tests_graph/"

if len(argv) < 2:
    print("Please provide the mode")
    sys.exit()


if (argv[1] == "gen"):
    print("Generating tests...")
    for i in range(0, 100): # 100 tests
        print("Generating test " + str(i+1))
        graph_size = randint(1, 100)
        max_edges_pos = (graph_size * (graph_size-1)) // 2
        edge_num = randint(1, max_edges_pos + 1)
        edges = [(randint(0, graph_size - 1), randint(0, graph_size - 1)) for i in range(edge_num)]
        f = open(tests_dir + "test" + str(i+1), "w")
        f.write(str(graph_size) + "\n")
        f.write(str(edge_num) + "\n")
        for x in edges:
            f.write("{} {}\n".format(x[0], x[1]))
        start = randint(0, graph_size - 1)
        dest = randint(0, graph_size - 1)
        f.write("{} {}".format(start, dest))
        f.close()

if (argv[1] == "run"):
    if len(argv) < 3 :
        print("Please provide executable path...")
        sys.exit()
    prog = argv[2]
    print("Running tests...")
    for i in range(0, 100):
        print("Running test " + str(i+1))
        command = "{} {}test{} {}ans{}".format(prog, tests_dir, i+1, tests_dir, i+1)
        os.system(command)

if (argv[1] == "check"):
    print("Checking test results...")
    failed_tests = 0
    for i in range(0, 100):
        test = open(tests_dir + "test" + str(i+1), "r")
        test_graph = dict()
        graph_size = int(test.readline())
        test.readline() # garbage
        test_graph = []
        for line in test:
            p = line.split()
            test_graph.append((int(p[0]), int(p[1])))
        start, goal = test_graph[-1]
        test_graph = test_graph[:-1] # last pair is start and goal
        test_graph_as_dict = {}
        for idx in range(0, graph_size):
            test_graph_as_dict[idx] = []
        for p in test_graph:
            frm = p[0]
            to = p[1]
            test_graph_as_dict[frm].append(to)
        exp_ans = solve(test_graph_as_dict, start, goal)
        test.close()
        ans_file = open(tests_dir + "ans" + str(i+1), "r")
        ans = int(ans_file.read())
        ans_file.close()
        
        res = ""
        if ans != exp_ans:
            failed_tests += 1
            res = "FAILED"
        else:
            res = "passed"
        print("Test{}: {}".format(i+1, res))
    print("TOTAL TESTS FAILED: {}".format(failed_tests))



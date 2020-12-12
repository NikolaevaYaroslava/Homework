#!/usr/bin/env python3

import os
import sys
from random import randint

argv = sys.argv

tests_dir = "./tests_sort/"

if len(argv) < 2:
    print("Please provide the mode")
    sys.exit()


if (argv[1] == "gen"):
    print("Generating tests...")
    for i in range(0, 100): # 100 tests
        print("Generating test " + str(i+1))
        array_size = randint(0, 100000)
        array = [randint(-900000,900000) for i in range(array_size)]
        f = open(tests_dir + "test" + str(i+1), "w")
        f.write(str(array_size) + "\n")
        for x in array:
            f.write(str(x) + "\n")
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
        test_array = list(map(int, test.read().split()))
        test_array = test_array[1:] # first number is amount of ints
        test.close()
        ans = open(tests_dir + "ans" + str(i+1), "r")
        res_array = list(map(int, ans.read().split()))
        test.close()
        
        test_array.sort()
        res = ""
        if test_array != res_array:
            failed_tests += 1
            res = "FAILED"
        else:
            res = "passed"
        print("Test{}: {}".format(i+1, res))
    print("TOTAL TESTS FAILED: {}".format(failed_tests))





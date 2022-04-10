#! /usr/local/bin/python3

import subprocess
import os
import difflib
from itertools import combinations
import re

total = 0
false = 0

f = open("trace.txt", "w");

params = ['-r', '-l', '-R', '-a', '-t'];
paramsCombos = sum([list(map(list, combinations(params, i))) for i in range(len(params) + 1)], [])

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def prefilter(line):
    return re.sub("\s+"," ",line.strip())

def get_diff(name, s1, s2):
	global f

	f.write("-------------------- ["+ name +"] --------------------");
	for line in difflib.unified_diff([prefilter(x) for x in s1], [prefilter(x) for x in s2], fromfile='mine', tofile='real', lineterm=''):
		f.write(line + "\n");
	f.write("\n");

def run_compare(path, commands):
	real = subprocess.run(["/bin/ls"] + commands + [path], stdout=subprocess.PIPE, stderr=subprocess.PIPE);

	if (real.returncode != 0):
		print("ERROR: REAL FAIL ", real.returncode ,["/bin/ls", "--color=never"] + commands + [path], real.stderr.decode("utf-8"));

	mine = subprocess.run(["./ft_ls"] + commands + [path], stdout=subprocess.PIPE, stderr=subprocess.PIPE);

	if (real.stdout.decode("utf-8") == mine.stdout.decode("utf-8")):
		return 0
	get_diff(" ".join(["./ft_ls"] + commands + [path]), real.stdout.decode("utf-8").splitlines(), mine.stdout.decode("utf-8").splitlines())
	return 1

def run_tests(path):
	global paramsCombos, total, false
	print(paramsCombos)
	for i in paramsCombos:
		res = run_compare(path, i);
		print('{:<40s}'.format(path + " " + " ".join(i)), flush=True, end='');
		total += 1
		if res != 0:
			print('{:>20s}'.format(bcolors.FAIL + "[ KO ]" + bcolors.ENDC))
			false += 1;
		else:
			print('{:>20s}'.format(bcolors.OKGREEN + "[ OK ]" + bcolors.ENDC))

def test():
	dirs = os.walk("./")
	for dir in dirs:
		if (dir[0].startswith("./tests/")):
			run_tests(dir[0]);

test()
f.close();
print ('{:d} tests run {:d} errors'.format(total, false));
if (false != 0):
	exit(1)
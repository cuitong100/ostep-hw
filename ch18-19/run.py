#!/usr/bin/env python
import os

i = 1
while i <= 4096 :
	print('page num ' + str(i))
	os.system('taskset -c 0 ./tlb ' + str(i) + ' ' + str(100000)) #run tlb for different number of pages, 100000 times for each
	i = i * 2
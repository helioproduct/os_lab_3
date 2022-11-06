#!/bin/python3

import re
from sys import argv

file = open(argv[1], "r")
s = file.read()
file.close()

substr = argv[2]
 
result = [_.start() for _ in re.finditer(substr, s)] 

for x in result:
    print(x)

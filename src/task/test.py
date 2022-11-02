#!/bin/python3

import re
from sys import argv


file = open(argv[1], "r")
s = file.read()
file.close()

result = [m.start() for m in re.finditer(argv[2], s)]

for i in result:
    print(i)


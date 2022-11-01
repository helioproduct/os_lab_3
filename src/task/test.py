#!/bin/python3

import re

file = open("./source.txt", "r")
s = file.read()
file.close()

result = [m.start() for m in re.finditer('секс', s)]

print(len(result))
print()

for i in result:
    print(i)


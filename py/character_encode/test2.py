# -*-coding:utf-8-*-

import sys, json

args = sys.argv

param = args[1]

print("------------------")
for c in param:
    print(c)
print("------------------")
for c in param:
    print(ord(c))
print(ord(param))

#
#  data = json.dumps({"content": param})
#  print("old_data: ", data)
#  print("new_data: ", data.encode())
print("------------------")

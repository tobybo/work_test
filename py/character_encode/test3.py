# -*-coding:utf-8-*-

import sys, json

args = sys.argv

param = args[1]

print("python: %s" %param)
print("------------------")
#  for c in param:
#      print(c)
#  for c in param.encode():
#      print(c)
print("------------------")

#  data = json.dumps({"content": param})
#  print("old_data: ", data)
#  print("new_data: ", data.encode())
print("------------------")

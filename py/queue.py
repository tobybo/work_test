
from Queue import Queue

q = Queue()

q.put(1)
q.put(2)
q.put(3)


print(q.qsize())
print("get: ", q.get())
print(q.qsize())

while not q.empty():
    item = q.get()
    print(item)


import sys


class Rope:
    def __init__(self, s):
        self.s = s

    def result(self):
        return self.s

    def process(self, i, j, k):
        if k == i:
            return
        start, mid, end = self.s[:i], self.s[i:j+1], self.s[j+1:]
        if k > i:
            self.s = start + end[:k-i] + mid + end[k-i:]
        else:
            self.s = start[:k] + mid + start[k:] + end


rope = Rope(sys.stdin.readline().strip())
q = int(sys.stdin.readline())
for _ in range(q):
    i, j, k = map(int, sys.stdin.readline().strip().split())
    rope.process(i, j, k)
print(rope.result())

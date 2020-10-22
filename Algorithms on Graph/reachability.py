import sys
from collections import deque

visited = set()
adj = None


def search(x, y):
    global visited
    qu = deque()
    if x not in visited:
        for v in adj[x]:
            if v == y:
                return 1
            else:
                qu.append(v)
        visited.add(x)
        while len(qu) > 0:
            if search(qu.popleft(), y):
                return 1
        else:
            return 0
    else:
        return 0


def reach(x, y):
    """Function to check if there is a path between x and y.

    Parameters
    ----------
    x : int
        Index of source vertex in graph.
    y : int
        Index of destination vertex in graph.

    Returns
    -------
    int
        retuns 1 if path exists else 0.
    """
    if search(x, y):
        return 1
    return 0


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    x, y = data[2 * m:]
    adj = [[] for _ in range(n)]
    x, y = x - 1, y - 1
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)
    print(reach(x, y))

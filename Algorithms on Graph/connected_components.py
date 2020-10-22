import sys
from collections import deque

visited = set()
adj = None


def count(x):
    """Function to check where a vetex is connected to already counted component.

    Parameters
    ----------
    x : int
        Index of the vertex in graph.

    Returns
    -------
    int
    """
    global visited
    qu = deque()
    if x not in visited:
        for v in adj[x]:
            qu.append(v)
        visited.add(x)
        while len(qu) > 0:
            count(qu.popleft())
        return 1
    else:
        return 0


def number_of_components(adj):
    """Function to compute the number of connected components.

    Parameters
    ----------
    adj : list
        Adjacency matrix represting the graph.

    Returns
    -------
    int
        Number of connected components.
    """
    result = 0
    for i in range(len(adj)):
        result += count(i)
    return result


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)
    print(number_of_components(adj))

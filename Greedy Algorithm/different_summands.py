import sys


def optimal_summands(n):
    """Find maximum distinct number which sum up to n

    Parameters
    ----------
    n : int

    Returns
    -------
    list
        list of distinct number
    """
    summands = []
    i = 1
    while n > 0:
        if n-i > i:
            summands.append(i)
            n -= i
        else:
            summands.append(n)
            n = 0
        i += 1
    return summands


if __name__ == '__main__':
    input = sys.stdin.read()
    n = int(input)
    summands = optimal_summands(n)
    print(len(summands))
    for x in summands:
        print(x, end=' ')

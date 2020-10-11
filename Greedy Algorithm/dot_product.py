import sys


def max_dot_product(a, b):
    """Finds the maximum value that can be obtained by dot product
    of any permutation of a and b.

    Parameters
    ----------
    a : list
    b : list

    Returns
    -------
    int
        maximum possible value
    """
    a.sort()
    b.sort()
    res = 0
    for i in range(len(a)):
        res += a[i] * b[i]
    return res


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    a = data[1:(n + 1)]
    b = data[(n + 1):]
    print(max_dot_product(a, b))

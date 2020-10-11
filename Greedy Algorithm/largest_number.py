import sys


def greater(x, y):
    """Find the number from x and y that will favour the formation
    of largest number

    Parameters
    ----------
    x : str
        string representing a number
    y : str
        stirng representing a number

    Returns
    -------
    str
        string representation of desigered number
    """
    if len(x) == 0:
        return y
    elif len(y) == 0:
        return x
    s, l = (x, y) if len(x) < len(y) else (y, x)
    if s > l[:len(s)]:
        return s
    elif s < l[:len(s)]:
        return l
    else:
        if greater(l[len(s):], s) == s:
            return s
        else:
            return l


def largest_number(a):
    """Finds the largest number that can be obtained by appending different
    numbers in a

    Parameters
    ----------
    a : list

    Returns
    -------
    str
        String representing the largest number
    """
    res = ""
    while len(a) != 0:
        max_ = a[0]
        for i in range(len(a)):
            max_ = greater(max_, a[i])
        res += max_
        a.remove(max_)
    return res


if __name__ == '__main__':
    input = sys.stdin.read()
    data = input.split()
    a = data[1:]
    print(largest_number(a))

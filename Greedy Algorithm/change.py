import sys


def get_change(m):
    """Finds the minimum number of coins needed to change m into
    coins with denominations of 1, 5 and 10

    Parameters
    ----------
    m : int
        amount to be changed

    Returns
    -------
    int
        minimum number of coins needed
    """
    count = 0
    count += m//10
    m = m % 10
    count += m//5
    m = m % 5
    count += m
    return count


if __name__ == '__main__':
    m = int(sys.stdin.read())
    print(get_change(m))

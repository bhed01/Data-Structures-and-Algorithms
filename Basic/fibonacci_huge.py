def get_fibonacci_huge(n, m):
    """Returns the nth fibonacci number modulo m

    Parameters
    ----------
    n : int
    m : int

    Returns
    -------
    int
        nth fibonacci number modulo m
    """
    if n <= 1:
        return n

    previous, current = 0, 1
    record = {0: 0, 1: 1}
    for _ in range(n - 1):
        previous, current = current, (previous + current) % m
        record[_+2] = current
        if previous == 0 and current == 1:
            break
    else:
        return current
    return record[n % (len(record)-2)]


if __name__ == '__main__':
    n, m = map(int, input().split())
    print(get_fibonacci_huge(n, m))

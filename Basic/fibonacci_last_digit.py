import sys


def get_fibonacci_last_digit_naive(n):
    """Returns last digit of the nth fibonacci number

    Parameters
    ----------
    n : int

    Returns
    -------
    int
        last digit of nth fibonacci number
    """
    if n <= 1:
        return n

    previous = 0
    current = 1

    for _ in range(n - 1):
        previous, current = current, (previous + current) % 10

    return current


if __name__ == '__main__':
    input = sys.stdin.read()
    n = int(input)
    print(get_fibonacci_last_digit_naive(n))

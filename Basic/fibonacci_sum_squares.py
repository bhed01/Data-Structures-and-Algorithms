# Uses python3
from sys import stdin


def find_repeating(n):
    """Finds repeating fibonacii numbers modulo n

    Parameters
    ----------
    n : int

    Returns
    -------
    (record, size, sum)
        list    -> list of repeating numbers
        size    -> count of repeating numbers
        sum     -> sum of square of repeating numbers 
    """
    record = [0, 1]
    previous = 0
    current = 1
    sum = 1
    size = 1
    while True:
        previous, current = current, (previous + current) % n
        record.append(current)
        if previous == 0 and current == 1:
            break
        else:
            size += 1
            sum = (sum + current**2) % 10
    return record[:-2], size, sum


def fibonacci_sum_squares(n):
    """Finds the last digit of sum of square of first n fibonacci numbers

    Parameters
    ----------
    n : int

    Returns
    -------
    int
        last digit of sum of square of first n fibonacci numbers
    """

    if n <= 1:
        return n

    record, size, sum = find_repeating(10)

    sum = (sum*(n//size)) % 10
    for i in range(n % size+1):
        sum = (sum+record[i]**2) % 10

    return sum


if __name__ == '__main__':
    n = int(stdin.read())
    print(fibonacci_sum_squares(n))

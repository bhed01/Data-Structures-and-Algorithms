# Uses python3
import sys


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
        sum     -> sum of repeating numbers 
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
            sum = (sum + current) % 10
    return record[:-2], size, sum


def fibonacci_sum(n):
    """Finds the last digit of sum of first n fibonacci numbers

    Parameters
    ----------
    n : int

    Returns
    -------
    int
        last digit of sum of first n fibonacci numbers
    """
    if n <= 1:
        return n

    record, size, sum = find_repeating(10)
    sum *= n//size
    sum %= 10
    for i in range(n % size+1):
        sum += record[i]
        sum %= 10
    return sum


if __name__ == '__main__':
    input = sys.stdin.read()
    n = int(input)
    print(fibonacci_sum(n))

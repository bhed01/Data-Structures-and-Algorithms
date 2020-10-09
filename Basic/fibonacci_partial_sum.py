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
            sum = (sum + current) % n
    return record[:-2], size, sum


def fibonacci_partial_sum(m, n):
    """Finds the last digit of sum of fibonacci numbers from mth index to nth index

    Parameters
    ----------
    m : int
    n : int

    Returns
    -------
    int
        last digit of sum of fibonacci numbers form m to n
    """
    record, size, sum = find_repeating(10)
    m = m-1

    sum_m = (sum*(m//size)) % 10
    for i in range(m % size+1):
        sum_m = (sum_m+record[i]) % 10

    sum_n = (sum*(n//size)) % 10
    for i in range(n % size+1):
        sum_n = (sum_n+record[i]) % 10

    return (sum_n-sum_m) % 10


if __name__ == '__main__':
    from_, to = map(int, input().split())
    print(fibonacci_partial_sum(from_, to))

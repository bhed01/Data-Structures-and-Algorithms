# Uses python3

def calc_fib(n):
    """Finds nth fibonacci number

    Parameters
    ----------
    n : int

    Returns
    -------
    int
        nth fibonacci numbers
    """
    if n <= 1:
        return n
    else:
        a = 1
        b = 1
        for _ in range(2, n):
            c = a+b
            a = b
            b = c
        return b


n = int(input())
print(calc_fib(n))

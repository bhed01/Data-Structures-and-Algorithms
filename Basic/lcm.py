# Uses python3
import sys


def gcd(a, b):
    """Finds the Greatest Common Divisor of a and b

    Parameters
    ----------
    a : int
    b : int

    Returns
    -------
    int
        GCD of a and b
    """
    if b == 0:
        return a
    rem = a % b
    return gcd(b, rem)


def lcm(a, b):
    """Finds the Least Common Multiple of a and b

    Parameters
    ----------
    a : int
    b : int

    Returns
    -------
    int
        LCM of a and b
    """
    return (a*b)//gcd(a, b)


if __name__ == '__main__':
    input = sys.stdin.read()
    a, b = map(int, input.split())
    print(lcm(a, b))

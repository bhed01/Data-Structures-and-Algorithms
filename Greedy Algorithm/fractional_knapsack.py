import sys


def get_optimal_value(capacity, weights, values):
    """Find the maximum fractional value that can be obtained by filling
    the knapsack of size=capacity.

    Parameters
    ----------
    capacity : int
        capacity of knapsack
    weights : list
        weight of different objects
    values : list
        value of different objects

    Returns
    -------
    float
        maximum fractional value
    """
    value = 0
    val_per_unit = []
    for i in range(len(values)):
        val_per_unit.append((values[i]/weights[i], weights[i]))
    val_per_unit.sort(reverse=True)

    for unit_val, weight in val_per_unit:
        if capacity <= weight:
            value += unit_val*capacity
            break
        else:
            value += unit_val*weight
            capacity -= weight

    return value


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n, capacity = data[0:2]
    values = data[2:(2 * n + 2):2]
    weights = data[3:(2 * n + 2):2]
    opt_value = get_optimal_value(capacity, weights, values)
    print("{:.10f}".format(opt_value))

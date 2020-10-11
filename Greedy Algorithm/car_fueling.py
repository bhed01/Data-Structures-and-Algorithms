import sys


def compute_min_refills(distance, tank, stops):
    """Finds the minimum number of refills needed to reach destination

    Parameters
    ----------
    distance : int
        distance between the cities
    tank : int
        capacity of car tank
    stops: list
        list of integers denoting gas stations distance from source

    Returns
    -------
    int
        number of refilss needed if possible otherwise -1
    """
    count = 0
    pre_stop = 0
    can_travel = tank
    for stop in stops:
        if can_travel < stop:
            can_travel = tank + pre_stop
            if can_travel < stop:
                count = -1
                break
            else:
                count += 1
        elif can_travel == stop:
            can_travel = tank + stop
            count += 1
        pre_stop = stop
    else:
        if can_travel < distance:
            can_travel = tank + pre_stop
            if can_travel < distance:
                count = -1
            else:
                count += 1

    return count


if __name__ == '__main__':
    d, m, _, *stops = map(int, sys.stdin.read().split())
    print(compute_min_refills(d, m, stops))

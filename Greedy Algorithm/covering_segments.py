import sys
from collections import namedtuple

Segment = namedtuple('Segment', 'start end')


def optimal_points(segments):
    """Finds the minimum number of points required so that each 
    segment contains at least one marked point.

    Parameters
    ----------
    segments: list
        list of tuples indicating stating and end of line.

    Returns
    -------
    int 
        minimum number of points required
    """
    points = []
    segments.sort(key=lambda x: x.end)

    while len(segments) != 0:
        s = segments[0]
        points.append(s.end)
        j = 0
        while j < len(segments):
            temp = segments[j]
            if temp.start <= s.end and temp.end >= s.end:
                segments.remove(temp)
            else:
                j += 1
    return points


if __name__ == '__main__':
    input = sys.stdin.read()
    n, *data = map(int, input.split())
    segments = list(map(lambda x: Segment(
        x[0], x[1]), zip(data[::2], data[1::2])))
    points = optimal_points(segments)
    print(len(points))
    print(*points)

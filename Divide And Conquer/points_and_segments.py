import sys

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    m = data[1]
    starts = data[2:2 * n + 2:2]
    ends = data[3:2 * n + 2:2]
    points = data[2 * n + 2:]
    all = list(map(lambda x: (x, 1), starts))
    all += list(map(lambda x: (x, 3), ends))
    all += list(map(lambda x: (x, 2), points))

    all.sort()
    count = 0
    record = {}
    for point in all:
        if point[1] == 1:
            count += 1
        elif point[1] == 3:
            count -= 1
        else:
            record[point[0]] = count

    for x in points:
        print(record[x], end=' ')

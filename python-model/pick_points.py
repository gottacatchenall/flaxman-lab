
import numpy as np

def keep_on_grid(points, size):
    for i in range(len(points)):
        if (points[i][0] < 0):
            points[i][0] = 0
        if (points[i][0] > size-1):
            points[i][0] = size-1
        if (points[i][1] < 0):
            points[i][1] = 0
        if (points[i][1] > size-1):
            points[i][1] = size-1

    return points

def gradient(size, num):

    per_side = int(np.floor(np.sqrt(num)))
    resid = num - (per_side)**2
    num_per_col = [per_side for n in range(per_side)]

    for i in range(resid):
        ind = i % (len(num_per_col))
        num_per_col[ind] += 1

    # shuffles num_per_row in place
    np.random.shuffle(num_per_col)

    spacing_y = [(size/x) for x in (num_per_col)]
    spacing_x = int(size / len(num_per_col))
    points = np.zeros((num, 2), dtype=int)

    offset_x = (size/len(num_per_col)) / 2
    offset_y = [size/(2*x) for x in num_per_col]

    row = 0
    col = 0
    i = 0
    for i_c, c in enumerate(num_per_col):
        x = spacing_x*i_c
        for r in range(c):
            y = spacing_y[i_c]*r
            points[i][0] = int(x) + offset_x
            points[i][1] = int(y) + offset_y[i_c]
            i += 1

    ## Add noise
    for i in range(len(points)):
        points[i][0] += int((size/8) * np.random.random())
        points[i][1] += int((size/8) * np.random.random())

    return keep_on_grid(points, size)


def niche(size, num):

    m = np.random.randint(25, 60, size=(4))
    s = sum(m)

    n_per_cluster = [int(num * float(x)/float(s)) for x in m]

    sum_npc = sum(n_per_cluster)
    resid = num - sum_npc

    n_per_cluster[0] += resid

    # shuffles num_per_row in place
    np.random.shuffle(n_per_cluster)

    n_per_cluster = np.reshape(n_per_cluster, (2,2))

    offset = int(size / 4)
    spacing = int(size / 2)

    points = np.zeros((num, 2), dtype=int)
    n = 0
    for i in range(len(n_per_cluster)):
        for j in range(len(n_per_cluster[i])):
            x_noise, y_noise = int((size/6) * np.random.random()), int((size/6) * np.random.random())
            x0 = (i)*spacing + offset + x_noise
            y0 = (j)*spacing + offset + y_noise
            points[n][0] = x0
            points[n][1] = y0
            n_per_cluster[i,j] -= 1
            n += 1
            for k in range(n_per_cluster[i,j]):
                theta = 2*np.pi * np.random.rand()
                r = np.random.poisson(size/8)
                x = int(r * np.cos(theta)) + x0
                y = int(r * np.sin(theta)) + y0
                points[n][0] = x
                points[n][1] = y
                n += 1

    return keep_on_grid(points, size)


def random(size, num):
    points = np.random.randint(0, size, size=(num, 2))
    return points

def pick_hotspot_points(size, num, MODE):
    if (MODE == 'g'):
        return gradient(size, num)
    elif (MODE == 'n'):
        return niche(size, num)
    else:
        return random(size, num)

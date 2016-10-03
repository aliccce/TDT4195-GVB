import numpy as np
from scipy import misc
import matplotlib.pyplot as plt
import math


def read_img(path):
    image = misc.imread(path)
    return image


def plot_fig(img, param='none'):
    plt.figure()
    if param == 'none':
        plt.imshow(img)
    if param == 'gray':
        plt.imshow(img, cmap=plt.cm.gray, vmin=0, vmax=255)
    plt.axis('off')


def threshold_alg(img, t_init, dT):  # t_init = initial threshold, dT = delta T
    t_previous = 0
    t = t_init
    s1 = []  # set of pixels where X > T
    s2 = []  # set of pixels where X <= T
    a = img.shape[0]
    b = img.shape[1]
    m1 = 0  # Mean of s1
    m2 = 0  # Mean of s2

    while (math.fabs(t - t_previous) > dT):
        for x in range(a):
            for y in range(b):
                if (img[x, y] > t):
                    s1.append(img[x, y])
                else:
                    s2.append(img[x, y])
        temp1 = 0
        for element in s1:
            temp1 += element
        m1 = temp1 / len(s1)

        temp2 = 0
        for element in s2:
            temp2 += element
        m2 = temp2 / len(s2)

        t_previous = t
        t = (m1 + m2) / 2

    return t


def avg_gsi(img):  # greyscale intensity
    a = img.shape[0]
    b = img.shape[1]

    avg = 0

    for x in range(a):
        for y in range(b):
            avg += img[x, y]

    return avg / (a * b)


def divide_by_thresh(img, t):
    a = img.shape[0]
    b = img.shape[1]

    divided_image = np.zeros([a, b], dtype=int)

    for x in range(a):
        for y in range(b):
            if (img[x, y] > t):
                divided_image[x, y] = 1;
            # No need for an else-statement to make [x,y] 0, seeing the image is already black

    return divided_image


def grow_seeds(img, seeds):
    # Takes in an image segmented in to two parts, labeled 1 and 0
    a = img.shape[0]
    b = img.shape[1]

    g = np.zeros([a, b], dtype=int)

    for seed in seeds:
        # Check surrounding pixels
        for y in range(-1, 2):
            for x in range(-1, 2):

                m = seed[1] + y
                n = seed[0] + x

                if (img[m, n] == 1):
                    g[m, n] = 255

    # To check if any occurences has happened to g
    prev_g = np.zeros([a, b], dtype=int)

    while (not (images_equal(prev_g, g))):  # Stop when they are the same, no more changes
        prev_g = np.copy(g)
        for y in range(b):
            for x in range(a):  # All pixels of img
                if (g[x, y] == 255):  # Here's a white pixel in g, try to grow it
                    for k in range(-1, 2):
                        for j in range(-1, 2):  # Check 8 surrounding pixels
                            if (x + j < a and y + k < b and img[
                                    x + j, y + k] == 1):  # Make sure we don't go past the edge
                                g[x + j, y + k] = 255

    return g


def images_equal(img1, img2):
    # 1 and 2 have to be the same size, obv
    a = img1.shape[0]
    b = img1.shape[1]

    for y in range(b):
        for x in range(a):
            if img1[x, y] != img2[x, y]:
                # No need to search anymore, not equal
                return False

    # Made it through the loop, all x,y pairs equal
    return True


image = read_img('images/defective_weld.tif')
image = image.astype(int)

print("Average greyscale intensity in image: ", avg_gsi(image))
t_init = 173
dT = 0.5
t = threshold_alg(image, t_init, dT)  # Experiment with t to refine segmentation
print("Determined threshold with values t_init =", t_init, ", dT =", dT, ":", t)

seeds = [[139, 255], [292, 251], [441, 236], [76, 289], [405, 236]]

plot_fig(image, 'gray')
div_img = divide_by_thresh(image, t)
seed_img = grow_seeds(div_img, seeds)
plot_fig(seed_img, 'gray')
misc.imsave("images/seed points.png", seed_img)
plt.show()



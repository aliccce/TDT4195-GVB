import numpy as np
from scipy import misc
import matplotlib.pyplot as plt
import math


def read_img(path):
    image = misc.imread(path)
    return image


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


def segmentation(image, threshold):
    return np.where(image > threshold, [1], [0])


image = read_img('images/defective_weld.tif')
image = image.astype(np.float32)
average_intensity = avg_gsi(image)

print("Average greyscale intensity in image: ", average_intensity)
t_init = average_intensity
dT = 0.5
threshold = threshold_alg(image, t_init, dT)
print("Determined threshold with values t_init =", t_init, ", dT =", dT, ":", threshold)

print(image.max(), image.min())


segmented_image = segmentation(image, threshold)

plt.imshow(segmented_image, cmap="gray")
misc.imsave("images/segmentation with threshold.png", segmented_image)
plt.show()

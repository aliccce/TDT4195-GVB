
import numpy as np
from scipy import misc
import matplotlib.pyplot as plt


def greyscale_2(path, weights=False):
    image = misc.imread(path)
    grey = np.zeros(image.shape[0:2])
    if weights:
        x = 0.2126
        y = 0.7152
        z = 0.0722

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            r = image[i, j][0]
            g = image[i, j][1]
            b = image[i, j][2]

            if weights:
                grey[i, j] = (x*r + y*g + z*b) / 255
            else:
                grey[i, j] = 1/3 * (r/255 + g/255 + b/255)

    return grey


def transformation(greyscale_im, p):

    new = np.zeros_like(greyscale_im)
    for i in range(greyscale_im.shape[0]):
        for j in range(greyscale_im.shape[1]):
            new[i, j] = greyscale_im[i, j] - p if 255 - p > 0 else 0
    return new


def grey_plotter(image):
    plt.figure()
    plt.imshow(image, interpolation='nearest', cmap=plt.cm.gray)
    plt.show()

im = greyscale_2(".\Cute-a-bunny.jpg")
print(im.shape)

im2 = misc.imread(".\Cute-a-bunny.jpg", flatten=True)

print(im2)

im3 = transformation(im2, 100)

print(im3)


_, ax = plt.subplots(1, 2)
ax[0].imshow(im2, cmap=plt.cm.gray)
ax[1].imshow(im3, cmap=plt.cm.gray)
ax[0].set_axis_off()
ax[1].set_axis_off()
plt.show()


#grey_plotter(im)





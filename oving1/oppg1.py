
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
    for y in range(greyscale_im.shape[1]):
        for x in range(greyscale_im.shape[0]):
            new[x, y] = greyscale_im[x, y] - p if 255 - p > 0 else 0

    #new = new / new.max()/255

    plt.figure()
    plt.imshow(new, interpolation='nearest', cmap=plt.cm.gray, vmin=0, vmax=255-p)
    plt.show()

    return new


def test(image):
    nb_rows = image.shape[0]
    nb_cols = image.shape[1]

    new_image = np.zeros_like(image)

    for y in range(nb_rows):
        for x in range(nb_cols):
            # Do something for each pixel here
            if y % 2 == 0 and x % 2 == 0:
                new_image[y, x] = image[y, x]

    plt.figure(figsize=(8, 8))
    plt.imshow(new_image, plt.cm.gray)
    plt.axis('off')
    plt.show()



def grey_plotter(image):
    plt.figure()
    plt.imshow(image, interpolation='nearest', cmap=plt.cm.gray)
    plt.show()




def convolution(image, kernel):
    # Make sure the kernel is actually a np.matrix. This way, the argument can be a two-dimensional python list.
    kernel = np.matrix(kernel)

    # Assuming n x n-kernel
    n = kernel.shape[0] // 2
    new_image = np.zeros_like(image)

    num_of_cols = image.shape[0]
    num_of_rows = image.shape[1]

    #Flips kernel, and runs correlation
    flipped_kernel = flip_kernel(kernel)

    for y in range(num_of_rows):
        for x in range(num_of_cols):
            # Iterates through each pixel in the image

            accumulator = 0

            for kernel_row in range(-n, n):
                for kernel_col in range(-n, n):
                    image_row = y + kernel_row
                    image_col = x + kernel_col

                    if image_row < 0 or image_row >= num_of_rows or image_col < 0 or image_col >= num_of_cols:
                        # Checks whether the kernel is at the edges of the image
                        accumulator += 0
                    else:
                        accumulator += image[image_col, image_row] * flipped_kernel[kernel_col, kernel_row]

            new_image[x, y] = np.float32(accumulator)
    return new_image


def flip_kernel(kernel):
    new_kernel = np.zeros_like(kernel)

    for y in range(1, kernel.shape[0] + 1):
        for x in range(1, kernel.shape[1] + 1):
            new_kernel[y - 1, x - 1] = kernel[-y, -x]

    return new_kernel



"""

n = 6
li = [[1]*5]*5
kernel = np.matrix(li)

im2 = misc.imread(".\Cute-a-bunny.jpg", flatten=True)

new_im = convolution(im2, kernel)


_, ax = plt.subplots(1, 2)
ax[0].imshow(im2, cmap=plt.cm.gray)
ax[1].imshow(new_im, cmap=plt.cm.gray)
ax[0].set_axis_off()
ax[1].set_axis_off()

misc.imsave('test.png', im2)
misc.imsave('test1.png', new_im)

plt.figure()
plt.imshow(new_im, interpolation="nearest", cmap=plt.cm.gray)
plt.show()

"""

im = greyscale_2(".\Cute-a-bunny.jpg")

print(im.shape)

im2 = misc.imread(".\Cute-a-bunny.jpg", flatten=True)




print(im2)

im3 = transformation(im2, 100)

print(im3)
misc.imsave('test.png', im3)
misc.imsave('test1.png', im2)

_, ax = plt.subplots(1, 2)
ax[0].imshow(im2, cmap=plt.cm.gray)
ax[1].imshow(im3, cmap=plt.cm.gray, vmax=im3.max(), vmin=im3.min())
ax[0].set_axis_off()
ax[1].set_axis_off()
plt.show()


#grey_plotter(im)





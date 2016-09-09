
import numpy as np
from scipy import misc
import matplotlib.pyplot as plt


def flip_kernel(kernel):
    new_kernel = np.zeros_like(kernel)

    for y in range(1, kernel.shape[0] + 1):
        for x in range(1, kernel.shape[1] + 1):
            new_kernel[y - 1, x - 1] = kernel[-y, -x]

    return new_kernel


def convolution(image, kernel):
    # Make sure the kernel is actually a np.matrix. This way, the argument can be a two-dimensional python list.
    kernel = np.matrix(kernel)

    # Assuming n x n-kernel
    n = kernel.shape[0] // 2
    new_image = np.zeros_like(image)

    num_of_rows = image.shape[0]
    num_of_cols = image.shape[1]

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
                        accumulator += image[image_row, image_col] * flipped_kernel[kernel_row, kernel_col]

            new_image[y, x] = np.float32(accumulator)
    return new_image


""" Create kernels """
box_blur = [[1/9]*3]*3

gaussian = [[1, 4, 6, 4, 1],
            [4, 16, 24, 16, 4],
            [6, 24, 36, 24, 6],
            [4, 16, 24, 16, 4],
            [1, 4, 6, 4, 1], ]

for i in range(len(gaussian)):
    for j in range(len(gaussian[i])):
        gaussian[i][j] /= 256

""" Read file """

image = misc.imread(".\Cute-a-bunny.jpg", flatten=True)

""" Do convolution """

box_blur_image = convolution(image, box_blur)
gaussian_image = convolution(image, gaussian)

""" Plot and save results """

_, ax = plt.subplots(1, 3)
ax[0].imshow(image, interpolation="nearest", cmap=plt.cm.gray)
ax[1].imshow(gaussian_image, interpolation="nearest", cmap=plt.cm.gray)
ax[2].imshow(box_blur_image, interpolation="nearest", cmap=plt.cm.gray)
ax[0].set_axis_off()
ax[1].set_axis_off()
ax[2].set_axis_off()


misc.imsave('oppg3-before.png', image)
misc.imsave('oppg3-box_blur.png', gaussian_image)
misc.imsave('oppg3-gaussian.png', box_blur_image)

plt.show()


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


def convolve_three_channels(r, g, b, kernel):
    new_r = convolution(r, kernel)
    print("... Convolved red channel")
    new_g = convolution(g, kernel)
    print("... Convolved green channel")
    new_b = convolution(b, kernel)
    print("... Convolved blue channel")
    return new_r, new_g, new_b


def rearrange_channels(r, g, b, image):
    print("... Rearranging")
    image[..., 0] = r
    image[..., 1] = g
    image[..., 2] = b
    return image

def calculate_magnitude(image_x, image_y):
    new_image = np.zeros_like(image_x)

    rows = image_x.shape[0]
    columns = image_x.shape[1]

    for y in range(rows):
        for x in range(columns):
            new_image[y, x] = np.sqrt(image_x[y, x]**2 + image_y[y, x]**2)

    return new_image




""" Create kernels """
sobel_x = [[1, 0, -1], [2, 0, -2], [1, 0, -1]]
sobel_y = [[1, 2, 1], [0, 0, 0], [-1, -2, -1]]

""" Read file """

image = misc.imread("./Cute-a-bunny.jpg", flatten=True)

resultx = convolution(image, sobel_x)
resulty = convolution(image, sobel_y)
magnitude = calculate_magnitude(resultx, resulty)


""" Plot and save results """

print("Plotting")
_, ax = plt.subplots(1, 3)
ax[0].imshow(resultx, cmap=plt.cm.gray, interpolation="nearest")
ax[1].imshow(resulty, cmap=plt.cm.gray, interpolation="nearest")
ax[2].imshow(magnitude, cmap=plt.cm.gray, interpolation="nearest")
ax[0].set_axis_off()
ax[1].set_axis_off()
ax[2].set_axis_off()

print("Saving")
misc.imsave('oppg3c-gradient-x.png', resultx)
misc.imsave('oppg3c-gradient-y.png', resulty)
misc.imsave('oppg3c-magnitude.png', magnitude)

plt.show()

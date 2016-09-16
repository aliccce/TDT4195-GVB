
import numpy as np
from scipy import misc, fftpack
import matplotlib.pyplot as plt


""" Functions for task 1a """


def magnitude_spectrum(fourier_shape):
    shift = fftpack.fftshift(fourier_shape)
    return 10*np.log10(np.abs(shift + 1))


def convolution_theorem(image, kernel):
    # Calculate the Fourier transformation of the image and the kernel
    # By specifying shape of kernel, the kernel is padded accordingly
    f_image = fftpack.fft2(image)
    f_kernel = fftpack.fft2(kernel, shape=image.shape)

    # Get the magnitude spectrum of the image, before filtering is done
    before = magnitude_spectrum(f_image)

    # Doing the multiplication
    f_image = np.multiply(f_image, f_kernel)

    # Magnitude spectrum after filtering is done
    after = magnitude_spectrum(f_image)

    # Calculating the inverse fourier transformation to get the image result
    result_image = fftpack.ifft2(f_image).real

    return result_image, before, after


""" Functions for task 1b """


def sharpen(image, kernel):
    # Assumes kernel is a sharpening kind (high pass)

    convolved_image = normalize(convolution_theorem(image, kernel)[0])

    return normalize(image + convolved_image)


""" General purpose-functions """





def normalize(image):

    image *= 255 / (image.max() - image.min())
    return image


def plot_pictures(*pictures):
    "Creates a plot of n pictures. Won't be optimal for n > 3 or 4 as the pictures will be very small."

    n = len(pictures)
    _, ax = plt.subplots(1, n)

    for i in range(n):
        ax[i].imshow(pictures[i], interpolation="nearest", cmap="gray")
        ax[i].set_axis_off()

    plt.show()


def save_pictures(*pictures, name=""):
    i = 0
    for picture in pictures:
        misc.imsave(name + str(i) + ".jpg", picture)
        i += 1


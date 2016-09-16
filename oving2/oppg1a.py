
from frequencyDomainFiltering import *

img = misc.imread("elephant.jpg", flatten=True)


low_pass_kernel = np.matrix([[1,  4,  6,  4, 1],
                             [4, 16, 24, 16, 4],
                             [6, 24, 36, 24, 6],
                             [4, 16, 24, 16, 4],
                             [1,  4,  6,  4, 1]]) * 1/256


high_pass_kernel = np.matrix([[0,  0, -1,  0,  0],
                              [0, -1, -2, -1,  0],
                              [-1, -2, 16, -2, -1],
                              [0, -1, -2, -1,  0],
                              [0,  0, -1,  0,  0], ])


# Use convolution theorem to convolve with a low pass filter
low_pass_image, low_pass_before, low_pass_after = convolution_theorem(img, low_pass_kernel)
plot_pictures(low_pass_image, low_pass_before, low_pass_after)

# Use convolution theorem to convolve with a high pass filter
high_pass_image, high_pass_before, high_pass_after = convolution_theorem(img, high_pass_kernel)
plot_pictures(high_pass_image, high_pass_before, high_pass_after)

# Saves pictures as 'oppg1a image-x.jpg'
save_pictures(low_pass_image, low_pass_before, low_pass_after,
              high_pass_image, high_pass_before, high_pass_after, name="oppg1a image-")

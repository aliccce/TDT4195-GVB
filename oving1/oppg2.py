
import numpy as np
from scipy import misc
import matplotlib.pyplot as plt


def invert(greyscale_im):

    transformed_image = np.zeros_like(greyscale_im)
    for y in range(greyscale_im.shape[1]):
        for x in range(greyscale_im.shape[0]):
            transformed_image[x, y] = 255 - greyscale_im[x, y]

    return transformed_image


def gamma(img, gamma):
    new_img = img.astype(np.float64)

    # Gamma equation: T(p) = cp^g, c > 0 and g > 0
    # We let c = 1

    rows = img.shape[0]
    cols = img.shape[1]

    for y in range(rows):
        for x in range(cols):
            new_img[x, y] = np.power(img[x, y], gamma)

    return new_img


def read_img(path):
    image = misc.imread(path)
    return image


def rgb2gray(img):
    new_img = np.zeros_like(image[..., 0])

    rows = img.shape[0]
    cols = img.shape[1]

    # Perception values
    red = 0.2126
    green = 0.7152
    blue = 0.0722

    for y in range(rows):
        for x in range(cols):
            r = float(img[x, y, 0])
            g = float(img[x, y, 1])
            b = float(img[x, y, 2])

            new_img[x, y] = r * red + g * green + b * blue

    return new_img


def plot_fig(img, param='none'):
    plt.figure()
    if param == 'none':
        plt.imshow(img)
    if param == 'gray':
        plt.imshow(img, cmap=plt.cm.gray, vmin=0, vmax=255)
    plt.axis('off')


def normalize(img):
    # We really should check that the image is not completely black to avoid division by 0, but were in a rush here

    rows = img.shape[0]
    cols = img.shape[1]

    for y in range(rows):
        for x in range(cols):
            img[x, y] = np.float64(img[x, y]) / 255.0
            break

    return img

""" Reads image and makes it greyscale """
image = read_img('./puppy.jpg')
image = rgb2gray(image)
image = image.astype(np.float32)

""" Perform function from task 2a """
inverted_image = invert(image)

""" Normalize and perform gamma function """
image = normalize(image)
darkened_image_with_gamma = gamma(image, 0.8)  # <1 darkens the picture
brightened_image_with_gamma = gamma(image, 1.2)  # >1 lightens the picture

""" Plot and save images """
plot_fig(image, 'gray')
plot_fig(darkened_image_with_gamma, 'gray')
plot_fig(brightened_image_with_gamma, 'gray')
plot_fig(inverted_image, 'gray')

plt.imsave('oppg2-inverted_image.png', inverted_image)
plt.imsave('oppg2-gamma-darker.png', darkened_image_with_gamma)
plt.imsave('oppg2-gamma-brighter.png', brightened_image_with_gamma)

plt.show()

import numpy as np
from scipy import misc
import matplotlib.pyplot as plt

def read_img(path):
	image = misc.imread(path)
	return image

def rgb2gray(img):

    new_img = np.zeros_like(image[...,0])

    rows = img.shape[0]
    cols = img.shape[1]

    #Perception values
    red = 0.2126
    green = 0.7152
    blue = 0.0722

    for y in range(cols):
        for x in range(rows):
            r = float(img[x,y,0])
            g = float(img[x,y,1])
            b = float(img[x,y,2])

            new_img[x,y] = r*red + g*green + b*blue

    return new_img

def plot_fig(img, param = 'none', title = ''):
	fig = plt.figure()

	if param == 'none':
		plt.imshow(img,)

	if param == 'gray':
		if len(img.shape) == 3:
			img = img.squeeze()

		plt.imshow(img, cmap=plt.cm.gray, vmin=0, vmax=255)

	fig.suptitle(title)
	plt.axis('off')

def linear_comb(img, kernel):

    new_img = img.astype(np.float64)

    kernel = np.array(kernel)

    a = kernel.shape[0]
    b = kernel.shape[1]

    c = img.shape[0]
    d = img.shape[1]

    #Center of the kernel is the median of its size
    center = np.median(np.array(range(a)))

    kernel_sum = 0
    for k in range(a):
        for l in range(b):
            kernel_sum += kernel[k][l]

    for m in range(1, c-1):
        for n in range(1, d-1):

            value = 0

            for y in range(a):
                for x in range(b):
                    #c-m,c-n er der kernel-senteret befinner seg til enhver tid.
                    value += img[m-c+y][n-d+x] * kernel[x][y]

            new_img[m][n] = value/kernel_sum 

    return new_img 

def search_cols(img):

    """
    green:355, 50
    yellow:440, 30
    red:750, 80
    black:555, 150
    purple:460, 450
    white:365, 255
    """

    """
    print 'green:', cols_at_coord(img, 355, 50)
    print 'yellow:', cols_at_coord(img, 440, 30)
    print 'black:', cols_at_coord(img, 555, 150)
    print 'purple:', cols_at_coord(img, 460, 450)
    print 'white:', cols_at_coord(img, 255, 255)
    """

    a = img.shape[0] #height
    b = img.shape[1] #width

    new_img = np.zeros_like(image[...,0])

    prev_col = -1
    curr_col = -3

    for y in range(a):
        for x in range(b):
            curr_col = img[y][x]
            if curr_col == prev_col:
                new_img[y][x] = 0
            else:
                new_img[y][x] = 255
            prev_col = curr_col

    return new_img

    #in square 0: x:0-100, y:0-100

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


kernel3 = [ [1, 2, 1],
            [2, 4, 2],
            [1, 2, 1] ]

kernel5 = [  [1,4,6,4,1],
            [4,16,24,16,4],
            [6,24,36,24,6],
            [4,16,24,16,4],
            [1,4,6,4,1] ]

image = read_img('./images/easy01.png')
grey_img = rgb2gray(image)
grey_img = linear_comb(grey_img, kernel5)

new_image = search_cols(grey_img)

plot_fig(grey_img, 'gray', 'grey')

plot_fig(image, 'none', 'original')
plot_fig(new_image, 'gray', 'experiment')

plt.show()

#plt.savefig('filename')
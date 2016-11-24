import numpy as np
from scipy import misc
import matplotlib.pyplot as plt

from scipy import misc, fftpack, ndimage

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

def threshold(im, a=255/2, max=255):
    new = np.where(im > a, max, 0)
    return new

def remove_small_elements(image, structure=None):
    new_image = ndimage.morphology.binary_opening(image, structure=structure, iterations=1).astype(int)
    return new_image

def manhattan_dist(col1, col2):
    dist = np.absolute(int(col1[0]) - int(col2[0])) + np.absolute(int(col1[1]) - int(col2[1])) + np.absolute(int(col1[2]) - int(col2[2]))
    return dist

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

def calculate_magnitude(image_x, image_y):
    new_image = np.zeros_like(image_x)

    rows = image_x.shape[0]
    columns = image_x.shape[1]

    for y in range(rows):
        for x in range(columns):
            new_image[y, x] = np.sqrt(image_x[y, x]**2 + image_y[y, x]**2)

    return new_image



def fig_in_square(img, binary, y, x):


    pixels = []
    #Should pick its sample node base on a good guess
    
    dom_col = None
    #dom_col = [img[50][350][0], img[50][350][1], img[50][350][2]]
    square_size = 100

    a = img.shape[0] #y, i, a
    b = img.shape[1]
    print "y,x:", y * square_size, x * square_size
    #The +/- 2 is to avoid the pixels on the edges
    for i in range(y * square_size + 2, y * square_size + 100 - 2):
        for j in range(x * square_size + 2, x * square_size + 100 - 2):
            
                if binary[i][j] == 255: #Found white
                    pixels.append([i, j])

    print "len(pixels): ", len(pixels)
    if (len(pixels) > 100): #consider there to be enough pixels to be a figure

        #Pick the pixel with the most neighbors as reference
        sample_x = x * square_size + square_size / 2
        sample_y = y * square_size + square_size / 2
        sample = img[sample_y][sample_x]
        dom_col = [sample[0], sample[1], sample[2]]


        best_score = float('inf')
        best_col = None
        for test_col in colors:
            score = manhattan_dist(colors[test_col], dom_col)
            if(score < best_score):
                best_score = score
                best_col = test_col

        print(best_col, shapes[best_col])

        #And then we need to find center somehow - average of everything?

        sum_x = 0
        sum_y = 0
        center_x = 0
        center_y = 0
        string = str(y) + " " + str(x) + " " + str(shapes[best_col]) + " " + str(center_x) + " " + str(center_y)
        return string

    else:
        print "Not enough white to consider a figure"
        return ""

"""Some kernels"""

kernel3 = [ [1, 2, 1],
            [2, 4, 2],
            [1, 2, 1] ]

kernel5 = [  [1,4,6,4,1],
            [4,16,24,16,4],
            [6,24,36,24,6],
            [4,16,24,16,4],
            [1,4,6,4,1] ]

sobel_x = [[1, 0, -1], [2, 0, -2], [1, 0, -1]]
sobel_y = [[1, 2, 1], [0, 0, 0], [-1, -2, -1]]

test_x = [[-1, 1], [-1, 1]]
test_y = [[1, 1], [-1, -1]]

"""Shapes"""

global shapes
shapes = {

    "white":0,       #hex1
    "blue":1,        #star
    "red":2,         #pacman
    "yellow":3,      #triangle2
    "purple":4,      #triangle1
    "green":5,       #trapez
    "black":6,       #hex2
}

"""Colors"""

global colors
colors = {
    "white":[170, 170, 170],
    "blue":[70, 60, 115],
    "red":[210,60,40],
    "yellow":[215, 185, 45],
    "purple":[135, 30, 95],
    "green":[100,145,65],
    "black":[30, 30, 30],
}


#image = read_img('./images/easy01.png')
path = './images/easy01.png'
image = misc.imread(path, flatten = True)
image_color = misc.imread(path)

image = linear_comb(image, kernel3)

resultx = convolution(image, sobel_x)
resulty = convolution(image, sobel_y)
magnitude = calculate_magnitude(resultx, resulty)

thresholded = threshold(magnitude, a = 25)

"""
#Noise reduction
thresholded1 = threshold(thresholded, max=1)
print thresholded1
clean_thresh = remove_small_elements(thresholded, structure = [[1,1],[1,1]])
print clean_thresh
clean_thresh = threshold(clean_thresh, a=0.5, max=255)
print clean_thresh
"""

#Iterate over in 100s (squares) to see who belong together
height = magnitude.shape[0]
width = magnitude.shape[1]
squares_y = height / 100
squares_x = width / 100

#Write to file
filepath = './communication.txt'
f = open(filepath, 'w')

for x in range(squares_x):
    for y in range(squares_y):
        writestring = fig_in_square(image_color, thresholded, y, x)
        if(writestring != ""):
            f.write(writestring)
            f.write('\n')

f.close()


plot_fig(magnitude, 'gray', 'magn')
plot_fig(image, 'gray', 'image')
plot_fig(resultx, 'gray', 'sobel_x')
plot_fig(resulty, 'gray', 'sobel_y')
plot_fig(thresholded, 'gray', 'thresholded')
#plot_fig(clean_thresh, 'gray', 'clean_thresh')
plot_fig(image_color, 'none', 'color')

plt.show()

#plt.savefig('filename')
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

	for y in range(rows):
		for x in range(cols):
			r = float(img[x,y,0])
			g = float(img[x,y,1])
			b = float(img[x,y,2])

			new_img[x,y] = r*red + g*green + b*blue

	return new_img

def flip_kernel(kernel):
	
	for array in kernel:
		kernel[kernel.index(array)] = list(reversed(array))
	
	kernel = kernel[::-1]

	#Will be easier to write all entries in order, then reverse them and put them back in rows and columns

	return kernel

def linear_comb(img, kernel):

	new_img = img.astype(np.float64)

	kernel = np.array(flip_kernel(kernel))
	
	a = kernel.shape[0]
	b = kernel.shape[1]

	c = img.shape[0]
	d = img.shape[1]

	center = np.median(np.array(range(a)))

	kernel_sum = 0
	for x in range(a):
		for y in range(b):
			kernel_sum += kernel[x,y]

	for m in range(1, c-1):
		for n in range(1, d-1):

			value = 0

			for y in range(a):
				for x in range(b):
					#c-m,c-n er der kernel-senteret befinner seg til enhver tid.
					#print c-m+y, c-n+x
					value += img[m-c+y, n-c+x]*kernel[x,y]

			new_img[m, n] = value/kernel_sum

	return new_img

def convolve(image, kernel):

	new_img = image.astype(np.float64)
	new_img = linear_comb(new_img, kernel)
	
	return new_img

def plot_fig(img, param = 'none'):
	plt.figure()
	if param == 'none':
		plt.imshow(img)
	if param == 'gray':
		plt.imshow(img, cmap=plt.cm.gray, vmin=0, vmax=255)
	plt.axis('off')


image = read_img('/home/maren/MTDT/TDT4195/images/sitting.jpg')
image = rgb2gray(image)
image = image.astype(np.float32)

#Gaussian
kernel = [	[1,4,6,4,1],
			[4,16,24,16,24],
			[6,24,36,24,6],
			[4,16,24,16,24],
			[1,4,6,4,1] ]

new_image = convolve(image, kernel)

plot_fig(image, 'gray')
plot_fig(new_image, 'gray')

plt.show()

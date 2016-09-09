import numpy as np
from scipy import misc
import matplotlib.pyplot as plt

def read_img(path):
	image = misc.imread(path)
	return image

def plot_fig(img, param = 'none'):
	plt.figure()
	if param == 'none':
		plt.imshow(img,)
	if param == 'gray':
		plt.imshow(img, cmap=plt.cm.gray, vmin=0, vmax=255)
	plt.axis('off')

def transform1(img, new_img):

	rows = img.shape[0]
	cols = img.shape[1]
	
	for y in range(rows):
		for x in range(cols):
			r = int(img[x,y,0])
			g = int(img[x,y,1])
			b = int(img[x,y,2])

			new_img[x,y] = (r+g+b)/3	
	
	return new_img

def transform2(img, new_img):

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

def gen_diff(img1, img2, diff):
	
	rows = img1.shape[0]
	cols = img1.shape[1]

	for y in range(rows):
		for x in range(cols):

			diff[x,y] = 255

			if img1[x,y] != img2[x,y]:
				diff[x,y] = 0

image = read_img('/home/maren/MTDT/TDT4195/images/kitten.jpg')

plot_fig(image)

plot_fig(image)

new_image1 = np.zeros_like(image[...,0])
new_image2 = np.zeros_like(image[...,0])
diff = np.zeros_like(image[...,0])

transform1(image, new_image1)
transform2(image, new_image2)

plot_fig(new_image1, 'gray')
plot_fig(new_image2, 'gray')

gen_diff(new_image1, new_image2, diff)

plot_fig(diff, 'gray')
plt.show()

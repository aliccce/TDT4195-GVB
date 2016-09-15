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


"""
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
"""

def downsample_m(img, m):

    #new_img = img.astype(np.float64)
	
    a = img.shape[0]
    b = img.shape[1]
    
    new_img = np.zeros([a/m,a/m,1],dtype=np.float64)
    #new_img = rgb2gray(new_img)
    new_img.fill(255)
    new_img = new_img.astype(np.float64)

    c = new_img.shape[0]
    d = new_img.shape[1]

    for x in range(a-1):
		for y in range(b-1):
			#Keep only values where n are multiples of M
			if (x % m == 0 and y % m == 0):
				new_img[x/m,y/m] = img[x,y]

    return new_img


#Gaussian
kernel = [  [1,4,6,4,1],
            [4,16,24,16,4],
            [6,24,36,24,6],
            [4,16,24,16,4],
            [1,4,6,4,1] ]

image = read_img('./images/bricks.tiff')
image = rgb2gray(image)
#lp = lowpass, to avoid aliasing
#lp_image = linear_comb(image, kernel)
#Keep every second row and column
#ds = downsampled
ds_image = downsample_m(image, 2)

plot_fig(image, 'gray', 'original')
plt.savefig('original_grey_a')
plot_fig(ds_image, 'gray', 'downsampled')
plt.savefig('downsampled_a')

plt.show()

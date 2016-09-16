
from frequencyDomainFiltering import *

img1 = misc.imread("angry.jpg", flatten=True)
img2 = misc.imread("happy.jpg", flatten=True)

low_pass_kernel = np.matrix([[1, 2, 1], [2, 4, 2], [1, 2, 1]]) * 1/16


high_pass_kernel = 1 - low_pass_kernel


high_pass_image = convolution_theorem(img1, high_pass_kernel)[0]
low_pass_image = convolution_theorem(img2, low_pass_kernel)[0]


hybrid_image = high_pass_image + low_pass_image

save_pictures(img1, img2, hybrid_image, name="oppg2c image-")

plt.imshow(hybrid_image, cmap="gray")
plt.show()

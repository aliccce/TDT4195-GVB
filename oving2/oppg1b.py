
from frequencyDomainFiltering import *

image = misc.imread("elephant.jpg", flatten=True)

laplace = np.matrix([[0, -1, 0], [-1, 4, -1], [0, -1, 0]])

sharpened_image = sharpen(image, laplace)

save_pictures(image, sharpened_image, name='oppg1b image-')
plot_pictures(image, sharpened_image)


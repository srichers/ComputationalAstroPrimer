import numpy as np
from mpl_toolkits.axes_grid1 import make_axes_locatable
import matplotlib.pyplot as plt
import matplotlib as mpl
import skimage.filters

# NOTE: all distance units EVERYWHERE should be in megameters (Mm)

#========#
# STEP 1 #
#========#
# Read the introduction and Fig. 5 of Riutord et al. (2010) "On the Power Spectrum of Solar Surface Flows"
# Fill in the range of length scales that solar supergranulation occurs on in units of megameters.
# These are the numbers we will compare our results against.
Mm = 1e8 # cm
#l_supergranulation = np.array([ FILL_ME_IN, FILL_ME_IN])
#l_granulation      = np.array([ FILL_ME_IN, FILL_ME_IN])

#========#
# STEP 2 #
#========#
# Read in the data using imread and set the data to the variable f
# The second line stores the number of pixels in the x and y directions
# Run the script and save the result as "step2.pdf"
f = plt.imread("sample.tif")
Nx,Ny = np.shape(f)

#========#
# STEP 3 #
#========#
# normalize the data to a brightness from 0 to 1 by dividing by the maximum brightness
# Run the script and save the result as "step3.pdf"
#f = f / FILL_ME_IN

#========#
# STEP 4 #
#========#
# Cut off extra space around the sun
# Just un-comment the following lines.
# This works by finding the box containing all pixels more than 15% as bright as the brightest pixel
# Run the script and save the result as "step4.pdf"
#max_x = np.squeeze(np.max(f, axis=FILL_ME_IN))
#max_y = np.squeeze(np.max(f, axis=FILL_ME_IN))
#xlocs = np.squeeze(np.where(FILL_ME_IN))
#ylocs = np.squeeze(np.where(FILL_ME_IN))
#i0 = xlocs[FILL_ME_IN]
#i1 = xlocs[FILL_ME_IN]
#j0 = ylocs[FILL_ME_IN]
#j1 = ylocs[FILL_ME_IN]
#f = f[FILL_ME_IN:FILL_ME_IN, FILL_ME_IN:FILL_ME_IN]
#Nx,Ny = np.shape(f)

#========#
# STEP 5 #
#========#
# make arrays for x and y in units of megameters
# The size of the diameter of the sun.
# Run the script and save the result as "step5.pdf"
#Rsun = FILL_ME_IN
#x = FILL_ME_IN
#y = FILL_ME_IN

#========#
# STEP 8 #
#========#
# Cut 1/4 of the image around the whole border.
# This gets rid of any empty space in the image.
# refine the area to 1/4 of the size of the sun
# Run the script and save the result as "step8.pdf"
#border_cut = Nx//4
#i0 = FILL_ME_IN
#i1 = FILL_ME_IN
#j0 = FILL_ME_IN
#j1 = FILL_ME_IN
#f = f[FILL_ME_IN:FILL_ME_IN, FILL_ME_IN:FILL_ME_IN]
#x = x[FILL_ME_IN:FILL_ME_IN]
#y = y[FILL_ME_IN:FILL_ME_IN]
#Nx,Ny = np.shape(f)

#=========#
# STEP 10 #
#=========#
# Skip over this step until steps 1-9 are done
# Replace the image data with an array of random numbers using np.random.rand
# We will use this to judge what part of the power spectrum is an artifact of the window function
# Run the script and save the result as "step10.pdf"
#f = FILL_ME_IN

#========#
# STEP 9 #
#========#
# Apply a window function to the data
# We will use the Kaiser window with a parameter of 14
# Use the skimage.filters.window function
# Run the script and save the result as "step9.pdf"
# use the function skimage.filters.window
#window_function = ('kaiser', 14)
#f = FILL_ME_IN

#========#
# STEP 6 #
#========#
# Calculate the fourier transform using np.fft.fftn
# use the function np.fft.fftn
# Divide the result by (Nx * Ny) so it does not depend on the number of pixels
#fft = FILL_ME_IN

# Define the maximum possible wavenumber based on the Nyquist theorem.
# This should be 2*pi / (twice the pixel size)
# The values should be in 1/Mm
#kmax_x = FILL_ME_IN
#kmax_y = FILL_ME_IN

# Define the wavenumber arrays using np.fft.fftfreq.
# Convert the wavenumber arrays from code units (the largest wavenumber will be 0.5) to physical units (the largest wavenumber should  be the maximum wavenumber you defined above.
# use the function np.fft.fftfreq
#kx = FILL_ME_IN
#ky = FILL_ME_IN

# Run the script and save the result as "step6.pdf"

#========#
# STEP 7 #
#========#
# Compute the power spectrum
# First, we need |fft|^2 for every value of (kx, ky)
# use the function np.abs
#fft2 = FILL_ME_IN

# Second, we need the value of |k| for every value of (kx, ky)
# use np.newaxis and the function np.sqrt
#kmag = FILL_ME_IN

# Third, we need to define the k grid we will use for our histogram.
# We will just use the kx array, but only include the positive values of kx
# use the function np.where
#kgrid = kx[FILL_ME_IN]

# Finally, use np.histogram to add up all of the "Fourier power" in each k bin
# use flatten() on all input arrays to remove unit-sized dimensions
#power_spectrum, kgrid = np.histogram(FILL_ME_IN, FILL_ME_IN, weights=FILL_ME_IN)

# Run the script and save the result as "step7.pdf"

#====================================#
# NO NEED TO MODIFY BELOW THIS POINT #
#====================================#
# Plotting Commands
mpl.rcParams['font.size'] = 16
mpl.rcParams['font.family'] = 'serif'
mpl.rc('text', usetex=True)
mpl.rcParams['xtick.major.size'] = 7
mpl.rcParams['xtick.major.width'] = 2
mpl.rcParams['xtick.major.pad'] = 8
mpl.rcParams['xtick.minor.size'] = 4
mpl.rcParams['xtick.minor.width'] = 2
mpl.rcParams['ytick.major.size'] = 7
mpl.rcParams['ytick.major.width'] = 2
mpl.rcParams['ytick.minor.size'] = 4
mpl.rcParams['ytick.minor.width'] = 2
mpl.rcParams['axes.linewidth'] = 2   
fig,axes = plt.subplots(3,1,figsize=(8,16))
if 'x' in globals():
    im1 = axes[0].imshow(f.T,extent=[x[0],x[-1],y[0],y[-1]])
    axes[0].set_xlabel("$x\,(\mathrm{Mm})$")
    axes[0].set_ylabel("$y\,(\mathrm{Mm})$")
else:
    im1 = axes[0].imshow(f.T)
divider = make_axes_locatable(axes[0])
cax0 = divider.append_axes("right", size="5%", pad=0.05)
plt.colorbar(im1, cax=cax0,label=r"$f$")
axes[1].set_xlabel("$k_x\,(\mathrm{Mm}^{-1})$")
axes[1].set_ylabel("$k_y\,(\mathrm{Mm}^{-1})$")
divider = make_axes_locatable(axes[1])
cax1 = divider.append_axes("right", size="5%", pad=0.05)
if 'fft' in globals():
    fft_shifted = np.fft.fftshift(fft)
    im2 = axes[1].imshow(np.log(np.abs(fft_shifted)).T,extent=[-kmax_x,kmax_x,-kmax_y,kmax_y])
    plt.colorbar(im2, cax=cax1,label=r"$\ln|\widetilde{f}|$")
axes[2].set_xlabel(r"$1/\lambda\,(\mathrm{Mm}^{-1})$")
axes[2].set_ylabel("$\mathcal{F}$")
if 'power_spectrum' in globals():
    axes[2].loglog(kgrid[:-1]/(2.*np.pi),power_spectrum)
    axes[2].text(1./l_supergranulation[1],np.max(power_spectrum)/2.,"supergranulation",va='center')
    axes[2].text(1./l_granulation[1],np.max(power_spectrum)/2.,"granulation",va='top',rotation=-90)
    axes[2].axvspan(1./l_supergranulation[0] , 1./l_supergranulation[1], alpha=0.25)
    axes[2].axvspan(1./l_granulation[0] , 1./l_granulation[1], alpha=0.25)
for ax in axes:
    ax.minorticks_on()
    ax.tick_params(axis='both',which='both',direction='in',right=True,top=True)
cax0.tick_params(axis='both',which='both',direction='in')
cax1.tick_params(axis='both',which='both',direction='in')
cax0.minorticks_on()
cax1.minorticks_on()
plt.savefig("FFT_2D.pdf",bbox_inches="tight")
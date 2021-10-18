import numpy as np
from mpl_toolkits.axes_grid1 import make_axes_locatable
import matplotlib.pyplot as plt
from skimage.filters import window

# granule length scales based on Rincon 2018 "The Sun's Supergranulation"
Mm = 1e8 # cm
l_supergranulation = np.array([ 30e8/Mm,  35e8/Mm])# cm (20 hr lifetime)
Rsun = 6.957e10/Mm # cm

# read in the data
f = plt.imread("sample.tif")
Nx,Ny = np.shape(f)

# normalize the data to a brightness from 0 to 1
f = f / np.max(f)

# get box bounding the sun
threshold = 0.1
max_x = np.squeeze(np.max(f, axis=1))
max_y = np.squeeze(np.max(f, axis=0))
xlocs = np.squeeze(np.where(max_x>threshold))
ylocs = np.squeeze(np.where(max_y>threshold))
i0 = xlocs[0]
i1 = xlocs[-1]
j0 = ylocs[0]
j1 = ylocs[-1]
f = f[i0:i1, j0:j1]
Nx,Ny = np.shape(f)

# make x and y arrays (units of Mm)
x = np.arange(Nx)/Nx * 2.*Rsun
y = np.arange(Ny)/Ny * 2.*Rsun

# refine the area to 1/4 of the size of the sun
i0 =   Nx//4
i1 = 3*Nx//4
j0 =   Ny//4
j1 = 3*Ny//4
f = f[i0:i1, j0:j1]
x = x[i0:i1]
y = y[j0:j1]
Nx,Ny = np.shape(f)

# (d) Apply a window function to the data
window_function = ('kaiser', 14)
f = f * window(window_function, f.shape)

# (b) Calculate fft(k) using scipy.fft.fftn
fft = np.fft.fftn(f) / (Nx * Ny)

kmax_x = np.pi / (x[1] - x[0])
kmax_y = np.pi / (y[1] - y[0])

kx = np.fft.fftfreq(Nx) * 2.*kmax_x
ky = np.fft.fftfreq(Ny) * 2.*kmax_y

# (c) Compute the 1D Power Spectrum
fft2 = np.abs(fft)**2
kmag = np.sqrt(kx[:,np.newaxis]**2 + ky[np.newaxis,:]**2)
kgrid = kx[np.where(kx>=0)]
power_spectrum_squared, kgrid = np.histogram(kmag.flatten(), kgrid, weights=fft2.flatten())

# Plotting Commands
fig,axes = plt.subplots(3,1,figsize=(8,16))
im1 = axes[0].imshow(f.T,extent=[x[0],x[-1],y[0],y[-1]])
axes[0].set_xlabel("$x$")
axes[0].set_ylabel("$y$")
divider = make_axes_locatable(axes[0])
cax = divider.append_axes("right", size="5%", pad=0.05)
plt.colorbar(im1, cax=cax,label=r"$f(x,y)$")
fft_shifted = np.fft.fftshift(fft)
im2 = axes[1].imshow(np.log(np.abs(fft_shifted)).T,extent=[-kmax_x,kmax_x,-kmax_y,kmax_y])
axes[1].set_xlabel("$k_x$")
axes[1].set_ylabel("$k_y$")
divider = make_axes_locatable(axes[1])
cax = divider.append_axes("right", size="5%", pad=0.05)
plt.colorbar(im2, cax=cax,label=r"$\log|\widetilde{f}|(k_x,k_y)$")
axes[2].set_xlabel(r"$|k|$")
axes[2].set_ylabel("$\mathcal{F}(|k|)$")
axes[2].semilogy(kgrid[:-1],np.sqrt(power_spectrum_squared))
#axes[2].axvspan(l_granulation[0]      , l_granulation[1]     , alpha=0.25)
axes[2].axvspan(2.*np.pi/l_supergranulation[0] , 2.*np.pi/l_supergranulation[1], alpha=0.25)
plt.savefig("FFT_2D.pdf",bbox_inches="tight")

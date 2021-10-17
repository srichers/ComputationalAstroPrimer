import numpy as np
from mpl_toolkits.axes_grid1 import make_axes_locatable
import matplotlib.pyplot as plt
from skimage.filters import window

# (a) Create an array of f(x,y) = sin(x) + cos(2y)
# where x and y are both in the range [0,10*pi) and using 200 points for each
Nx = 200
xstart = 0
xstop = 10.*np.pi
xstep = (xstop - xstart) / Nx
x = np.arange(xstart, xstop, xstep)

Ny = 200
ystart = 0
ystop = 10.*np.pi
ystep = (ystop - ystart) / Ny
y = np.arange(ystart, ystop, ystep)

f = np.sin(x)[:,np.newaxis] + np.cos(2.*y)[np.newaxis,:]

# (d) Apply a window function to the data
window_function = ('kaiser', 14)
f = f * window(window_function, f.shape)

# (b) Calculate fft(k) using scipy.fft.fftn
fft = np.fft.fftn(f) / (Nx * Ny)
kmax_x = np.pi / xstep
kx = np.fft.fftfreq(Nx) * 2.*kmax_x
kmax_y = np.pi / ystep
ky = np.fft.fftfreq(Ny) * 2.*kmax_y

# (c) Compute the 1D Power Spectrum
fft2 = np.abs(fft)**2
kmag = np.sqrt(kx[:,np.newaxis]**2 + ky[np.newaxis,:]**2)
kgrid = kx[np.where(kx>=0)]
power_spectrum_squared, kgrid = np.histogram(kmag.flatten(), kgrid, weights=fft2.flatten())

# Plotting Commands
fig,axes = plt.subplots(3,1,figsize=(8,16))
im1 = axes[0].imshow(f.T,extent=[xstart,xstop,ystart,ystop])
axes[0].set_xlabel("$x$")
axes[0].set_ylabel("$y$")
divider = make_axes_locatable(axes[0])
cax = divider.append_axes("right", size="5%", pad=0.05)
plt.colorbar(im1, cax=cax,label=r"$f(x,y)$")
fft_shifted = np.fft.fftshift(fft)
im2 = axes[1].imshow(np.abs(fft_shifted).T,extent=[-kmax_x,kmax_x,-kmax_y,kmax_y])
axes[1].set_xlabel("$k_x$")
axes[1].set_ylabel("$k_y$")
divider = make_axes_locatable(axes[1])
cax = divider.append_axes("right", size="5%", pad=0.05)
plt.colorbar(im2, cax=cax,label=r"$|\widetilde{f}|(k_x,k_y)$")
axes[2].set_xlabel(r"$|k|$")
axes[2].set_ylabel("$\mathcal{F}(|k|)$")
axes[2].semilogy(kgrid[:-1],np.sqrt(power_spectrum_squared))
plt.savefig("FFT_2D.pdf",bbox_inches="tight")


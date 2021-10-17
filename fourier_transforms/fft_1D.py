import numpy as np
import matplotlib.pyplot as plt
from skimage.filters import window

# (a) Create an array of 1000 values in the range of [0,20*pi)
npoints = 200
xstart = 0
xstop = 10.*np.pi
xstep = (xstop - xstart) / npoints
x = np.arange(xstart, xstop, xstep)

# (b) Create an array of f(x) = sin(x) values
f = np.sin(x)

# apply window function
window_function = ('kaiser', 14)
f = f * window(window_function, f.shape)

# (d) Calculate fft(k) using scipy.fft.fftn
fft = np.fft.fftn(f) / npoints
kmax = np.pi / xstep
k = np.fft.fftfreq(npoints) * 2.*kmax

# (c) Compute the 1D Power Spectrum
fft2 = np.abs(fft)**2
kmag = np.abs(k)
kgrid = k[np.where(k>=0)]
power_spectrum_squared, kgrid = np.histogram(kmag.flatten(), kgrid, weights=fft2.flatten())

# Plotting Commands
fig,axes = plt.subplots(3,1,figsize=(8,12))
axes[0].plot(x,f)
axes[0].set_xlabel("$x$")
axes[0].set_ylabel("$f(x)$")
fft_shifted = np.fft.fftshift(fft)
k_shifted = np.fft.fftshift(k)
axes[1].plot(k_shifted,np.abs(fft_shifted))
axes[1].set_xlabel("$k$")
axes[1].set_ylabel("$|\widetilde{f}|(k)$")
axes[2].plot(kgrid[:-1],np.sqrt(power_spectrum_squared))
axes[2].set_xlabel(r"$|k|$")
axes[2].set_ylabel(r"$\mathcal{F}(|k|)$")
plt.savefig("FFT_1D.pdf")

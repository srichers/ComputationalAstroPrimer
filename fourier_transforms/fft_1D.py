import numpy as np
#import scipy
import matplotlib.pyplot as plt

# Two-plot setup
fig,axes = plt.subplots(2,1,figsize=(8,8))

# (a) Create an array of 1000 values in the range of [0,20*pi)
npoints = 200
xstart = 0
xstop = 10.*np.pi
xstep = (xstop - xstart) / npoints
x = np.arange(xstart, xstop, xstep)

# (b) Create an array of f(x) = sin(x) values
f = np.sin(x)

# (c) Plot f(x)
axes[0].plot(x,f)
axes[0].set_xlabel("$x$")
axes[0].set_ylabel("$f(x)$")

# (d) Calculate fft(k) using scipy.fft.fftn
fft = np.fft.fftn(f)
kmax = 2.*np.pi / (2.*xstep)
k = np.fft.fftfreq(npoints) * 2.*kmax

# (e) Shift the order of the data in fft and k to make more sense
fft_shifted = np.fft.fftshift(fft)
k_shifted = np.fft.fftshift(k)

# (f) plot |fft|(k)
axes[1].plot(k_shifted,np.abs(fft_shifted))
axes[1].set_xlabel("$k$")
axes[1].set_ylabel("$\widetilde{f}(k)$")

# save the figure
plt.savefig("FFT_1D.pdf")

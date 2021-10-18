import numpy as np
from mpl_toolkits.axes_grid1 import make_axes_locatable
import matplotlib.pyplot as plt
import matplotlib as mpl
from skimage.filters import window

# granule length scales based on Rincon 2018 "The Sun's Supergranulation"
Mm = 1e8 # cm
l_supergranulation = np.array([ 12.5,  75])# Fig. 5, Riutord+(2010) "On the Power Spectrum..."
l_granulation      = np.array([  1.5, 2.0]) # cm (0.2 hr lifetime)
Rsun = 6.957e10/Mm # cm

# read in the data
f = plt.imread("sample.tif")
Nx,Ny = np.shape(f)

# normalize the data to a brightness from 0 to 1
#f = f / np.max(f)

# get box bounding the sun
#threshold = 0.15
#max_x = np.squeeze(np.max(f, axis=1))
#max_y = np.squeeze(np.max(f, axis=0))
#xlocs = np.squeeze(np.where(max_x>threshold))
#ylocs = np.squeeze(np.where(max_y>threshold))
#i0 = xlocs[0]
#i1 = xlocs[-1]
#j0 = ylocs[0]
#j1 = ylocs[-1]
#f = f[i0:i1, j0:j1]
#Nx,Ny = np.shape(f)

# make x and y arrays (units of Mm)
#x = np.arange(Nx)/Nx * 2.*Rsun
#y = np.arange(Ny)/Ny * 2.*Rsun

# refine the area to 1/4 of the size of the sun
#border_cut = Nx//4
#i0 =   border_cut
#i1 = Nx - border_cut
#j0 =   border_cut
#j1 = Ny - border_cut
#f = f[i0:i1, j0:j1]
#x = x[i0:i1]
#y = y[j0:j1]
#Nx,Ny = np.shape(f)

# Randomize the data to see the impact of the window function
#f = np.random.rand(Nx,Ny)

# (d) Apply a window function to the data
#window_function = ('kaiser', 14)
#f = f * window(window_function, f.shape)

# (b) Calculate fft(k) using scipy.fft.fftn
#fft = np.fft.fftn(f) / (Nx * Ny)

#kmax_x = np.pi / (x[1] - x[0])
#kmax_y = np.pi / (y[1] - y[0])

#kx = np.fft.fftfreq(Nx) * 2.*kmax_x
#ky = np.fft.fftfreq(Ny) * 2.*kmax_y

# (c) Compute the 1D Power Spectrum
#fft2 = np.abs(fft)**2
#kmag = np.sqrt(kx[:,np.newaxis]**2 + ky[np.newaxis,:]**2)
#kgrid = kx[np.where(kx>=0)]
#power_spectrum, kgrid = np.histogram(kmag.flatten(), kgrid, weights=fft2.flatten())

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

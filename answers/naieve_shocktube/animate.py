import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib as mpl

total_time = 5 # s

#==============#
# plot options #
#==============#
mpl.rcParams['font.size'] = 22
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

#===============#
# read the data #
#===============#
filename = "output.dat"
it = np.genfromtxt(filename, usecols=(0))
t = np.genfromtxt(filename, usecols=(1))
x = np.genfromtxt(filename, usecols=(4))
rho = np.genfromtxt(filename, usecols=(5))
eint = np.genfromtxt(filename, usecols=(6))
px = np.genfromtxt(filename, usecols=(7))

fig, axes = plt.subplots(3,1)
plt.subplots_adjust(wspace=0, hspace=0)

initial = np.where(it==0)

rhoplot, = axes[0].plot([],[],'r', lw=2)
axes[0].set_ylim(0, np.max(rho[initial])*1.1)
axes[0].set_xlim(0, np.max(x))
axes[0].set_ylabel(r"$\rho$")

px_max = np.max(np.sqrt(eint[initial] * 2.*rho[initial]))
pxplot, = axes[1].plot([],[],'g',lw=2)
axes[1].set_ylim(-px_max, px_max)
axes[1].set_xlim(0, np.max(x))
axes[1].set_ylabel(r"$p_x$")

eintplot, = axes[2].plot([],[],'b', lw=2)
axes[2].set_ylim(0, np.max(eint[initial])*1.1)
axes[2].set_xlim(0, np.max(x))
axes[2].set_ylabel(r"$e_\mathrm{int}$")
axes[2].set_xlabel(r"$x$")

#============#
# Formatting #
#============#
for ax in axes:
    ax.minorticks_on()
    ax.tick_params(axis='both',which="both", direction="in",top=True,right=True)

for ax in axes[:-1]:
    for label in ax.get_xticklabels():
        label.set_visible(False)


#=========================================#
# function for each step of the animation #
#=========================================#
def animate(i):
    locs = np.where(it==i)
    time = t[locs][0]

    rhoplot.set_data(x[locs], rho[locs])
    pxplot.set_data(x[locs], px[locs])
    eintplot.set_data(x[locs], eint[locs])
    return rhoplot, pxplot, eintplot

ani = animation.FuncAnimation(fig, animate)
#plt.show()
ani.save("animation.mp4", fps=len(np.unique(it))/total_time)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

filename = "output.dat"
it = np.genfromtxt(filename,   usecols=(0))
t = np.genfromtxt(filename,    usecols=(1))
ix = np.genfromtxt(filename,   usecols=(2))
x = np.genfromtxt(filename,    usecols=(3))
rho = np.genfromtxt(filename,  usecols=(4))
px = np.genfromtxt(filename,   usecols=(5))
etot = np.genfromtxt(filename, usecols=(6))

ilist = np.unique(it)
#tlist = np.unique(t)
Nt = len(ilist)-10

E = np.zeros(Nt)
M = np.zeros(Nt)
P = np.zeros(Nt)
tlist = np.zeros(Nt)

dx = x[1]-x[0]

for i in range(Nt):
    locs = np.where(it==i)

    tlist[i] = t[locs][0]
    E[i] = np.sum(etot[locs])
    M[i] = np.sum(rho[locs])
    P[i] = np.sum(px[locs])


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

fig, axes = plt.subplots(3,1,figsize=(6,8))
plt.subplots_adjust(wspace=0, hspace=0)

initial = np.where(it==0)
Pmax = np.sum(np.sqrt(etot[initial] * 2.*rho[initial]))

Merror = np.abs(M-M[0])/M[0]
Perror = np.abs(P-P[0])/Pmax
Eerror = np.abs(E-E[0])/E[0]

axes[0].semilogy(tlist,Merror,"r")
axes[1].semilogy(tlist,Perror,"g")
axes[2].semilogy(tlist,Eerror,"b")

axes[0].set_ylabel(r"$\delta M/M_0$")
axes[1].set_ylabel(r"$\delta P/P_\mathrm{max}$")
axes[2].set_ylabel(r"$\delta E/E_0$")

for ax in axes:
    ax.set_ylim(top=1)
    ax.set_xlim(0,tlist[-1])
    ax.minorticks_on()
    ax.tick_params(axis='both',which="both", direction="in",top=True,right=True)

for ax in axes[:-1]:
    for label in ax.get_xticklabels():
        label.set_visible(False)

axes[2].set_xlabel(r"$t$")
plt.savefig("conservation.pdf",bbox_inches="tight")

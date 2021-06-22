import numpy as np
import matplotlib.pyplot as plt

filename = "output.dat"
it = np.genfromtxt(filename, usecols=(0))
x = np.genfromtxt(filename, usecols=(4))
rho = np.genfromtxt(filename, usecols=(5))

locs = np.where(it==10)
time = np.genfromtxt(filename,usecols=(1))[locs][0]

plt.plot(x[locs],rho[locs],"o-")
plt.grid()
plt.title("time="+str(time))
plt.xlabel("x")
plt.ylabel(r"$\rho$")
plt.savefig("results.pdf",bbox_inches="tight")

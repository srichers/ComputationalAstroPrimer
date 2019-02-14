import matplotlib.pyplot as plt
import numpy as np

dr = .05
t = 20.
kappa = 200.

data = np.genfromtxt("output.dat",skip_header=1).transpose()
r = data[1]
density = data[3]
N = np.sum(4.*np.pi*r*r*dr * density)
print("Calculated normalization: "+str(N))

D = 1. / (3.*kappa)
theory = 1./np.sqrt( (4.*np.pi *D*t)**3) * np.exp(-data[1]**2 / (4*D*t))
Nt = np.sum(4.*np.pi*r*r*dr * theory)
print("Theory normalization: "+str(Nt))

l2norm = (density-theory)**2
chi2 = np.sum( l2norm / theory**2 )
print("chi^2: "+str(chi2/len(r)))


# plot the results
plt.plot(r, theory)
plt.scatter(r, density)
plt.xlim(0,1)
plt.xlabel("Radius")
plt.ylabel("Density")
plt.savefig("result.pdf")

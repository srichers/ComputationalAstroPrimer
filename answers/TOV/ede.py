import numpy as np
import interpolar
import matplotlib.pyplot as plt
from units import *

class EDE:
    def __init__(self, DensidadDeMasaMin, DensidadDeMasaMax, npoints):
        self.log10Presion = np.zeros(npoints)
        self.log10DensidadDeMasa = np.zeros(npoints)
        self.log10DensidadDeEnergia = np.zeros(npoints)

        # crear array de densidad de masa
        log10DensidadDeMasaMin = np.log10(DensidadDeMasaMin)
        log10DensidadDeMasaMax = np.log10(DensidadDeMasaMax)
        dlog10DensidadDeMasa = (log10DensidadDeMasaMax - log10DensidadDeMasaMin) / (npoints-1)
        self.log10DensidadDeMasa = np.array([log10DensidadDeMasaMin + i*dlog10DensidadDeMasa for i in range(npoints)])
        DensidadDeMasa = 10**self.log10DensidadDeMasa # g/ccm

        # definir constantes para ecuacion 13 de Oppenheimer
        mB4 = mB*mB*mB*mB;
        c5 = c*c*c*c*c;
        h3 = h*h*h;
        K = np.pi*mB4*c5 / (4.*h3); # erg/ccm 
        
        # crear array de t, presion, densidad de energia
        phat = (DensidadDeMasa/mB * 3.*h3/(8.*np.pi))**(1./3.) / (mB*c)
        t = 4. * np.log(phat + np.sqrt(1.+phat*phat))
        DensidadTotal = K    * (np.sinh(t) - t) # erg/ccm
        Presion       = K/3. * (np.sinh(t) - 8.*np.sinh(t/2.) + 3.*t) # erg/ccm
        DensidadDeEnergia = DensidadTotal - DensidadDeMasa*c**2 # erg/ccm

        # crear arrays logaritmicos para interpolacion
        self.log10DensidadDeMasa    = np.log10(DensidadDeMasa)
        self.log10Presion           = np.log10(Presion)
        self.log10DensidadDeEnergia = np.log10(DensidadDeEnergia)
        
    def Presion(self,DensidadDeMasaEn):
        return np.exp( interpolar.interpolar(np.log10(DensidadDeMasaEn), self.log10DensidadDeMasa, self.log10Presion))
        
    def DensidadDeMasa(self,PresionEn):
        return np.exp( interpolar.interpolar(np.log10(PresionEn), self.log10Presion, self.log10DensidadDeMasa) )

    def densidadDeEnergia(self,presion):
        return np.exp( interpolar.interpolar(PresionEn, self.log10Presion, self.log10DensidadDeEnergia) )

    def hacerGrafico(self):
        # hacer las curvas
        pres,  = plt.loglog(10**self.log10DensidadDeMasa, 10**self.log10Presion)
        edens, = plt.loglog(10**self.log10DensidadDeMasa, 10**self.log10DensidadDeEnergia)

        # hacer la leyenda
        plt.legend([pres,edens],["Presion","Densidad de Energia"])

        # poner la cuadricula
        plt.grid()

        # poner las etiquas de eje
        plt.xlabel("Densidad de Masa (g cm$^{-3}$)")
        plt.ylabel("Presion y Densidad de Energia (erg cm$^{-3}$)")

        # guardar el grafico
        plt.savefig("ede.pdf")

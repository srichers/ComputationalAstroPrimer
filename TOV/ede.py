import numpy as np
import interpolar
import matplotlib.pyplot as plt
from unidades import *

class EDE:
    def __init__(self, DensidadDeMasaMin, DensidadDeMasaMax, npoints):
        # crear array de densidad de masa
        log10DensidadDeMasaMin = np.log10(DensidadDeMasaMin)
        log10DensidadDeMasaMax = np.log10(DensidadDeMasaMax)
        dlog10DensidadDeMasa = (log10DensidadDeMasaMax - log10DensidadDeMasaMin) / (npoints-1)
        self.log10DensidadDeMasa = np.array([log10DensidadDeMasaMin + i*dlog10DensidadDeMasa for i in range(npoints)])
        DensidadDeMasa = 10**self.log10DensidadDeMasa # g/ccm

        # definir constantes para ecuacion 13 de Oppenheimer
        # COMPLETA ESTO #
        # DensidadTotal =  # erg/ccm
        # Presion       =  # erg/ccm
        # DensidadDeEnergia = # erg/ccm

        # crear arrays logaritmicos para interpolacion
        self.log10DensidadDeMasa    = np.log10(DensidadDeMasa)
        self.log10Presion           = np.log10(Presion)
        self.log10DensidadDeEnergia = np.log10(DensidadDeEnergia)

    def calcPresion(self,DensidadDeMasa): # erg/ccm
        x = np.log10(DensidadDeMasa)
        xgrid = self.log10DensidadDeMasa
        ygrid = self.log10Presion
        return 10**interpolar.interpolar(x, xgrid, ygrid)
        
    def calcDensidadDeMasa(self,Presion): # g/ccm
        x = np.log10(Presion)
        xgrid = self.log10Presion
        ygrid = self.log10DensidadDeMasa
        return 10**interpolar.interpolar(x, xgrid, ygrid)

    def calcDensidadDeEnergia(self, Presion): # erg/ccm
        x = np.log10(Presion)
        xgrid = self.log10Presion
        ygrid = self.log10DensidadDeEnergia
        return 10**interpolar.interpolar(x, xgrid, ygrid)
    
    def calcDensidadTotal(self, Presion): # g/ccm
        return self.calcDensidadDeEnergia(Presion)/c**2 + self.calcDensidadDeMasa(Presion)
    
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
        print("Grafico ede.pdf cargado.")

import numpy as np
import ede
from unidades import *

# Derivadas
def dPresion_dr(r, DensidadTotal, Presion, MasaTotalInterna): # cm, g/ccm, g, erg/ccm, erg/ccm
    result =  -G*MasaTotalInterna/r**2 * (DensidadTotal + Presion/c**2) * (1.0 + 4.*np.pi*Presion*r**3/(MasaTotalInterna*c**2)) / (1. - 2.*G*MasaTotalInterna/(r*c**2))
    return result
    
def dMasaTotalInterna_dr(r, DensidadTotal):
    return 4.*np.pi*r**2 * DensidadTotal

    
# RK2 Integrador
def integrar_RK2(r0, Presion0, MasaTotalInterna0, dr, ede, tolerancia):

    # paso 0 - tambien necesitamos densidad total
    DensidadTotal0 = ede.calcDensidadTotal(Presion0)
    
    # paso 1 - haz medio paso usando numeros iniciales
    r1 = r0 + dr/2.
    dPdr0 =          dPresion_dr(r0, DensidadTotal0, Presion0, MasaTotalInterna0)
    dMdr0 = dMasaTotalInterna_dr(r0, DensidadTotal0)
    Presion1          =          Presion0 + dr/2. * dPdr0
    MasaTotalInterna1 = MasaTotalInterna0 + dr/2. * dMdr0
    DensidadTotal1 = ede.calcDensidadTotal(Presion1)
    
    # paso 2 - haz paso completo usando paso 1
    r2 = r0 + dr
    dPdr1 =          dPresion_dr(r1, DensidadTotal1, Presion1, MasaTotalInterna1)
    dMdr1 = dMasaTotalInterna_dr(r1, DensidadTotal1)
    Presion2          =          Presion0 + dr * dPdr1
    MasaTotalInterna2 = MasaTotalInterna0 + dr * dMdr1
    DensidadTotal2 = ede.calcDensidadTotal(Presion2)

    # calcular error, adjustar paso de longitud
    errorPresion          = abs(dPdr0 - dPdr1) / abs(dPdr0+dPdr1)
    errorMasaTotalInterna = abs(dMdr0 - dMdr1) / abs(dMdr0+dMdr1)
    error = max(errorPresion, errorMasaTotalInterna)
    dr = dr * (tolerancia/error)
    
    # queremos usar el paso 2
    return r2, Presion2, MasaTotalInterna2, dr
        
def calcularRadioYMasa(dr, tolerancia, DensidadDeMasaAlCentro, DensidadDeMasa_parar, ede, imprimir=False):
    # condiciones iniciales (al centro de la estrella)
    r = dr
    DensidadDeMasa = DensidadDeMasaAlCentro
    Presion = ede.calcPresion(DensidadDeMasa) # erg/ccm
    DensidadTotal = ede.calcDensidadTotal(Presion) # g/ccm
    MasaTotalInterna = 4./3. * np.pi * r**3 * DensidadTotal # g
    
    # hacer pasos hasta la densidad de masa esta demasiado pequeno
    i=0
    while DensidadDeMasa > DensidadDeMasa_parar:
        r, Presion, MasaTotalInterna, dr = integrar_RK2(r, Presion, MasaTotalInterna, dr, ede, tolerancia)
        DensidadDeMasa = ede.calcDensidadDeMasa(Presion)
        
        # imprimir el radio (km), la densidad de masa (g/ccm), y la masa total interna (g)
        if imprimir and i%1000==0:
            print(i, r/km, DensidadDeMasa, MasaTotalInterna/Msol)
        i = i+1
    if imprimir:
        print(i, r/km, DensidadDeMasa, MasaTotalInterna/Msol)
        
    return r, MasaTotalInterna

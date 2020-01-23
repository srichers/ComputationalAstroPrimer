import numpy as np
import ede
from units import *

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

    #print("r",r0,r1,r2)
    #print("Densidad",DensidadTotal0, DensidadTotal1, DensidadTotal2)
    #print("Presion",Presion0, Presion1, Presion2)
    #print("Masa",MasaTotalInterna0,MasaTotalInterna1,MasaTotalInterna2)
    
    # calcular error, adjustar paso de longitud
    errorPresion          = abs(dPdr0 - dPdr1) / abs(dPdr0+dPdr1)
    errorMasaTotalInterna = abs(dMdr0 - dMdr1) / abs(dMdr0+dMdr1)
    error = max(errorPresion, errorMasaTotalInterna)
    dr = dr * (tolerancia/error)
    #print("dPdr",dPdr0, dPdr1)
    #print("dMdr",dMdr0, dMdr1)
    #print(errorPresion, errorMasaTotalInterna, dr)
    
    # queremos usar el paso 2
    return r2, Presion2, MasaTotalInterna2, dr
        

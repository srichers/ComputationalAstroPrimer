import numpy as np
from ede import *
from integrar import integrar_RK2

# inicializar la ecuacion de estadio.
# Solo nos importan las densidades entre 1e10 y 1e16 g/ccm,
# pero usamos un alcance mas grande para ver como queda.
# Calcular 200 puntas, entre de la clase EDE interpola.
ede = EDE(1e9, 1e20, 200)

# Hacer un grafico que mostra la ecuacion de estado
#ede.hacerGrafico()

# constantes que determinan la caulidad de la calculacion
dr = 1
tolerancia = 1e-3

# condiciones iniciales (al centro de la estrella)
dr = 1 # cm
r = dr
DensidadDeMasa = 1e15
Presion = ede.calcPresion(DensidadDeMasa) # erg/ccm
DensidadTotal = ede.calcDensidadTotal(Presion) # g/ccm
MasaTotalInterna = 4./3. * np.pi * r**3 * DensidadTotal # g

# Para la integracion cuando la densidad esta menos que 1e10 g/ccm
DensidadDeMasa_parar = 1e10

# hacer pasos hasta la densidad de masa esta demasiado pequeno
i=0
while DensidadDeMasa > DensidadDeMasa_parar:
    r, Presion, MasaTotalInterna, dr = integrar_RK2(r, Presion, MasaTotalInterna, dr, ede, tolerancia)
    DensidadDeMasa = ede.calcDensidadDeMasa(Presion)

    # imprimir el radio (km), la densidad de masa (g/ccm), y la masa total interna (g)
    if i%1000==0:
        print(r/1e5, DensidadDeMasa, MasaTotalInterna)
    i = i+1


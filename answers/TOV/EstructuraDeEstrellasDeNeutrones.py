# Escrito por Sherwood Richers
# University of California, Berkeley
# Lee el archivo "LICENSE" para reglas de usar y distribuir

import numpy as np
from ede import *
from integrar import integrar_RK2, calcularRadioYMasa
import matplotlib.pyplot as plt

print("###################################################################################")
print("# Haciendo una ecuacion de estado basado en presion de degeneracion de neutrones. #")
print("###################################################################################")

# inicializar la ecuacion de estadio.
# Solo nos importan las densidades entre 1e10 y 1e16 g/ccm,
# pero usamos un alcance mas grande para ver como queda.
# Calcular 200 puntas, entre de la clase EDE interpola.
ede = EDE(1e9, 1e20, 200)

# Hacer un grafico que mostra la ecuacion de estado
ede.hacerGrafico()

print()
print("#########################################################")
print("# Calculando la Estructura de Una Estrella de Neutrones #")
print("#########################################################")
print()
print("Paso   Radio(km)   DensidadDeMasa(g/ccm)   MasaTotalInterna(Msol)")

# constantes que determinan la caulidad de la calculacion
dr = 1 # cm
tolerancia = 1e-3
DensidadDeMasa_parar = 1e10

# Tratar de calcular la masa y radio de solo una estrella de neutrones
DensidadDeMasaAlCentro = 1e15
R, M = calcularRadioYMasa(dr, tolerancia, DensidadDeMasaAlCentro, DensidadDeMasa_parar, ede, True)

print()
print("##################################################")
print("# Calculando las Estructuras de Muchas Estrellas #")
print("##################################################")
print()
print("DensidadDeMasaAlCentro(g/ccm)   Radio(km)   Masa(Msol)")

# Calcula la masa y radio de muchos estrellas de neutrinos y hacer un grafico
DensidadDeMasaAlCentro0 = 1e14 # g/ccm
DensidadDeMasaAlCentro1 = 1e17 # g/ccm
NumeroDeEstrellas = 50
DensidadesALosCentros = np.exp(np.linspace(np.log(DensidadDeMasaAlCentro0), np.log(DensidadDeMasaAlCentro1), NumeroDeEstrellas))
ListaDeR = []
ListaDeM = []
for iEstrella in range(NumeroDeEstrellas):
    DensidadDeMasaAlCentro = DensidadesALosCentros[iEstrella]
    R,M = calcularRadioYMasa(dr, tolerancia, DensidadDeMasaAlCentro, DensidadDeMasa_parar, ede, False)
    ListaDeR.append(R/km)
    ListaDeM.append(M/Msol)
    print(DensidadDeMasaAlCentro, R/km, M/Msol)
plt.grid()
plt.xlabel("Radio (km)")
plt.ylabel("Masa (Msol)")
plt.scatter(ListaDeR, ListaDeM)
plt.savefig("muchas_estrellas.pdf")
print("Grafico muchas_estrellas.pdf cargado.")

import numpy as np
from ede import *

# inicializar la ecuacion de estadio.
# Solo nos importan las densidades entre 1e10 y 1e16 g/ccm,
# pero usamos un alcance mas grande para ver como queda.
# Calcular 200 puntas, entre de la clase EDE interpola.
ede = EDE(1e9, 1e20, 200)

# Hacer un grafico mostrando la ecuacion de estado
ede.hacerGrafico()


print(ede.Presion(1e14))

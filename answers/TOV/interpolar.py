import numpy as np
import bisect
    
def interpolar(xEn, xCuadricula, yCuadricula):
    # get the upper indes
    i = bisect.bisect_right(xCuadricula, xEn, lo=0, hi=len(xCuadricula))

    # check for degenerate case
    yDerecha    = yCuadricula[i  ];
    xDerecha    = xCuadricula[i  ];
    yIzquierda  = yCuadricula[i-1];
    xIzquierda  = xCuadricula[i-1];
    if(yDerecha == yIzquierda):
        return yDerecha;

    # do the interpolation
    inclinacion = (yDerecha-yIzquierda) / (xDerecha-xIzquierda);
    ySalida = yIzquierda + (xEn-xIzquierda)*inclinacion;
    return ySalida;



import numpy as np
import bisect

def h00(t):
    return (1.0+2.0*t)*(1.0-t)*(1.0-t);
def h10(t):
    return t*(1.0-t)*(1.0-t);
def h01(t):
    return t*t*(3.0-2.0*t);
def h11(t):
    return t*t*(t-1.0);

def secant(i, j, xgrid, ygrid):
    return (ygrid[j]-ygrid[i]) / (xgrid[j]-xgrid[i])

def tangent(i, j, xgrid, ygrid):
    N = length(xgrid)

    # two-point stencil on boundary, 3-point stencil elsewhere. Keep out infinities.
    if i==0:
        left_secant = np.inf
    else:
        left_secant = secant(i-1,i,xgrid,ygrid)

    if i==N-1:
        right_secant = np.inf
    else:
        right_secant = secant(i,i+1,xgrid,ygrid)
        
    if i==0:
        return right_secant
    elif i==N-1:
        return left_secant
    else:
        if np.isinf(left_secant):
            result = right_secant
        elif np.isinf(right_secant):
            result = left_secant
        else:
            result = 0.5 * (right_secant + left_secant)
        return result
    
def interpolar(xin, xgrid, ygrid):
    # get the upper indes
    i = bisect.bisect_right(xgrid, xin, lo=0, hi=len(xgrid))

    # check for degenerate case
    yRight = ygrid[i  ];
    xRight = xgrid[i  ];
    yLeft  = ygrid[i-1];
    xLeft  = xgrid[i-1];
    if(yRight == yLeft):
        return yRight;

    # do the interpolation
    slope = (yRight-yLeft) / (xRight-xLeft);
    yout = yLeft + (xin-xLeft)*slope;
    return yout;



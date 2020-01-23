import numpy as np
import bisect
    
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



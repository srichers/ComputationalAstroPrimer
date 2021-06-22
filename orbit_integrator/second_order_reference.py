import numpy as np
import matplotlib.pyplot as plt

G = 6.6725985e-8 # cm^3 g^-1 s^-2
Mearth = 5.976e27 # g

# create a function to find the radius given x and y
def radius(x,y):
    return np.sqrt(x**2 + y**2)

# set the initial position and velocity
# correspoinding to a low-earth orbit
x  = 7e8 # cm (low earth orbit)
y  = 0
vx = 0
vy = np.sqrt(G * Mearth / radius(x,y))
t  = 0

# set our timestep and number of steps
nsteps = 3000
dt = 60.0 # s

def evaluate_derivatives(x,y,vx,vy):
    dx_dt = vx
    dy_dt = vy
    theta = np.arctan2(y,x)
    radial_acceleration = - G*Mearth / radius(x,y)**2
    dvx_dt = radial_acceleration * np.cos(theta)
    dvy_dt = radial_acceleration * np.sin(theta)

    return dx_dt, dy_dt, dvx_dt, dvy_dt

def take_a_step(t, x,y,vx,vy):
    dx_dt, dy_dt, dvx_dt, dvy_dt = evaluate_derivatives(x,y,vx,vy)
    k1_x  = dt * dx_dt 
    k1_y  = dt * dy_dt 
    k1_vx = dt * dvx_dt
    k1_vy = dt * dvy_dt

    dx_dt, dy_dt, dvx_dt, dvy_dt = evaluate_derivatives(x  + 0.5*k1_x,
                                                        y  + 0.5*k1_y,
                                                        vx + 0.5*k1_vx,
                                                        vy + 0.5*k1_vy)
    k2_x  = dt * dx_dt 
    k2_y  = dt * dy_dt 
    k2_vx = dt * dvx_dt
    k2_vy = dt * dvy_dt

    t  = t  + dt
    x  = x  + k2_x
    y  = y  + k2_y
    vx = vx + k2_vx
    vy = vy + k2_vy

    return t, x, y, vx, vy

# create list for plotting
data = [[t,x,y,vx,vy],]

for step in range(nsteps):
    t, x, y, vx, vy = take_a_step(t, x, y, vx, vy)
    
    data.append([t,x,y,vx,vy])
    
data = np.array(data)
plt.scatter(data[:,1],data[:,2], s=2)
plt.gca().set_aspect('equal')
plt.savefig("second_order.pdf")

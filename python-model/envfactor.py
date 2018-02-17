
import numpy as np

class EnvFactor():
    def __init__(self, x, y, lam, sigma=15):
        self.x0 = x
        self.y0 = y
        self.sigma = sigma
        self.lam = lam
        self.g = []
        self.ph1 = 5*np.random.rand()
        self.ph2 = 5*np.random.rand()
    def gaussian(self, x, y):
        theta = np.arctan((x-self.x0)/(y-self.y0))
        func = 0.1 * np.sin(3*theta + self.ph1) + .3*np.cos(1.3*x - self.ph2) + 1
        val =  np.exp(-1 *(((abs(x-self.x0)**2 / self.sigma) + (abs(y-self.y0)**2 / self.sigma))))
        return func*val

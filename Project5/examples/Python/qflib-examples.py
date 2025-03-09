# qflib library examples

#%%
import qflib as qf
import numpy as np
import os

ver = qf.version()
print(f'qflib version: {ver}')
pid = os.getpid()
print(f'pid: {pid}')

# Greet
print('----------------')
name = "World"
print(qf.sayHello(name))

# Outer product
print('----------------')
x = [1, 2, 3]
y = [4, 5]
op = qf.outerProd(x, y)
print(f'x: {x}\ny: {y}')
print(f'outerProd:\n{op}')

# Matrix
print('----------------')
m = np.array([[1, 2, 3], [4, 5, 6]])
em = qf.echoMatrix(m)
print(f'orig matrix:\n{m}')
print(f'echo matrix:\n{em}')

#PPolyEval
print('----------------')
xbpt = np.arange(1, 6)
yval =  np.arange(-10, 15, 5)
pord = 1
xval = np.arange(0.5, 6.0, 0.5)
pval = qf.ppolyEval(xbpt, yval, pord, xval, 0)
pder = qf.ppolyEval(xbpt, yval, pord, xval, 1)
pint = qf.ppolyIntegral(xbpt, yval, pord, xval[0], xval)
print('Piecewise polynomial')
print(f'bkpts={xbpt}')
print(f'yvals={yval}')
print(f'pord={pord}')
print(f'xval={xval}')
print(f'pval={pval}')
print(f'pder={pder}')
print(f'pint={pint}')


#%%
# function group 1
print('================')
print('Analytic prices')

#fwdprice
fwdpx = qf.fwdPrice(spot = 100, timetoexp = 1.0, intrate = 0.02, divyield = 0.04)
print('Forward price analytic solution')
print(f'Price={fwdpx:.4f}')

digi = qf.digiBS(payofftype = 1, spot = 100, timetoexp = 1.0, strike = 100,
                 intrate = 0.02, divyield = 0.04, volatility = 0.2)
print('Digital option using Black-Scholes analytic solution')
print(f'Price={digi:.4f}')

euro = qf.euroBS(payofftype = 1, spot = 100, timetoexp = 1.0, strike = 100,
                intrate = 0.02, divyield = 0.04, volatility = 0.4)
print('European option using Black-Scholes analytic solution')
print(f'Price={euro:.4f}')

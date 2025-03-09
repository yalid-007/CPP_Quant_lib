import qflib.pyqflib

###################
# function group 0

def version(): 
    """qflib library version.

    Returns
    -------
    str
        version in the format Major.Minor.Revision
    """
    return pyqflib.version()


def sayHello(name): 
    """Says hello.

    Parameters
    ----------
    name : str
        caller name

    Returns
    -------
    str
        greeting
    """
    return pyqflib.sayHello(name)


def outerProd(vector1, vector2):
    """Computes the outer product of two numerical vectors.

    Parameters
    ----------
    vector1 : list(double) or 1D numpy array
        first vector
    vector2: list(double) or 1D numpy array
        second vector

    Returns
    -------
    2D numpy array
        outer product as matrix
    """
    return pyqflib.outerProd(vector1, vector2)


def erf(x):
    """Error function at `x`. 
    """
    return pyqflib.erf(x)


def invErf(x):
    """Inverse error function at `x`. 
    """
    return pyqflib.invErf(x)


def normalCdf(x):
    """Cumulative standard normal distribution at `x`. 
    """
    return pyqflib.normalCdf(x)


def normalInvCdf(x):
    """Inverse of the cumulative standard normal distribution at quantile `x`.
    """
    return pyqflib.normalInvCdf(x)


def fwdPrice(spot, timetoexp, intrate, divyield):
    """Forward price of an asset.

    Parameters
    ----------
    spot : double
        asset spot price
    timetoexp : double
        time to expiration in years
    intrate : double
        interest rate, p.a. and c.c.
    divyield : double    
        asset dividend yield, p.a. and c.c.

    Returns
    -------
    double
        asset forward price
     """
    return pyqflib.fwdPrice(spot, timetoexp, intrate, divyield)

def quantoFwdPrice(spot, timeToExp, rForeign, dividendYield,
                   assetVol, fxVol, corrAssetFx, qFix=1.0):
    """Quanto forward price of a foreign asset.

    Parameters
    ----------
    spot : float
        current spot of the foreign asset (USD notion)
    timeToExp : float
        time to expiration in years
    rForeign : float
        foreign risk-free rate, continuous compounding
    dividendYield : float
        dividend yield of the asset
    assetVol : float
        volatility of the underlying asset (foreign)
    fxVol : float
        volatility of the FX rate
    corrAssetFx : float
        correlation between asset returns and FX
    qFix : float, optional
        fixed quanto exchange rate, default = 1.0
    
    Returns
    -------
    float
        quanto forward price, in domestic currency (USD)
    """
    return pyqflib.quantoFwdPrice(
        spot, timeToExp, rForeign, dividendYield,
        assetVol, fxVol, corrAssetFx, qFix
    )
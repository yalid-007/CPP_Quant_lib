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


def polyProd(vector1, vector2):
    """
    Computes the product of two polynomials represented as numerical vectors.

    Parameters
    ----------
    p : list or 1D numpy array
        Coefficients of the first polynomial.
    q : list or 1D numpy array
        Coefficients of the second polynomial.

    Returns
    -------
    numpy array
        Coefficients of the resulting polynomial after multiplication.
    """
    return pyqflib.polyProd(vector1, vector2)

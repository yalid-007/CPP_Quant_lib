/** 
@file  pyfunctions1.hpp
@brief Implementation of Python callable functions
*/

#include <qflib/math/interpol/piecewisepolynomial.hpp>
#include "pycpp.hpp"
#include <qflib/defines.hpp>
#include <qflib/pricers/simplepricers.hpp>
#include <string>

static
PyObject*  pyQfFwdPrice(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pySpot(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OOOO", &pySpot, &pyTimeToExp, &pyIntRate, &pyDivYield))
    return NULL;

  double spot = asDouble(pySpot);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);

  double fwd = qf::fwdPrice(spot, timeToExp, intRate, divYield);

  return asPyScalar(fwd);
PY_END;
}

static
PyObject*  pyQfDigiBS(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyPayoffType(NULL);
  PyObject* pySpot(NULL);
  PyObject* pyStrike(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyVolatility(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
    &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility))
    return NULL;

  int payoffType = asInt(pyPayoffType);
  double spot = asDouble(pySpot);
  double strike = asDouble(pyStrike);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double vol = asDouble(pyVolatility);

  double price = qf::digitalOptionBS(payoffType, spot, strike, timeToExp, intRate, divYield, vol);

  return asPyScalar(price);
PY_END;
}

static
PyObject*  pyQfEuroBS(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;

  PyObject* pyPayoffType(NULL);
  PyObject* pySpot(NULL);
  PyObject* pyStrike(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyIntRate(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyVolatility(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
    &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility))
    return NULL;


  int payoffType = asInt(pyPayoffType);
  double spot = asDouble(pySpot);
  double strike = asDouble(pyStrike);
  double timeToExp = asDouble(pyTimeToExp);
  double intRate = asDouble(pyIntRate);
  double divYield = asDouble(pyDivYield);
  double vol = asDouble(pyVolatility);

  double price = qf::europeanOptionBS(payoffType, spot, strike, timeToExp,
    intRate, divYield, vol);

  return asPyScalar(price);
PY_END;
}

static
PyObject* pyQfPPolySum(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyBkpoints1(NULL);
  PyObject* pyValues1(NULL);
  PyObject* pyBkpoints2(NULL);
  PyObject* pyValues2(NULL);
  PyObject* pyOrder(NULL);
  
  if (!PyArg_ParseTuple(pyArgs, "OOOOO", &pyBkpoints1, &pyValues1, &pyBkpoints2, &pyValues2, &pyOrder))
    return NULL;
    
  // Get arrays from Python objects
PyArrayObject* pyBkp1Arr = reinterpret_cast<PyArrayObject*>(PyArray_FROM_OTF(pyBkpoints1, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY));
PyArrayObject* pyVal1Arr = reinterpret_cast<PyArrayObject*>(PyArray_FROM_OTF(pyValues1, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY));
PyArrayObject* pyBkp2Arr = reinterpret_cast<PyArrayObject*>(PyArray_FROM_OTF(pyBkpoints2, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY));
PyArrayObject* pyVal2Arr = reinterpret_cast<PyArrayObject*>(PyArray_FROM_OTF(pyValues2, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY));
  int order = asInt(pyOrder);
  
  // Check that order is 0 or 1
  if (order > 1) {
    PyErr_SetString(PyExc_ValueError, "Order must be 0 or 1");
    return NULL;
  }
  
  // Get sizes and data pointers
  int n1 = PyArray_DIM(pyBkp1Arr, 0);
  int n2 = PyArray_DIM(pyBkp2Arr, 0);
  
  // Check that breakpoints and values arrays have same sizes
  if (n1 != PyArray_DIM(pyVal1Arr, 0) || n2 != PyArray_DIM(pyVal2Arr, 0)) {
    PyErr_SetString(PyExc_ValueError, "Breakpoints and values arrays must have same size");
    return NULL;
  }
  
  // Get data pointers for the arrays - using reinterpret_cast 
  double* bkp1 = reinterpret_cast<double*>(PyArray_DATA(pyBkp1Arr));
  double* val1 = reinterpret_cast<double*>(PyArray_DATA(pyVal1Arr));
  double* bkp2 = reinterpret_cast<double*>(PyArray_DATA(pyBkp2Arr));
  double* val2 = reinterpret_cast<double*>(PyArray_DATA(pyVal2Arr));
  
  // Create PiecewisePolynomial objects
  qf::PiecewisePolynomial p1(bkp1, bkp1 + n1, val1, order);
  qf::PiecewisePolynomial p2(bkp2, bkp2 + n2, val2, order);
  
  // Add the polynomials
  qf::PiecewisePolynomial psum = p1 + p2;
  
  // Get the breakpoints and values of the sum
  int nsum = psum.size();
  
  // Create result array: an nx2 array where first column is breakpoints and second is values
  npy_intp dims[2] = { nsum, 2 };
  PyArrayObject* pyResult = reinterpret_cast<PyArrayObject*>(PyArray_SimpleNew(2, dims, NPY_DOUBLE));
  
  // Fill the result array
  double* result_data = reinterpret_cast<double*>(PyArray_DATA(pyResult));
  for (int i = 0; i < nsum; ++i) {
    // Breakpoint
    result_data[i*2] = psum.breakPoint(i);
    // Value at breakpoint
    result_data[i*2 + 1] = psum.coefficient(0, i);
  }
  
  // Clean up temporary arrays
  Py_DECREF(pyBkp1Arr);
  Py_DECREF(pyVal1Arr);
  Py_DECREF(pyBkp2Arr);
  Py_DECREF(pyVal2Arr);
  
  return reinterpret_cast<PyObject*>(pyResult);
PY_END;
}
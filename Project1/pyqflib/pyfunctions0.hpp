/** 
@file  pyfunctions0.hpp
@brief Implementation of Python callable functions
*/
#include "pycpp.hpp"
#include <qflib/defines.hpp>
#include <string>

static 
PyObject*  pyQfVersion(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  return asPyScalar(std::string(QF_VERSION_STRING));
PY_END;
}

static 
PyObject* pyQfSayHello(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyArg1(NULL);
  if (!PyArg_ParseTuple(pyArgs, "O", &pyArg1))
    return NULL;
  std::string name = asString(pyArg1);        // read in the name
  std::string greet = "Hello " + name + "!";  // compose the greeting  
  return asPyScalar(greet);
PY_END;
}


static 
PyObject* pyQfOuterProd(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyArg1(NULL);
  PyObject* pyArg2(NULL);
  if (!PyArg_ParseTuple(pyArgs, "OO", &pyArg1, &pyArg2))
    return NULL;

  std::vector<double> vec1 = asDblVec(pyArg1);
  std::vector<double> vec2 = asDblVec(pyArg2);
  size_t nrow = vec1.size();
  size_t ncol = vec2.size();
  
  // allocate and compute the answer
  std::vector<std::vector<double>> outprod(nrow);
  for (size_t i = 0; i < nrow; ++i) {
	  outprod[i].resize(ncol);
	  for (size_t j = 0; j < ncol; ++j) {
		  outprod[i][j] = vec1[i] * vec2[j];
	  };
  };
	
  return asPyArray(outprod);

PY_END;
}


static 
PyObject* pyQfPolyProd(PyObject* pyDummy, PyObject* pyArgs)
{
PY_BEGIN;
  PyObject* pyArg1(NULL);
  PyObject* pyArg2(NULL);

  if (!PyArg_ParseTuple(pyArgs, "OO", &pyArg1, &pyArg2))
    return NULL;

  std::vector<double> p = asDblVec(pyArg1);
  std::vector<double> q = asDblVec(pyArg2);

  if (p.empty() || q.empty()) {
    throw std::invalid_argument("Input vectors cannot be empty");
  }

  size_t m = p.size();
  size_t n = q.size();
  std::vector<double> result(m + n - 1, 0.0);

  // Perform polynomial multiplication
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < n; ++j) {
      result[i + j] += p[i] * q[j];
    }
  }

  // Remove trailing zeros (except when the result is exactly [0])
  while (result.size() > 1 && result.back() == 0.0) {
    result.pop_back();
  }

  return asPyArray(result);

PY_END;
}



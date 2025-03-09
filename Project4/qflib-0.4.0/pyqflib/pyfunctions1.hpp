/** 
@file  pyfunctions1.hpp
@brief Implementation of Python callable functions
*/
#include "pycpp.hpp"
#include <qflib/defines.hpp>
#include <qflib/pricers/simplepricers.hpp>
#include <string>
#include "pyutils.hpp"

/** Forward price function exposed to Python */
static PyObject* pyQfFwdPrice(PyObject* pyDummy, PyObject* pyArgs)
{
    PY_BEGIN;

    PyObject *pySpot(NULL), *pyTimeToExp(NULL), *pyIntRate(NULL), *pyDivYield(NULL);
    
    if (!PyArg_ParseTuple(pyArgs, "OOOO", &pySpot, &pyTimeToExp, &pyIntRate, &pyDivYield)) {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments: Expected (spot, timeToExp, intRate, divYield)");
        return NULL;
    }

    if (!PyNumber_Check(pySpot) || !PyNumber_Check(pyTimeToExp) ||
        !PyNumber_Check(pyIntRate) || !PyNumber_Check(pyDivYield)) {
        PyErr_SetString(PyExc_TypeError, "All arguments must be numeric.");
        return NULL;
    }

    double spot = asDouble(pySpot);
    double timeToExp = asDouble(pyTimeToExp);
    double intRate = asDouble(pyIntRate);
    double divYield = asDouble(pyDivYield);

    double fwd = qf::fwdPrice(spot, timeToExp, intRate, divYield);

    return asPyScalar(fwd);

    PY_END;
}

/** Digital option pricing function exposed to Python */
static PyObject* pyQfDigiBS(PyObject* pyDummy, PyObject* pyArgs)
{
    PY_BEGIN;

    PyObject *pyPayoffType(NULL), *pySpot(NULL), *pyStrike(NULL), *pyTimeToExp(NULL);
    PyObject *pyIntRate(NULL), *pyDivYield(NULL), *pyVolatility(NULL);

    if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
        &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility)) {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments: Expected (payoffType, spot, strike, timeToExp, intRate, divYield, volatility)");
        return NULL;
    }

    if (!PyNumber_Check(pyPayoffType) || !PyNumber_Check(pySpot) ||
        !PyNumber_Check(pyStrike) || !PyNumber_Check(pyTimeToExp) ||
        !PyNumber_Check(pyIntRate) || !PyNumber_Check(pyDivYield) || 
        !PyNumber_Check(pyVolatility)) {
        PyErr_SetString(PyExc_TypeError, "All arguments must be numeric.");
        return NULL;
    }

    int payoffType = asInt(pyPayoffType);
    double spot = asDouble(pySpot);
    double strike = asDouble(pyStrike);
    double timeToExp = asDouble(pyTimeToExp);
    double intRate = asDouble(pyIntRate);
    double divYield = asDouble(pyDivYield);
    double vol = asDouble(pyVolatility);

    qf::Vector greeks = qf::digitalOptionBS(payoffType, spot, strike, timeToExp, intRate, divYield, vol);

    return asNumpy(greeks);

    PY_END;
}

/** European option pricing function exposed to Python */
static PyObject* pyQfEuroBS(PyObject* pyDummy, PyObject* pyArgs)
{
    PY_BEGIN;

    PyObject *pyPayoffType(NULL), *pySpot(NULL), *pyStrike(NULL), *pyTimeToExp(NULL);
    PyObject *pyIntRate(NULL), *pyDivYield(NULL), *pyVolatility(NULL);

    if (!PyArg_ParseTuple(pyArgs, "OOOOOOO", &pyPayoffType, &pySpot, &pyStrike,
        &pyTimeToExp, &pyIntRate, &pyDivYield, &pyVolatility)) {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments: Expected (payoffType, spot, strike, timeToExp, intRate, divYield, volatility)");
        return NULL;
    }

    if (!PyNumber_Check(pyPayoffType) || !PyNumber_Check(pySpot) ||
        !PyNumber_Check(pyStrike) || !PyNumber_Check(pyTimeToExp) ||
        !PyNumber_Check(pyIntRate) || !PyNumber_Check(pyDivYield) ||
        !PyNumber_Check(pyVolatility)) {
        PyErr_SetString(PyExc_TypeError, "All arguments must be numeric.");
        return NULL;
    }

    int payoffType = asInt(pyPayoffType);
    double spot = asDouble(pySpot);
    double strike = asDouble(pyStrike);
    double timeToExp = asDouble(pyTimeToExp);
    double intRate = asDouble(pyIntRate);
    double divYield = asDouble(pyDivYield);
    double vol = asDouble(pyVolatility);

    qf::Vector greeks = qf::europeanOptionBS(payoffType, spot, strike, timeToExp, intRate, divYield, vol);

    return asNumpy(greeks);

    PY_END;
}

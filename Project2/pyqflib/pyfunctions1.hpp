/** 
@file  pyfunctions1.hpp
@brief Implementation of Python callable functions
*/
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
PyObject* pyQfQuantoFwdPrice(PyObject* /*pyDummy*/, PyObject* pyArgs)
{
  PY_BEGIN;

  PyObject* pySpot(NULL);
  PyObject* pyTimeToExp(NULL);
  PyObject* pyRForeign(NULL);
  PyObject* pyDivYield(NULL);
  PyObject* pyAssetVol(NULL);
  PyObject* pyFxVol(NULL);
  PyObject* pyCorrAssetFx(NULL);
  PyObject* pyQfix(NULL);

  // expecting 8 parameters: (spot, timeToExp, rForeign, dividendYield,
  //                         assetVol, fxVol, corrAssetFx, qFix)
  if (!PyArg_ParseTuple(pyArgs, "OOOOOOOO",
        &pySpot, &pyTimeToExp, &pyRForeign, &pyDivYield,
        &pyAssetVol, &pyFxVol, &pyCorrAssetFx, &pyQfix))
  {
    return NULL;  // parse failed
  }

  double spot        = asDouble(pySpot);
  double timeExp     = asDouble(pyTimeToExp);
  double rForeign    = asDouble(pyRForeign);
  double divYield    = asDouble(pyDivYield);
  double assetVol    = asDouble(pyAssetVol);
  double fxVol       = asDouble(pyFxVol);
  double corrAssetFx = asDouble(pyCorrAssetFx);
  double qFix        = asDouble(pyQfix);

  double qFwd = qf::quantoFwdPrice(
      spot, timeExp, rForeign, divYield,
      assetVol, fxVol, corrAssetFx, qFix
  );

  return asPyScalar(qFwd);
  PY_END;
}

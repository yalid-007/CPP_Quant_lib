/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <qflib/pricers/simplepricers.hpp>
#include <qflib/math/stats/normaldistribution.hpp>

#include <cmath>

BEGIN_NAMESPACE(qf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield)
{
  QF_ASSERT(spot >= 0.0, "spot must be non-negative");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");

  return spot * exp((intRate - divYield) * timeToExp);
}

/** Quanto forward price */
double quantoFwdPrice(double spot, double timeToExp, double rForeign, double dividendYield, double assetVol, double fxVol, double corrAssetFx, double qFix)
{
  QF_ASSERT(spot > 0.0,         "spot must be > 0");
  QF_ASSERT(timeToExp > 0.0,    "time to expiration must be > 0");
  QF_ASSERT(rForeign >= 0.0,    "foreign interest rate must be non-negative");
  QF_ASSERT(dividendYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(assetVol >= 0.0,    "asset vol must be non-negative");
  QF_ASSERT(fxVol >= 0.0,       "fx vol must be non-negative");
  QF_ASSERT(corrAssetFx >= -1.0 && corrAssetFx <= 1.0, 
            "asset-fx correlation must be in [-1, 1]");

  // 2. computing the usual forward price in the foreign currency 
  //    (but conceptually "converted" to domestic at qFix = 1.0):
  double baseForward = fwdPrice(spot, timeToExp, rForeign, dividendYield);

  // 3. quanto adjustment factor:
  //    exp( rho * sigma_S * sigma_Q * (T - t) ) * qFix
  double extraExponent = corrAssetFx * assetVol * fxVol * timeToExp;
  double quantoAdj     = std::exp(extraExponent);

  // 4. quanto forward
  return qFix * baseForward * quantoAdj;
}


END_NAMESPACE(qf)

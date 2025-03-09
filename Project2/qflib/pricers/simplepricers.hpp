/**
@file  simplepricers.hpp
@brief Declaration of simple pricing functions
*/

#ifndef QF_SIMPLEPRICERS_HPP
#define QF_SIMPLEPRICERS_HPP

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>


BEGIN_NAMESPACE(qf)

/** The forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield);


double quantoFwdPrice(double spot, double timeToExp, double rForeign, double dividendYield, double assetVol, double fxVol, double corrAssetFx,
                      double qFix = 1.0);

END_NAMESPACE(qf)

#endif // QF_SIMPLEPRICERS_HPP

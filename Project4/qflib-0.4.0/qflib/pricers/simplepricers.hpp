/**
@file  simplepricers.hpp
@brief Declaration of simple pricing functions
*/

#ifndef QF_SIMPLEPRICERS_HPP
#define QF_SIMPLEPRICERS_HPP

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>
#include <qflib/math/matrix.hpp>
#include <vector>

BEGIN_NAMESPACE(qf)

/** Computes the forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield);

/** Price & Greeks of a European digital option in the Black-Scholes model */
qf::Vector digitalOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                           double intRate, double divYield, double volatility);

/** Price & Greeks of a European vanilla option in the Black-Scholes model */
qf::Vector europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                            double intRate, double divYield, double volatility);

END_NAMESPACE(qf)

#endif // QF_SIMPLEPRICERS_HPP
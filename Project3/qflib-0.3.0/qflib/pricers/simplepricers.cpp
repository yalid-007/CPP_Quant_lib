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

/** Price of a European digital option in the Black-Scholes model*/
double digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                       double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d2 = log(fwd / strike) / sigT - 0.5 * sigT;
  NormalDistribution normal;

  double price = exp(-intRate * timeToExp) * normal.cdf(phi * d2);

  return price;
}

/** Price of a European option in the Black-Scholes model*/
double europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                        double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = payoffType;
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * sqrt(timeToExp);
  double d1 = log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = exp(-intRate * timeToExp);
  double price = fwd * normal.cdf(phi * d1) - strike * normal.cdf(phi * d2);
  price *= phi * df;

  return price;
}

/** Price of a Knockout Forward Contract */
double knockoutFwd(double spot, double strike, double KOLevel, double timeToExp, 
  double timeToKO, double intRate, double divYield, double volatility)
{
QF_ASSERT(KOLevel >= 0.0, "KO level must be non-negative");
QF_ASSERT(spot >= 0.0, "spot must be non-negative");
QF_ASSERT(strike >= 0.0, "strike must be non-negative");
QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
QF_ASSERT(timeToKO >= 0.0, "time to knockout must be non-negative");

NormalDistribution normal;

// d1 and d2 at knockout time T1
double sigT1 = volatility * sqrt(timeToKO);
double d1_T1 = (log(spot / KOLevel) + (intRate - divYield + 0.5 * volatility * volatility) * timeToKO) / sigT1;
double d2_T1 = d1_T1 - sigT1;

// Probability of NOT being knocked out at T1
double P_noKO = 1.0 - normal.cdf(-d1_T1);

// Expected S(T1) given no knockout
double E_S_T1 = spot * exp((intRate - divYield) * timeToKO);

// Expected S(T) given no knockout
double E_S_T_given_noKO = E_S_T1 * exp((intRate - divYield) * (timeToExp - timeToKO));

// Discounted expected payoff
double price = exp(-intRate * timeToExp) * P_noKO * (E_S_T_given_noKO - strike);

return price;
}


END_NAMESPACE(qf)

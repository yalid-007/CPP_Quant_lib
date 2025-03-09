/**
@file  simplepricers.cpp
@brief Implementation of simple pricing functions
*/

#include <qflib/pricers/simplepricers.hpp>
#include <qflib/math/stats/normaldistribution.hpp>
#include <cmath>

BEGIN_NAMESPACE(qf)

/** Computes the forward price of an asset */
double fwdPrice(double spot, double timeToExp, double intRate, double divYield)
{
  QF_ASSERT(spot >= 0.0, "spot must be non-negative");
  QF_ASSERT(timeToExp >= 0.0, "time to expiration must be non-negative");
  QF_ASSERT(intRate >= 0.0, "interest rate must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");

  return spot * std::exp((intRate - divYield) * timeToExp);
}

/** Price & Greeks of a European digital option in the Black-Scholes model */
qf::Vector digitalOptionBS(int payoffType, double spot, double strike, double timeToExp,
                           double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(divYield >= 0.0, "dividend yield must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = double(payoffType);
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * std::sqrt(timeToExp);
  double d1 = std::log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = std::exp(-intRate * timeToExp);
  double pdf_d2 = normal.pdf(d2);
  double cdf_d2 = normal.cdf(phi * d2);

  // Price
  double price = df * cdf_d2;

  // Greeks
  double delta = phi * std::exp(-divYield * timeToExp) * pdf_d2 / (volatility * std::sqrt(timeToExp));
  double gamma = delta * (-d2 / spot);
  double theta = intRate * price - (intRate - divYield) * spot * delta - 0.5 * (volatility * volatility) * (spot * spot) * gamma;
  double vega = df * phi * pdf_d2 * (-d2 / volatility - std::sqrt(timeToExp));

  qf::Vector greeks(5);
  greeks << price << delta << gamma << theta << vega;
  return greeks;
}

/** Price & Greeks of a European vanilla option in the Black-Scholes model */
qf::Vector europeanOptionBS(int payoffType, double spot, double strike, double timeToExp, 
                            double intRate, double divYield, double volatility)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "payoffType must be 1 or -1");
  QF_ASSERT(strike >= 0.0, "strike must be non-negative");
  QF_ASSERT(volatility >= 0.0, "volatility must be non-negative");

  double phi = double(payoffType);
  double fwd = fwdPrice(spot, timeToExp, intRate, divYield);
  double sigT = volatility * std::sqrt(timeToExp);
  double d1 = std::log(fwd / strike) / sigT + 0.5 * sigT;
  double d2 = d1 - sigT;

  NormalDistribution normal;
  double df = std::exp(-intRate * timeToExp);
  double pdf_d1 = normal.pdf(d1);
  double cdf_d1 = normal.cdf(phi * d1);
  double cdf_d2 = normal.cdf(phi * d2);

  // Price
  double price = df * phi * (fwd * cdf_d1 - strike * cdf_d2);

  // Greeks
  double delta = phi * std::exp(-divYield * timeToExp) * cdf_d1;
  double gamma = std::exp(-divYield * timeToExp) * pdf_d1 / (spot * volatility * std::sqrt(timeToExp));
  double theta = intRate * price - (intRate - divYield) * spot * delta - 0.5 * (volatility * volatility) * (spot * spot) * gamma;
  double vega = spot * std::exp(-divYield * timeToExp) * std::sqrt(timeToExp) * pdf_d1;

  qf::Vector greeks(5);
  greeks << price << delta << gamma << theta << vega;
  return greeks;
}

END_NAMESPACE(qf)
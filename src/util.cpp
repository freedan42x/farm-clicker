#include "util.hpp"

void sec(int result)
{
  if (result < 0) (void) sec<void>(nullptr);
}

void isec(int result)
{
  if (result < 0) (void) isec<void>(nullptr);
}

std::string format_money(double x, unsigned short prec)
{
  std::string result;

  static const double eps = 0.001;
  const double rx = round(x);
  if (abs(rx - x) <= eps) {
    size_t len = snprintf(nullptr, 0, "%llu", (ull_t) rx);
    result.resize(len);
    snprintf(&result[0], len + 1, "%llu", (ull_t) rx);
  } else {
    size_t len = snprintf(nullptr, 0, "%.*f", prec, x);
    result.resize(len);
    snprintf(&result[0], len + 1, "%.*f", prec, x);
  }
  
  return result;
}

double apply_percent(double x, unsigned short ps)
{
  return x + x * (ps / 100.0);
}

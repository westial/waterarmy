#include "Percentage.h"

long Percentage::calculate(long min, long max, long value) {
  return ((value - min) * 100) / (max - min);
}

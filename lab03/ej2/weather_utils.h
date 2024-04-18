#ifndef WEATHER_UTILS_H
#define WEATHER_UTILS_H

#include "array_helpers.h"

int min_temp_min(WeatherTable array);

void may_temp_max(WeatherTable array, int output[YEARS]);

void may_prec_men(WeatherTable array, month_t meses[YEARS]);

#endif
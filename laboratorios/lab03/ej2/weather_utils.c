#include "weather_utils.h"


int min_temp_min(WeatherTable array){
    int minima = array[0][0][0]._min_temp;

    for(unsigned int year = 0; year < YEARS; year++){
        for(unsigned int month = 0; month < MONTHS; month++){
            for(unsigned int day = 0; day < DAYS; day++){
                if(array[year][month][day]._min_temp < minima){
                    minima = array[year][month][day]._min_temp;
                }
            }
        }
    }
    return minima;

} 

void may_temp_max(WeatherTable array, int output[YEARS]){
    
    for(unsigned int year = 0; year < YEARS; year++){
        int maxima = array[year][0][0]._max_temp;
        for(unsigned int month = 0; month < MONTHS; month++){
            for(unsigned int day = 0; day < DAYS; day++){
                if(array[year][month][day]._max_temp > maxima){
                    maxima = array[year][month][day]._max_temp;
                }

            }
        }
        output[year] = maxima;
    }
}

void may_prec_men(WeatherTable array, month_t meses[YEARS]){
    
    for(unsigned int year = 0u; year < YEARS; year++){
        unsigned int max_prec = 0u;
        for(month_t month = january; month <= december; month++){
            unsigned int cant_prec_men = 0u;
            for(unsigned int day = 0u; day < DAYS; day++){
                cant_prec_men = cant_prec_men + array[year][month][day]._max_temp;
            }
            if(cant_prec_men > max_prec){
                meses[year] = month;
                max_prec = cant_prec_men;

            }
        }
    }
}
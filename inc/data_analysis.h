#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H

#include <cstddef>
#include <string.h>
#include <math.h>
#include <time.h>

double get_abs_err(double measures[], double average, const size_t n);

const size_t n_measures = 10;

bool check_proportion(const double conf_val, const size_t n);

#define TIMER(code, stream)                                                                         \
    {                                                                                               \
    double measures[n_measures] = {};                                                               \
    double average = 0;                                                                             \
    for (size_t i = 0; i < n_measures; i++) {                                                       \
        clock_t time_start_point = clock();                                                         \
        if (code != 0) {                                                                            \
        fprintf(stream, RED "processing line[%d] = (measure failure)\n" WHT, __LINE__); \
        }                                                                                           \
        double seconds = (double)(clock() - time_start_point) / CLOCKS_PER_SEC;                     \
        measures[i] = seconds;                                                                      \
        average = average + seconds;                                                                \
    }                                                                                               \
    average = average / n_measures;                                                                 \
    double abs_err_val = get_abs_err(measures, average, n_measures);                                \
    fprintf(stream, RED "processing line[%d] = (%lg +- %lg)\n" WHT, __LINE__, average, abs_err_val); \
    }                                                                                               \


#endif // DATA_ANALYSIS_H
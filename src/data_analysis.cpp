#include "data_analysis.h"

double get_abs_err(double measures[], double average, const size_t n) {
    if (n == 1) {
        return 0.0;
    }
    double sample_variance = 0;
    for (size_t i = 0; i < n; i++) {
        sample_variance += (measures[i] - average) * (measures[i] - average);
    }
    sample_variance = sample_variance / (double) (n - 1);

    return sqrt(sample_variance / (double) n);
}
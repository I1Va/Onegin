#ifndef STORAGE_FUNCS_H
#define STORAGE_FUNCS_H

#include <cstddef>
#include <string.h>
#include <stdio.h>

struct text_data {
    char *data;
    char **arr_orig;
    char **arr_sorted;
    char **arr_sorted_rev;
    size_t n_lines;
};


text_data *input_data(const char *const path);

size_t file_sz(const char *const path);

#endif // STORAGE_FUNCS_H
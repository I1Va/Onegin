#ifndef STORAGE_FUNCS_H
#define STORAGE_FUNCS_H

#include "error_processing.h"
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

void copy_ptr_arr(char **dest, char **source, size_t n);

void text_data_destructor(text_data *text);

size_t input_text_data(const char *const path, text_data **text, err_code *return_err);

char **place_pointers(char *const data_start, const size_t n_lines, const size_t file_byte_sz, err_code *return_err);

size_t input_data(const char *path, char **data_start, const size_t file_sz, err_code *return_err);

size_t get_file_sz(const char *const path, err_code *return_err);

#endif // STORAGE_FUNCS_H
#ifndef STORAGE_FUNCS_H
#define STORAGE_FUNCS_H

#include "error_processing.h"
#include <cstddef>
#include <string.h>
#include <stdio.h>

struct line_data {
    size_t len;
    char *ptr;
};

struct text_data {
    char *data;
    line_data *arr_orig;
    line_data *arr_sorted;
    line_data *arr_sorted_rev;
    size_t n_lines;
};

void copy_ptr_arr(line_data *dest, line_data *source, size_t n);

void text_data_destructor(text_data *text);

size_t input_text_data(const char *const path, text_data **text, err_code *return_err);

line_data *place_pointers(char *const data_start, const size_t n_lines, const size_t file_byte_sz, err_code *return_err);

size_t input_data(const char *path, char **data_start, const size_t file_sz, err_code *return_err);

size_t get_file_sz(const char *const path, err_code *return_err);

#endif // STORAGE_FUNCS_H
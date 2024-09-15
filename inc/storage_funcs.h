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
    size_t n_lines;
    size_t max_line_sz;
};

void copy_ptr_arr(line_data *dest, line_data *source, size_t n);

void text_data_destructor(text_data *text);

size_t input_text_data(const char *const path, text_data **text, err_code *return_err);

line_data *place_pointers(char *const data_start, const size_t n_lines, const size_t file_sz, size_t *max_line_sz, err_code *return_err);

size_t input_data(const char *path, char **data_start, const size_t file_sz, err_code *return_err);

size_t get_file_sz(const char *const path, err_code *return_err);

line_data *line_data_create(const size_t n_lines, const line_data* src = NULL);

void line_data_destructor(line_data *ptr);

#endif // STORAGE_FUNCS_H
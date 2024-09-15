#ifndef OUTPUT_FUNCS_H
#define OUTPUT_FUNCS_H

#include <string.h>
#include "error_processing.h"
#include "storage_funcs.h"

void fprint_ascii_chars(FILE *stream, char *string, const size_t n);

void print_text_arr(line_data *arr, const size_t n, bool only_syms = false, bool del_borders = false);

void printf_un_end(char *ptr, const char end);

#endif // OUTPUT_FUNCS_H
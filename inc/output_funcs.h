#ifndef OUTPUT_FUNCS_H
#define OUTPUT_FUNCS_H

#include <string.h>
#include "error_processing.h"
#include "storage_funcs.h"

void fprint_ascii_chars(FILE *stream, const char *const string, const size_t n);

void fprint_text_arr(FILE* stream, const line_data *const arr, const size_t n, bool only_syms, bool del_borders);

void fprint_border(FILE* stream);

void printf_un_end(const char *ptr, const char end);

void onegin_text_printf(const char* output_file_path, const text_data *data, err_code *ReturnErr);

#endif // OUTPUT_FUNCS_H
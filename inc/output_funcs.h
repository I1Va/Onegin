#ifndef OUTPUT_FUNCS_H
#define OUTPUT_FUNCS_H

#include <string.h>
#include "error_processing.h"

err_code print_ascii_chars(char *string, const size_t n);

int print_text_arr(char ** arr, const size_t n);

void printf_un_end(char *ptr, const char end);

#endif // OUTPUT_FUNCS_H
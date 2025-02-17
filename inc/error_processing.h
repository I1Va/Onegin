#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H

#include <stdio.h>

#include "general.h"

enum err_code {
    ERR_OK = 0,
    ERR_NULLPTR = 1, // TODO: подравняй нумерацию
    ERR_CALLOC = 2,
    ERR_MEM = 3,
    ERR_UNKNOWN = 4,
    ERR_STAT = 5,
    ERR_INPUT_DATA = 6,
    ERR_FILE_OPEN = 7,
    ERR_FILE_CLOSE = 8,
    ERR_ARGS = 9,
};

const char *get_descr(enum err_code err = ERR_UNKNOWN);

int fprintf_abort(const char file_name[], const int line, const char function_name[], const char error_descr[]);

err_code fprintf_return(const char file_name[], const int line, const char function_name[], const err_code code);

// #ifndef _REALIZE
//     #define asserted(code) ? 1 : printf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code));
// #else
//     #define asserted(code) ;
// #endif // _REALIZE


// #define error_pull_up(condition, code) if (!condition) {fprintf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code)); return code;}

#endif // ERROR_PROCESSING_H

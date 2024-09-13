#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H

#include <stdio.h>

#include "general.h"

enum err_code {
    ERR_OK = 0,
    ERR_NULLPTR = 1,
    ERR_CALLOC = 2,
    ERR_MEM = 3,
    ERR_UNKNOWN = 4,
    ERR_STAT_ERROR = 5,
    ERR_INPUT_DATA = 6,
};


const char *get_descr(enum err_code err = ERR_UNKNOWN);

int fprintf_abort(const char file_name[], const int line, const char function_name[], const char error_descr[]);


#ifndef _REALIZE
    #define asserted(code) ? 1 : fprintf_abort(__FILE_NAME__, __LINE__, __PRETTY_FUNCTION__, get_descr(code));
#else
    #define asserted(code) ;
#endif // _REALIZE

#define error_pull_up(code) || fprintf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code)); return code;

#endif // ERROR_PROCESSING_H
#include <stdlib.h>

#include "error_processing.h"

#define DESCR_(code) case code : return #code;

const char *get_descr(enum err_code err) {
    switch (err) {
        DESCR_(ERR_OK)
        DESCR_(ERR_UNKNOWN)
        DESCR_(ERR_CALLOC)
        DESCR_(ERR_NULLPTR)
        DESCR_(ERR_STAT_ERROR)
        DESCR_(ERR_INPUT_DATA)
        default: return "???";
    }
}

int fprintf_abort(const char file_name[], const int line, const char function_name[], const char error_descr[]) {
    fprintf_red(stderr, "{%s}[%s: %d]; err_info: %s\n", file_name,function_name, line, error_descr);
    abort();
    return 1;
}

#undef DESCR_
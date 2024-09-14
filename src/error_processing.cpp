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
        DESCR_(ERR_MEM)
        default: return "???";
    }
}

#undef DESCR_
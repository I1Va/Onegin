
#include "error_processing.h"

#define DESCR_ case code : return #code

const char *get_descr(enum err_code err) {
    switch (err) {
        case ERR_CALLOC: return "calloc error";
        case ERR_UNKNOWN: return "unknown error";
        default: return "???";
    }
}

#undef DESCR_
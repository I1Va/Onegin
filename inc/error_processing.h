#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H


enum err_code {
    ERR_OK = 52,
    ERR_NULLPTR = 3,
    ERR_CALLOC = 1,
    ERR_MEM = 2,
    ERR_UNKNOWN = -1,
    ERR_STAT_ERROR = 4,
};


const char *get_descr(enum err_code err = ERR_UNKNOWN);


#ifndef _REALIZE
    #define asserted(code) || fprintf_red(stderr, "[%s: %d]; err_info: %s\n", __PRETTY_FUNCTION__, __LINE__, get_descr(code)); abort();
#else
    #define asserted(code) ;
#endif // _REALIZE


#endif // ERROR_PROCESSING_H
#ifndef ERROR_PROCESSING_H
#define ERROR_PROCESSING_H


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


#ifndef _REALIZE
    #define asserted(code) || fprintf_red(stderr, "[%s: %d]; err_info: %s\n", __PRETTY_FUNCTION__, __LINE__, get_descr(code)); abort();
#else
    #define asserted(code) ;
#endif // _REALIZE

#define error_pull_up(code) || fprintf_red(stderr, "{%s}; [%s: %d]; err_info: %s\n", __FILE_NAME__, __PRETTY_FUNCTION__, __LINE__, get_descr(code)); return code;

#endif // ERROR_PROCESSING_H
#ifndef ARRAY_H
#define ARRAY_H

#define GRN "\e[0;32m"
#define WHT "\e[0;37m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"

#define printf_red(str_, ...) printf(RED str_ WHT, ##__VA_ARGS__)
#define printf_wht(str_, ...) printf(WHT str_ WHT, ##__VA_ARGS__)
#define printf_grn(str_, ...) printf(GRN str_ WHT, ##__VA_ARGS__)
#define printf_yel(str_, ...) printf(YEL str_ WHT, ##__VA_ARGS__)

#define fprintf_red(stream, str_, ...) fprintf(stream, RED str_ WHT, ##__VA_ARGS__)
#define fprintf_wht(stream, str_, ...) fprintf(stream, WHT str_ WHT, ##__VA_ARGS__)
#define fprintf_grn(stream, str_, ...) fprintf(stream, GRN str_ WHT, ##__VA_ARGS__)
#define fprintf_yel(stream, str_, ...) fprintf(stream, YEL str_ WHT, ##__VA_ARGS__)


#define FREE(ptr)          \
    do {                    \
        free(ptr); ptr = NULL; \
    } while(0)


/*
#define FREE(ptr)                \
    ({                           \
        typeof(ptr) ptr__ = ptr; \
        free(ptr);               \
        ptr = NULL;              \
        ptr__                    \
    })
*/

enum RETURN_STATES {
    RETURN_ERROR = -1,
    RETURN_FALSE =  0,
    RETURN_TRUE  =  1,
};

#ifdef _DEBUG
#define debug(str_, ...) fprintf_red(stderr, "[%s: %d] " str_, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define debug(str_, ...)
#endif // _DEBUG

#endif // ARRAY_H
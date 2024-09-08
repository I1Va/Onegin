#ifndef ARRAY_H
#define ARRAY_H

#define FREE(ptr)           \
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
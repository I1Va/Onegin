#include <cstddef>
#include <stdio.h>

#include "general.h"
#include "storage_funcs.h"
#include "output_funcs.h"

int print_ascii_chars(char *string, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        const char cur = *(string + i);
        if (cur == '\n') {
            putchar(92);
            putchar('n');
        } else if (cur == '\r') {
            putchar(92);
            putchar('r');
        } else if (cur == '\0') {
            putchar(92);
            putchar('0');
        } else {
            putchar(cur);
        }
    }
    printf("\n");
    return RETURN_TRUE;
}

int print_text_arr(char ** arr, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (*arr[i]) {
            printf("%s\n", arr[i]);
        }
    }
    return RETURN_TRUE;
}
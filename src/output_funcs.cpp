#include <cassert>
#include <cstddef>
#include <stdio.h>
#include <system_error>

#include "general.h"
#include "storage_funcs.h"
#include "output_funcs.h"
#include "error_processing.h"

err_code print_ascii_chars(char *string, const size_t n) {
    assert(string != NULL);

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
    return ERR_OK;
}

int print_text_arr(char ** arr, const size_t n) {
    assert(arr != NULL);

    for (size_t i = 0; i < n; i++) {
        // debug("idx: %ld: ", i);
        printf("%s\n", arr[i]);
    }
    return RETURN_TRUE;
}

void printf_un_end(char *ptr, const char end) {
    printf("line: \"");
    while (*ptr != end) {
        putchar(*ptr++);
    }
    printf("\"\n");
}


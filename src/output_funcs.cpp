#include <cassert>
#include <cstddef>
#include <stdio.h>
#include <system_error>

#include "general.h"
#include "storage_funcs.h"
#include "output_funcs.h"
#include "error_processing.h"

void fprint_ascii_chars(FILE *stream, char *string, const size_t n) {
    assert(string != NULL);

    for (size_t i = 0; i < n; i++) {
        const char cur = *(string + i);
        if (cur == '\n') {
            fprintf(stream, "%cn", 92);
        } else if (cur == '\r') {
            fprintf(stream, "%cr", 92);
        } else if (cur == '\0') {
            fprintf(stream, "%c0", 92);
        } else {
            fprintf(stream, "%cr", 92);
        }
    }
    fprintf(stream, "\n");
}

int print_text_arr(line_data *arr, const size_t n) {
    assert(arr != NULL);

    for (size_t i = 0; i < n; i++) {
        // debug("idx: %ld: ", i);
        printf("%s\n", arr[i].ptr);
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


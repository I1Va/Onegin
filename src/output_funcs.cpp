#include <cassert>
#include <cctype>
#include <cstddef>
#include <stdio.h>
#include <system_error>

#include "general.h"
#include "storage_funcs.h"
#include "output_funcs.h"
#include "processing_funcs.h"
#include "error_processing.h"

const size_t LINE_MAX_SIZE = 10;

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

void fprint_text_arr(FILE* stream, line_data *arr, const size_t n, bool only_syms, bool del_borders) {
    assert(arr != NULL);

    for (size_t i = 0; i < n; i++) {
        if (only_syms) {
            if (!letters_in_string(arr[i].ptr, '\0')) {
                continue;
            }
        }
        if (del_borders) {
            size_t start_j = 0;
            while (!isalpha(arr[i].ptr[start_j])) {
                start_j++;
            }
            size_t end_j = arr[i].len - 1;
            while (!isalpha(arr[i].ptr[end_j])) {
                end_j--;
            }
            for (size_t j = start_j; j <= end_j; j++) {
                fprintf(stream, "%c", arr[i].ptr[j]);
            }
            fprintf(stream, "\n");
        } else {
            fprintf(stream, "%s\n", arr[i].ptr);
        }
    }
}

void printf_un_end(char *ptr, const char end) {
    printf("line: \"");
    while (*ptr != end) {
        putchar(*ptr++);
    }
    printf("\"\n");
}

void fprint_border(FILE* stream) {
    fprintf(stream, RED "##############################################################################" WHT "\n");
}

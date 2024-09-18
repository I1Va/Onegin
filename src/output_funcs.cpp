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

void fprint_ascii_chars(FILE *stream, const char *const string, const size_t n) {
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
            fprintf(stream, "%c", *(string + i));
        }
    }
    fprintf(stream, "\n");
}

void fprint_text_arr(FILE* stream, const line_data *const arr, const size_t n, bool only_syms, bool del_borders) {
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

void printf_un_end(const char *ptr, const char end) {
    printf("line: \"");
    while (*ptr != end) {
        putchar(*ptr++);
    }
    printf("\"\n");
}

void fprint_border(FILE* stream) {
    fprintf(stream, RED "##############################################################################" WHT "\n");
}

void onegin_text_printf(const char* output_file_path, const text_data *data, err_code *ReturnErr) {
    FILE *output_file_ptr = NULL;
    if (output_file_path == NULL) {
        output_file_ptr = stdout;
    } else {
        output_file_ptr = fopen(output_file_path, "wb");
        if (output_file_ptr == NULL) {
            *ReturnErr = ERR_FILE_OPEN;
            printf("didn't find output file [%s]\n", output_file_path);
            DEBUG_ERROR(ERR_FILE_OPEN);
            return;
        }
    }
    printf("path: %s\n", output_file_path);

    fprint_text_arr(output_file_ptr, data->arr_sorted, data->n_lines, true, true);
    fprint_border(output_file_ptr);

    fprint_text_arr(output_file_ptr, data->arr_sorted_rev, data->n_lines, true, true);
    fprint_border(output_file_ptr);

    fprint_text_arr(output_file_ptr, data->arr_orig, data->n_lines, false, false);
}

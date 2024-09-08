#include <stdio.h>

#include "storage_funcs.h"
#include "output_funcs.h"

void fprint_data(FILE* stream, char data[][MAX_LINE_SZ]) {
    for (size_t i = 0; i < MAX_LINES_CNT; i++) {
        for (size_t j = 0; j < MAX_LINE_SZ; j++) {
            fprintf(stream, "%c", data[i][j]);
        }
        // fprintf(stream, "\n");
    }
}

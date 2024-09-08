#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "processing_funcs.h"
#include "storage_funcs.h"
#include "output_funcs.h"

int main() {
    // TODO: протестить сампоисные строковые функции


    char data[MAX_LINES_CNT][MAX_LINE_SZ] = {}; // TODO: динамическая память
    FILE *file = fopen("./onegin.txt", "r");
    if (file == NULL) {
        strerror(errno);
        return EXIT_FAILURE;
    }
    input_data(file, data);
    for (size_t i = 0; i < MAX_LINE_SZ; i++) {
        remove_extra_spaces(data[i]);
    }
    bubble_sort(data);
    for (size_t i = 0; i < MAX_LINES_CNT; i++) {
        printf("data[%ld]: %s", i, data[i]);
    }
    fprint_data(stdout, data);

    fclose(file);
    return EXIT_SUCCESS;
}

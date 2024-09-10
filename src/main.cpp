#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "processing_funcs.h"
#include "storage_funcs.h"
#include "general.h"
#include "output_funcs.h"

int main() {
    text_data* data = input_data("./test.txt");
    if (data == NULL) {
        debug("input data error\n");
        return EXIT_FAILURE;
    }

    data->arr_sorted = bubble_sort(data, true);

    print_text_arr(data->arr_sorted, data->n_lines);

    return EXIT_SUCCESS;
}

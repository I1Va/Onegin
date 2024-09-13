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
#include "error_processing.h"


int main() {
    text_data* data = input_text_data("./test.txt"); // TODO: передачу названия файла через командную строку
    if (data == NULL) {
        debug("input data error\n");
        return EXIT_FAILURE;
    }

    data->arr_sorted = bubble_sort(data, false);

    print_text_arr(data->arr_sorted, data->n_lines);
    // TODO: создать деструктор для text_data
    return EXIT_SUCCESS;
}

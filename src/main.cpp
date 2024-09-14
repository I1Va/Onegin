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
    err_code last_err = ERR_OK;
    text_data* data = NULL;
    input_text_data("./test.txt", &data, &last_err);

    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err);
        return EXIT_FAILURE;
    } // TODO: передачу названия файла через командную строку

    // data->arr_sorted = bubble_sort(data, false);
    print_text_arr(data->arr_orig, data->n_lines);
    text_data_destructor(data);
    return EXIT_SUCCESS;
}

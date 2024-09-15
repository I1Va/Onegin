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
    DEBUG_ERROR(last_err)
    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err)
        return EXIT_FAILURE;
    } // TODO: передачу названия файла через командную строку

    line_data *sorted_arr = line_data_create(data->n_lines, data->arr_orig);
    line_data *sorted_arr_rev = line_data_create(data->n_lines, data->arr_orig);

    bubble_sort(sorted_arr, data->n_lines, str_cmp);
    bubble_sort(sorted_arr_rev, data->n_lines, str_cmp_rev);

    print_text_arr(data->arr_orig, data->n_lines, false, false);
    print_border()
    print_text_arr(sorted_arr, data->n_lines, true, true);
    print_border()
    print_text_arr(sorted_arr_rev, data->n_lines, true, true);

    text_data_destructor(data);
    return EXIT_SUCCESS;
}

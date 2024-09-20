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
#include "data_analysis.h"
#include "output_funcs.h"
#include "error_processing.h"
#include "args_processing.h"

#include <time.h>


int main(const int argc, const char *argv[]) {
    srand((unsigned int) clock());

    err_code LastErr = ERR_OK;
    text_data* data = NULL;
    path_data *pathes = mode_launcher(argc, argv, &LastErr);

    if (pathes == NULL) {
        DEBUG_ERROR(LastErr);
        return EXIT_FAILURE;
    }

    input_text_data(pathes->input_path, &data, &LastErr);
    if (LastErr != ERR_OK) {
        DEBUG_ERROR(LastErr)
        goto END_POINT_0;
    }

    data->arr_sorted = line_data_create(data->n_lines, data->arr_orig);
    if (data->arr_sorted == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        goto END_POINT_1;
    }

    data->arr_sorted_rev = line_data_create(data->n_lines, data->arr_orig);
    if (data->arr_sorted_rev == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        goto END_POINT_2;
    }

    // TODO: как не выводить stderr?
    //TIMER(quick_sort(data->arr_sorted, data->n_lines, sizeof(line_data), (cmp) str_cmp, pivot_simp), stderr);
    TIMER(quick_sort(data->arr_sorted, data->n_lines, sizeof(line_data), (cmp) str_cmp, pivot_random), stderr);
    // TIMER(quick_sort(data->arr_sorted, data->n_lines, sizeof(line_data), (cmp) str_cmp), stderr); // FIXME: исправить random pivot
    TIMER(qsort(data->arr_sorted_rev, data->n_lines, sizeof(line_data), (cmp) str_cmp_rev), stderr);

    onegin_text_printf(pathes->output_path, data, &LastErr);
    if (LastErr != ERR_OK) {
        DEBUG_ERROR(LastErr);
        goto END_POINT_3;
    }

    text_data_destructor(data);
    path_data_destructor(pathes);

    return EXIT_SUCCESS;

    END_POINT_3:
    END_POINT_2:
    END_POINT_1:
    text_data_destructor(data);
    END_POINT_0:
    path_data_destructor(pathes);

    return EXIT_FAILURE;
}

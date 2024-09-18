#include <cassert>
#include <cctype>
#include <cstddef>
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
#include "args_processing.h"

path_data *path_data_constructor(const char *src_inp_path, const char *src_out_path) {
    assert(src_inp_path != NULL);

    path_data *pathes = (path_data *) calloc(1, sizeof(path_data));
    size_t inp_sz = 0;
    size_t out_sz = 0;
    char *input_file_path = NULL;
    char *output_file_path = NULL;

    if (pathes == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        return NULL;
    }

    inp_sz = strlen(src_inp_path);
    out_sz = strlen(src_out_path);


    input_file_path = (char *) calloc(inp_sz + 1, sizeof(char));
    if (input_file_path == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        return NULL;
    }

    output_file_path = (char *) calloc(out_sz + 1, sizeof(char));
    if (output_file_path == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        goto END_POINT_0;
    }

    strncpy(output_file_path, src_out_path, out_sz + 1);
    strncpy(input_file_path, src_inp_path, inp_sz + 1);

    pathes->input_path = input_file_path;
    pathes->output_path = output_file_path;

    return pathes;

    END_POINT_0:
    FREE(input_file_path)
    return NULL;
}

void path_data_destructor(path_data *pathes) {
    FREE(pathes->input_path)
    FREE(pathes->output_path)
    FREE(pathes)
}

void main_mode_launch(const char input_file_path[], const char output_file_path[], err_code *const ReturnErr) {
    err_code LastErr = ERR_OK;

    text_data* data = NULL;
    line_data *sorted_arr = NULL;
    line_data *sorted_arr_rev = NULL;
    FILE *output_file_ptr = NULL;


    input_text_data(input_file_path, &data, &LastErr);
    if (LastErr != ERR_OK) {
        *ReturnErr = LastErr;
        printf("didn't find input file [%s]\n", input_file_path);
        DEBUG_ERROR(LastErr)
        return;
    }

    sorted_arr = line_data_create(data->n_lines, data->arr_orig);
    if (sorted_arr == NULL) {
        *ReturnErr = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC);
        goto END_POINT_1;
    }

    sorted_arr_rev = line_data_create(data->n_lines, data->arr_orig);
    if (sorted_arr_rev == NULL) {
        *ReturnErr = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC);
        goto END_POINT_2;
    }

    quick_sort(sorted_arr, data->n_lines, sizeof(line_data), (cmp) str_cmp);
    qsort(sorted_arr_rev, data->n_lines, sizeof(line_data), (cmp) str_cmp_rev);

    if (output_file_path == NULL) {
        output_file_ptr = stdout;
    } else {
        output_file_ptr = fopen(output_file_path, "wb");
        if (output_file_ptr == NULL) {
            printf("didn't find output file [%s]\n", output_file_path);
            DEBUG_ERROR(ERR_FILE_OPEN);
            goto END_POINT_3;
        }
    }


    fprint_text_arr(output_file_ptr, sorted_arr, data->n_lines, true, true);
    fprint_border(output_file_ptr);

    fprint_text_arr(output_file_ptr, sorted_arr_rev, data->n_lines, true, true);
    fprint_border(output_file_ptr);

    fprint_text_arr(output_file_ptr, data->arr_orig, data->n_lines, false, false);

    text_data_destructor(data);
    line_data_destructor(sorted_arr);
    line_data_destructor(sorted_arr_rev);

    return;


    // ZONE OF PTR FREE
    END_POINT_3:
    line_data_destructor(sorted_arr_rev);
    END_POINT_2:
    line_data_destructor(sorted_arr);
    END_POINT_1:
    text_data_destructor(data);
    return;
}

path_data *mode_launcher(const int argc, const char *argv[], err_code *const ReturnErr) {
    if (argc < 2) {
        *ReturnErr = ERR_ARGS;
        printf("input file was't entered\n");
        DEBUG_ERROR(ERR_ARGS);
        return NULL;
    }

    if (argc < 3) {
        path_data *pathes = path_data_constructor(argv[1], NULL);
        return pathes;
    }
    path_data *pathes = path_data_constructor(argv[1], argv[2]);
    return pathes;
}

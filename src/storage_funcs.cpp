#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

#include "storage_funcs.h"
#include "error_processing.h"
#include "general.h"
#include "processing_funcs.h"
#include "storage_funcs.h"

line_data *line_data_create(const size_t n_lines, const line_data* src) {
    line_data *data = (line_data *) calloc(n_lines, sizeof(line_data));
    if (data == NULL) {
        DEBUG_ERROR(ERR_CALLOC);
        return NULL;
    }

    if (src != NULL) {
        for (size_t i = 0; i < n_lines; i++) {
            data[i] = src[i];
        }
    }
    return data; // WARNING: скопирует только первые n_lines из src
}

void line_data_destructor(line_data *ptr) {
    FREE(ptr);
}

void text_data_destructor(text_data *text) {
    FREE(text->data);
    FREE(text->arr_orig);
    FREE(text);
}

size_t get_file_sz(const char *const path, err_code *return_err) {
    struct stat buf = {};
    if (stat(path, &buf) != 0) {
        *return_err = ERR_STAT;
        DEBUG_ERROR(ERR_STAT)
        return 0;
    }

    return (size_t) buf.st_size;
}

line_data *place_pointers(char *const data_start, const size_t n_lines, const size_t file_sz, size_t *max_line_sz, err_code *return_err) {
    assert(data_start != NULL);

    *max_line_sz = 0;

    line_data *arr_orig = (line_data *) calloc(n_lines, sizeof(line_data));
    if (arr_orig == NULL) {
        *return_err = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC)
        return NULL;
    }

    size_t line_idx = 0;
    char *data_curptr = data_start;
    while ((size_t) (data_curptr - data_start) < file_sz) {
        (arr_orig + line_idx)->ptr = data_curptr;

        char *next_ptr = strchr(data_curptr, '\n');
        (arr_orig + line_idx)->len = (size_t) (next_ptr - data_curptr);
        *max_line_sz = MAX(*max_line_sz, (arr_orig + line_idx)->len);
        data_curptr = next_ptr;

        *data_curptr++ = '\0';
        line_idx++;
    }

    return arr_orig;
}

size_t input_data(const char *path, char **data_start, const size_t file_sz, err_code *return_err) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        DEBUG_ERROR(ERR_FILE_OPEN)
        *return_err = ERR_FILE_OPEN;
        return 0;
    }

    size_t fread_cnt = fread(*data_start, sizeof(char), file_sz - 1, file);
    assert(fread_cnt == (file_sz - 1));

    *(*data_start + file_sz - 1) = '\n';

    if (fclose(file) != 0) {
        DEBUG_ERROR(ERR_FILE_CLOSE);
        *return_err = ERR_FILE_CLOSE;
        return 0;
    }
    return file_sz;
}

void copy_ptr_arr(line_data *dest, line_data *source, size_t n) {
    while(n--) {
        *dest++ = *source++;
    }
}

size_t input_text_data(const char *const path, text_data **text, err_code *return_err) {
    err_code last_err = ERR_OK;

    text_data *text_data_ptr = NULL;
    char *data_start = NULL;
    line_data *arr_orig = NULL;
    size_t file_sz = 0;
    size_t n_lines = 0;
    size_t max_line_sz = 0;

    if (path == NULL) {
        *return_err = ERR_NULLPTR;
        DEBUG_ERROR(ERR_NULLPTR);
        goto END_POINT_0;
    }

    fprintf_yel(stderr, "cur_path: %s\n\n", path);

    text_data_ptr = (text_data *) calloc(1, sizeof(text_data));
    if (text_data_ptr == NULL) {
        *return_err = ERR_NULLPTR;
        DEBUG_ERROR(ERR_NULLPTR)
        goto END_POINT_1;
    }

    file_sz = get_file_sz(path, &last_err) + 1;

    data_start = (char *) calloc(file_sz, sizeof(char));
    if (data_start == NULL) {
        *return_err = ERR_NULLPTR;
        DEBUG_ERROR(ERR_NULLPTR)
        goto END_POINT_2;

    }

    input_data(path, &data_start, file_sz, &last_err);
    if (last_err != ERR_OK) {
        *return_err = last_err;
        DEBUG_ERROR(ERR_OK)
        goto END_POINT_3;
    }

    n_lines = str_cnt_chr(data_start, '\n', file_sz);

    arr_orig = place_pointers(data_start, n_lines, file_sz, &max_line_sz, &last_err);
    if (last_err != ERR_OK) {
        *return_err = last_err;
        DEBUG_ERROR(last_err)
        goto END_POINT_4;
    }


    text_data_ptr->data = data_start;
    text_data_ptr->arr_orig = arr_orig;
    text_data_ptr->n_lines = n_lines;
    text_data_ptr->max_line_sz = max_line_sz;
    *text = text_data_ptr;

    return file_sz;

    // ZONE OF PTR FREE
    END_POINT_4:
    END_POINT_3:
    FREE(data_start);
    END_POINT_2:
    FREE(text_data_ptr);
    END_POINT_1:
    END_POINT_0:

    return 0;
}

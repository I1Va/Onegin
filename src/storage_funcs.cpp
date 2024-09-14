#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "storage_funcs.h"
#include "error_processing.h"
#include "general.h"
#include "processing_funcs.h"
#include "storage_funcs.h"
#include "output_funcs.h"

void text_data_destructor(text_data *text) {
    FREE(text->data);
    FREE(text->arr_orig);
    FREE(text->arr_sorted);
    FREE(text->arr_sorted_rev);
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

char **place_pointers(char *const data_start, const size_t n_lines, const size_t file_sz, err_code *return_err) {
    assert(data_start != NULL);

    char **arr_orig = (char **) calloc(n_lines, sizeof(char *));
    if (arr_orig == NULL) {
        *return_err = ERR_CALLOC;
        DEBUG_ERROR(ERR_CALLOC)
        return NULL;
    }

    size_t line_idx = 0;
    char *data_curptr = data_start;
    while ((size_t) (data_curptr - data_start) < file_sz) {
        *(arr_orig + line_idx++) = data_curptr;
        data_curptr = strchr(data_curptr, '\n');
        *data_curptr++ = '\0';
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

void copy_ptr_arr(char **dest, char **source, size_t n) {
    while(n--) {
        *dest++ = *source++;
    }
}

size_t input_text_data(const char *const path, text_data **text, err_code *return_err) {
    err_code last_err = ERR_OK;

    if (path == NULL) {
        DEBUG_ERROR(ERR_NULLPTR);
        *return_err = ERR_NULLPTR;
        return 0;
    }

    debug("cur path: '%s'\n", path);

    text_data *text_data_ptr = (text_data *) calloc(1, sizeof(text_data));
    if (text_data_ptr == NULL) {
        DEBUG_ERROR(ERR_NULLPTR)
        *return_err = ERR_NULLPTR;
        return 0;
    }

    // TODO: можно проинициализировать в начале и использовать goto для освобождения памяти
    size_t file_sz = get_file_sz(path, &last_err) + 1;

    char *data_start = (char *) calloc(file_sz, sizeof(char)); // get_file_sz - кол-во байт
    if (data_start == NULL) {
        DEBUG_ERROR(ERR_NULLPTR)
        *return_err = ERR_NULLPTR;
        return 0;
    }
    input_data(path, &data_start, file_sz, &last_err);
    if (last_err != ERR_OK) {
        DEBUG_ERROR(ERR_OK)
        *return_err = last_err;
        return 0;
    }

    size_t n_lines = str_cnt_chr(data_start, '\n', file_sz);

    char **arr_orig = place_pointers(data_start, n_lines, file_sz, &last_err);
    if (last_err != ERR_OK) {
        DEBUG_ERROR(last_err);
        return 0;
    }
    char **arr_sorted = (char **) calloc(n_lines, sizeof(char *));
    copy_ptr_arr(arr_sorted, arr_orig, n_lines);
    char **arr_sorted_rev = (char **) calloc(n_lines, sizeof(char *));
    copy_ptr_arr(arr_sorted_rev, arr_orig, n_lines);

    text_data_ptr->data = data_start;
    text_data_ptr->arr_orig = arr_orig;
    text_data_ptr->arr_sorted = arr_sorted;
    text_data_ptr->arr_sorted_rev = arr_sorted_rev;
    text_data_ptr->n_lines = n_lines;
    *text = text_data_ptr;

    return ERR_OK;
}

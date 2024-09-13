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
#include "allocation_funcs.h"

size_t file_sz(const char *const path) {
    struct stat buf = {};
    if (stat(path, &buf) != 0) {
        strerror(errno);
        debug("stat error");
        return 0;
    }
    return (size_t) buf.st_size;
}

char **place_pointers(char *const data_start, const size_t n_lines, const size_t file_byte_sz) {
    char **arr_orig = (char **) calloc(n_lines, sizeof(char *));
    if (arr_orig == NULL) {
        debug("error: %s\n", strerror(errno));
        return 0;
    }
    size_t line_idx = 0;
    char *data_curptr = data_start;

    while (data_curptr < (data_start + file_byte_sz)) {
        *(arr_orig + line_idx++) = data_curptr;

        data_curptr = strchr(data_curptr, '\n');
        *data_curptr++ = '\0';
    }

    return arr_orig;
}

size_t input_data(const char *path, char **data_start) {
    size_t file_byte_sz = (size_t) file_sz(path) + 1; // TODO: добавить enum ошибок
    assert(file_byte_sz != 1);

    FILE *file = fopen(path, "rb");
    if (file == NULL) { // TODO: исправить
        debug("error: %s\n", strerror(errno)); // TODO: сделать printf strerror
        FREE(data_start);
        return 0;
    }

    size_t fread_cnt = fread(*data_start, sizeof(char), file_byte_sz - 1, file);
    assert(fread_cnt == (file_byte_sz - 1));

    *(*data_start + file_byte_sz - 1) = '\n';
    // print_ascii_chars(*data_start, file_byte_sz);
    if (fclose(file) != 0) {
        debug("fclose error");
        return 0;
    }
    return file_byte_sz;
}

err_code input_text_data(const char *const path, text_data **text) {
    path == NULL asserted(ERR_NULLPTR);
    debug("cur path: '%s'\n", path);

    text_data *text_data_ptr = (text_data *) calloc(1, sizeof(text_data));
    if (text_data_ptr == NULL) {
        debug("text_data_ptr calloc error");
        return ERR_OK;
    };

    size_t file_byte_sz = file_sz(path) + 1;
    char *data_start = (char *) calloc(file_byte_sz, sizeof(char)); // file_sz - кол-во байт
    if (data_start == NULL) {
        debug("data_start calloc error\n");
        return ERR_OK;
    }


    input_data(path, &data_start);

    size_t n_lines = str_cnt_chr(data_start, '\n');
    char **arr_orig = place_pointers(data_start, n_lines, file_byte_sz);

    text_data_ptr->data = data_start;
    text_data_ptr->arr_orig = arr_orig;
    text_data_ptr->n_lines = n_lines;
    *text = text_data_ptr;
    return ERR_OK;
}

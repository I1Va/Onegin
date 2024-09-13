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
// TODO: сделать enum OneginError* error

// void place_pointers(char *data_ptr) {

// }

text_data *input_data(const char *const path) { // FIXME: как делать FREE? Не могу применить goto, так как есть инициализация переменных
    assert(path != NULL);
    debug("cur path: '%s'\n", path); // TODO: разбить на более мелкие функции

    text_data *text_data_ptr = (text_data *) calloc(1, sizeof(text_data));
    if (text_data_ptr == NULL) {
        debug("text_data_ptr calloc error");
        return NULL;
    };


    size_t file_byte_sz = (size_t) file_sz(path) + 1; // TODO: добавить enum ошибок
    assert(file_byte_sz != 1);

    char *data_start = (char *) calloc(file_byte_sz, sizeof(char)); // file_sz - кол-во байт
    if (data_start == NULL) {
        debug("data_start calloc error\n");
        return NULL;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL) { // TODO: исправить
        debug("error: %s\n", strerror(errno)); // TODO: сделать printf strerror
        FREE(data_start);
        return NULL;
    }

    size_t fread_cnt = fread(data_start, sizeof(char), file_byte_sz - 1, file);
    assert(fread_cnt == (file_byte_sz - 1));

    *(data_start + file_byte_sz - 1) = '\n';

    if (fclose(file) != 0) {
        debug("fclose error");
        return NULL;
    }

    size_t n_lines = str_cnt_chr(data_start, '\n');
    char **arr_orig = (char **) calloc(n_lines, sizeof(char *));
    if (arr_orig == NULL) {
        debug("error: %s\n", strerror(errno));
        FREE(data_start);
        FREE(text_data_ptr);
        return NULL;
    }
    // print_ascii_chars(data_start, file_byte_sz);

    size_t line_idx = 0;
    char *data_cur_ptr = data_start;
    while (data_cur_ptr < (data_start + file_byte_sz)) {
        if (letters_in_string(data_cur_ptr, '\n')) {
            *(arr_orig + line_idx++) = data_cur_ptr;
        }
        data_cur_ptr = strchr(data_cur_ptr, '\n');
        *data_cur_ptr++ = '\0';
    }

    arr_orig = (char **) realloc(arr_orig, line_idx * sizeof (char*));
    n_lines = line_idx;

    for (size_t i = 0; i < n_lines; i++) {
        *(arr_orig + i) = remove_extra_spaces(*(arr_orig + i)); // FIXME: меняется структура текста
        string_to_lower(*(arr_orig + i));
    }

    // print_ascii_chars(data_start, file_byte_sz);

    text_data_ptr->data = data_start;
    text_data_ptr->arr_orig = arr_orig;
    text_data_ptr->n_lines = n_lines;

    return text_data_ptr;
}

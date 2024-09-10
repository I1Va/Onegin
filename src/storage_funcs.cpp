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

text_data *input_data(const char *const path) { // FIXME: как делать FREE? Не могу применить goto, так как есть инициализация переменных
    assert(path != NULL);
    debug("cur path: %s\n", path);

    text_data *text_data_ptr = (text_data *) calloc(1, sizeof(text_data));
    if (text_data_ptr == NULL) {
        debug("text_data_ptr calloc error");
        return NULL;
    };

    struct stat buf = {};
    if (stat(path, &buf) != 0) {
        strerror(errno);
        debug("stat error");
        return NULL;
    }
    size_t file_byte_sz = (size_t) buf.st_size + 1;

    char *data_start = (char *) calloc(file_byte_sz, sizeof(char)); // file_sz - кол-во байт
    if (data_start == NULL) {
        debug("data_start calloc error");
        return NULL;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        strerror(errno);
        FREE(data_start);
        return NULL;
    }

    size_t fread_cnt = fread(data_start, sizeof(char), file_byte_sz - 1, file);
    assert(fread_cnt == (file_byte_sz - 1));

    *(data_start + file_byte_sz - 1) = '\n';

    size_t n_lines = str_cnt_chr(data_start, '\n');

    fclose(file);

    char ** arr_orig = (char **) calloc(n_lines, sizeof(char *));
    if (arr_orig == NULL) {
        strerror(errno);
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

    // arr_orig = (char **) realloc(arr_orig, line_idx);
    n_lines = line_idx;

    for (size_t i = 0; i < n_lines; i++) {
        *(arr_orig + i) = remove_extra_spaces(*(arr_orig + i));
        string_to_lower(*(arr_orig + i));
    }


    // print_ascii_chars(data_start, file_byte_sz);

    text_data_ptr->data = data_start;
    text_data_ptr->arr_orig = arr_orig;
    text_data_ptr->n_lines = n_lines;

    return text_data_ptr;
}

// int remove_extra_spaces(char *line) { // FIXME:
//     char *tmp = (char *) calloc(MAX_LINE_SZ, sizeof(char));
//     char *line_start = line;
//     char *tmp_start = tmp;

//     while (*line != '\0') {
//         if (*line != ' ') {
//             break;
//         }
//         line++;
//     }
//     while (1) {
//         *tmp++ = *line++;
//         if (*line == '\0') {
//             break;
//         }
//     }

//     ni_strncpy(line_start, tmp_start, MAX_LINE_SZ);

//     FREE(tmp_start);

//     return RETURN_TRUE;
// }




// torn_matrix_obj *torn_matrix_alloc(const size_t n, const size_t *const size_arr) {
//     torn_matrix_obj *torn_matrix_ptr = (torn_matrix_obj *) calloc(1, sizeof(torn_matrix_obj));
//     if (torn_matrix_ptr == NULL) {
//         debug("calloc error");
//         return NULL;
//     }

//     double **matrix_data_ptr = (double**) calloc(n, sizeof(double *));
//     if (matrix_data_ptr == NULL) {
//         FREE(torn_matrix_ptr);
//         return NULL;
//     }

//     size_t *size_arr_ptr = (size_t *) calloc(n, sizeof(size_t));
//     if (size_arr_ptr == NULL) {
//         FREE(torn_matrix_ptr);
//         FREE(matrix_data_ptr);
//         debug("calloc arror");
//         return NULL;
//     }

//     for (size_t i = 0; i < n; i++) {
//         *(matrix_data_ptr + i) = (double*) calloc(size_arr[i], sizeof(double));
//         if (*(matrix_data_ptr + i) == NULL) {
//             debug("calloc error");
//             FREE(matrix_data_ptr);
//             FREE(torn_matrix_ptr);
//             FREE(size_arr_ptr);
//             for (size_t j = 0; j < i; j++) {
//                 FREE(*(matrix_data_ptr + j));
//             }
//             return NULL;
//         }
//     }


//     torn_matrix_ptr->n = n;
//     torn_matrix_ptr->data = matrix_data_ptr;
//     torn_matrix_ptr->size_arr = size_arr_ptr;

//     return torn_matrix_ptr;
// }

// int torn_matrix_free(torn_matrix_obj *matrix) {
//     if (matrix == NULL) {
//         debug("matrix == nullptr");
//         return FAIL_STATE;
//     }
//     for (size_t i = 0; i < matrix->n; i++) {
//         FREE(*(matrix->data + i));
//     }
//     FREE(matrix->data);
//     FREE(matrix->size_arr);
//     FREE(matrix);
//     return TRUE_STATE;
// }

// // TODO: torn matrix - то не матрица

// torn_matrix_obj *torn_matrix_input() {
//     // TODO: Обработка переполнения n > MAX_ARR_SZ
//     size_t n = 0;
//     size_t size_arr[MAX_ARRAY_SIZE] = {0};

//     printf("n: \n");
//     if (scanf("%ld", &n) != 1) {
//         debug("scanf fail");
//         return NULL;
//     }

//     for (size_t i = 0; i < n; i++) {
//         printf("\nenter size of %ld row: ", i);
//         if (scanf("%ld", &size_arr[i]) != 1) {
//             debug("scanf fail");
//             return NULL;
//         }
//     }

//     torn_matrix_obj *matrix = torn_matrix_alloc(n, size_arr);

//     printf("\n");

//     if (matrix == NULL) {
//         debug("torn_matrix_alloc error");
//         return NULL;
//     }
//     for (size_t i = 0; i < n; i++) {
//         for (size_t j = 0; j < size_arr[i]; j++) {
//             if (scanf("%lg", &matrix->data[i][j]) != 1) {
//                 debug("scanf error");
//                 return NULL;
//             }
//         }

//     }
//     return matrix;
// }

// int torn_matrix_print(const torn_matrix_obj *const matrix) {
//     if (matrix == NULL) {
//         debug("matrix == nullptr");
//         return FAIL_STATE;
//     }
//     // for (size_t i = 0; i < matrix->n; i++) {
//     //     debug("arrsz[%ld]: %ld\n", i, matrix->size_arr_ptr[i]);
//     // }
//     // for (size_t i = 0; i < matrix->n; i++) {
//     //     ;
//     //     //FIXME: ПЕсли убрать for, то нарушится вывод матрицы. UB
//     //     // debug("arr[%ld]: %ld\n", i, matrix->size_arr_ptr[i]);
//     // }
//     for (size_t i = 0; i < (matrix->n); i++) {
//         for (size_t j = 0; j < (matrix->size_arr[i]); j++) {
//             debug("arrsz[%ld]: %ld\n", i, matrix->size_arr_ptr[i]);
//             printf("%lg ", matrix->data[i][j]);
//         }
//         printf("\n");
//     }
//     return TRUE_STATE;
// }
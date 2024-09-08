#include <cstdlib>
#include <stdio.h>

#include "storage_funcs.h"
#include "general.h"
#include "processing_funcs.h"

struct text_data {
    char **data;
    size_t *size_arr;
    size_t n;
};

int input_data(FILE* stream, char data[][MAX_LINE_SZ]) {
    size_t row_idx = 0;
    while (row_idx < MAX_LINES_CNT && fgets(data[row_idx], MAX_LINE_SZ, stream) != NULL) {
        row_idx++;
    }

    return RETURN_TRUE;
}

int remove_extra_spaces(char *line) { // FIXME:
    char *tmp = (char *) calloc(MAX_LINE_SZ, sizeof(char));
    char *line_start = line;
    char *tmp_start = tmp;

    while (*line != '\0') {
        if (*line != ' ') {
            break;
        }
        line++;
    }
    while (1) {
        *tmp++ = *line++;
        if (*line == '\0') {
            break;
        }
    }

    ni_strncpy(line_start, tmp_start, MAX_LINE_SZ);

    FREE(tmp_start);

    return RETURN_TRUE;
}

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
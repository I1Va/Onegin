// #include <cstdlib>
// #include <stdio.h>

// #include "allocation_funcs.h"
// #include "general.h"


// void **pointers_bufer = NULL;

// // int pointers_bufer_clear() {
// //     while (*pointers_bufer_curptr != NULL) {
// //         FREE(*pointers_bufer_curptr--);
// //     }
// //     return RETURN_TRUE;
// // }

// // void *ni_calloc(size_t nmemb, size_t size) {
// //     void *ptr = calloc(nmemb, size);
// //     if (ptr == NULL) {
// //         pointers_bufer_clear();
// //         return NULL;
// //     }

// //     return ptr;
// // }

// // void *ni_realloc(void *ptr, size_t general_size) { // FIXME: мб использовать бинпоиск для поиска указателя?
// //     void *old_ptr = ptr;
// //     void **pointers_bufer_pos = pointers_bufer_curptr;
// //     void *new_ptr = (char **) realloc(ptr, general_size);
// //     while (1) {
// //         if (*pointers_bufer_curptr == NULL) {
// //             debug("ni_realloc hasn't find old_ptr\n");
// //             return NULL;
// //         }
// //         if (*pointers_bufer_pos == old_ptr) {
// //             *pointers_bufer_pos-- = new_ptr;
// //         }
// //     }
// //     return new_ptr;
// // }

// // void printf_ptr_bufer() {
// //     void **ptr = pointers_bufer_start;
// //     while (ptr != NULL) {
// //         printf("[%5s] ", (char *) *ptr++);
// //     }
// //     printf("\n");
// // }

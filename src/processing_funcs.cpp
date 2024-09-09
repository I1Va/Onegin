#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "general.h"
#include "storage_funcs.h"
#include "output_funcs.h"
#include "processing_funcs.h"

size_t ni_str_len(const char *a) {
    assert(a != NULL);

    size_t len = 0;
    while (*a++ != '\0') {
        len++;
    }
    return len;
}

char *ni_strncpy(char *destination, const char *source, size_t num) {
    assert(destination != NULL);
    assert(destination != NULL);

    while (num-- && *source != '\0') {
        *destination++ = *source++;
    }

    while (num--) {
        *destination++ = '\0';
    }

    return destination;
}

char *ni_strcat(char *dest, const char *src) {
    assert(dest != NULL);
    assert(src != NULL);

    char *start_dest_ptr = dest;

    while (*dest++ != '\0');
    dest--; // *dest == '\0'

    while((*dest++ = *src++) != '\0');

    return start_dest_ptr;
}

char *ni_strstr(char *haystack, char *needle) {
    assert(haystack != NULL);
    assert(needle != NULL);

    char *start_needle = needle;
    char *substring_begin = NULL;

    while (1) {
        if (*needle == '\0') {
            return substring_begin;
        }

        if (*needle == *haystack) {
            if (substring_begin == NULL) {
                substring_begin = haystack;
            }
            needle++, haystack++;
        } else {
            substring_begin = NULL;
            needle = start_needle;
            haystack++;
        }

        if (*haystack == '\0') {
            return NULL;
        }
    }

    return NULL;
}

bool str_contains_char(const char *str, const char c) {
    while (*str != '\0') {
        if (c == *str) {
            return true;
        }
        str++;
    }
    return false;
}

bool is_intersection_str(char *source, const char* pattern) {
    while(*source != '\0') {
        if (str_contains_char(pattern, *source)) {
            return true;
        }
        source++;
    }
    return false;
}

const char *start_token(const char *str, const char *const delims) {
    while (*str != '\0') {
        if (str_contains_char(delims, *str)) {
            str++; // Пропускаем разделительные симовлы из delims
        } else {
            return str; // Нашли первый символ не из delims
        }
    }
    return NULL; // В строке нет следующего токена
}

const char *end_token(const char *str, const char *const delims) {
    while (*str != '\0') {
        if (!str_contains_char(delims, *str)) { // Идем по токену
            str++;
        } else {
            break; // *str - разделительный символ
        }
    }
    return str; // возвращаем конец токена
}

const char *ni_strtok(const char *const str, const char *const delims) {
    assert(delims != NULL);

    static const char *start_token_ptr; // не инициализирую, потому что static
    if (str != NULL) {
        start_token_ptr = start_token(str, delims); // str_ptr - начало токена
        return start_token_ptr; // если str != NULL, функция вернет указатель на строку
    }
    const char *end_token_ptr = end_token(start_token_ptr, delims);
    size_t token_len = (size_t) (end_token_ptr - start_token_ptr);

    char *return_token_start = (char *) calloc(token_len, sizeof(char));
    char *return_token_ptr = return_token_start;

    while (start_token_ptr != end_token_ptr) {
        *return_token_ptr++ = *start_token_ptr++;
    }
    *return_token_ptr = '\0';

    start_token_ptr = start_token(start_token_ptr, delims);

    return return_token_start;
}

int str_cmp__(const char *a, const char *b, const char *const end_a, const char *const end_b, const int step) {
    while (a != end_a && b != end_b) {
        if (!isalpha(*a)) {
            a += step;
            continue;
        }
        if (!isalpha(*b)) {
            b += step;
            continue;
        }
        if (tolower(*a) != tolower(*b)) {
            break;
        }
        a += step;
        b += step;
    }
    return tolower(*a) - tolower(*b);
}

int str_cmp(const char *a, const char *b) {
    const char *end_a = strchr(a, '\0');
    const char *end_b = strchr(b, '\0');
    return str_cmp__(a, b, end_a, end_b, 1);
}

int str_cmp_rev(const char *a, const char *b) {
    const char *end_a = strchr(a, '\0');
    const char *end_b = strchr(b, '\0');
    return str_cmp__(end_a, end_b, a, b, -1);
}

int str_cpy(char *a, char *b) {
    for (size_t i = 0; i < MAX_LINE_SZ; i++) {
        *a++ = *b++;
    }
    return RETURN_TRUE;
}

int str_swap(char *a, char *b) {
    char tmp[MAX_LINE_SZ] = {0};
    str_cpy(tmp, a);
    str_cpy(a, b);
    str_cpy(b, tmp);
    return RETURN_TRUE;
}

void bubble_sort(char data[][MAX_LINE_SZ]) {
    for (size_t i = 0; i < MAX_LINES_CNT - 1; i++) {
        // printf("i: %ld\n", i);
        for (size_t j = 0; j < MAX_LINES_CNT - 1; j++) {
            if (str_cmp_rev(data[j], data[j + 1]) > 0) {
                // printf("swap\n");
                str_swap(data[j], data[j + 1]);
            }
        }
    }
}
//
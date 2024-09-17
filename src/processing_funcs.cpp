#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/param.h>

#include "storage_funcs.h"

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
    assert(source != NULL);

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

bool str_contains_char(const char *const str, const char c) {
    assert(str != NULL);

    return (strchr(str, c) != NULL);
}

bool is_intersection_str(char *source, const char* pattern) {
    assert(source != NULL);
    assert(pattern != NULL);

    while(*source != '\0') {
        if (str_contains_char(pattern, *source)) {
            return true;
        }
        source++;
    }
    return false;
}

const char *start_token(const char *str, const char *const delims) {
    assert(str != NULL);
    assert(delims != NULL);

    while (*str != '\0') {
        if (str_contains_char(delims, *str)) {
            str++; // Пропускаем разделительные симовлы из delims
        } else {
            return str; // Нашли первый символ не из delims
        }
    }
    return NULL; // В строке нет следующего токена
}

size_t str_cnt_chr(const char *string, const char c, size_t n) {
    assert(string != NULL);
    size_t c_cnt = 0;
    while (n--) {
        c_cnt += (*string++ == c);
    }
    return c_cnt;
}

const char *end_token(const char *str, const char *const delims) {
    assert(str != NULL);
    assert(delims != NULL);

    while (*str != '\0') {
        if (!str_contains_char(delims, *str)) { // Идем по токену
            str++;
        } else {
            break; // *str - разделительный символ
        }
    }
    return str; // возвращаем конец токена
}

const char *ni_strtok(const char *const str, const char *const delims) { // FIXME: Неоптимальное использование памяти в *1
    assert(delims != NULL);

    static const char *start_token_ptr; // не инициализирую, потому что static
    if (str != NULL) {
        start_token_ptr = start_token(str, delims); // str_ptr - начало токена
        return start_token_ptr; // если str != NULL, функция вернет указатель на строку
    }
    const char *end_token_ptr = end_token(start_token_ptr, delims);
    size_t token_len = (size_t) (end_token_ptr - start_token_ptr);

    char *return_token_start = (char *) calloc(token_len, sizeof(char)); // FIXME: *1. токены могут плодиться и занимать неосвобождаемую память
    char *return_token_ptr = return_token_start;

    while (start_token_ptr != end_token_ptr) {
        *return_token_ptr++ = *start_token_ptr++;
    }
    *return_token_ptr = '\0';

    start_token_ptr = start_token(start_token_ptr, delims);

    return return_token_start;
}

int str_cmp__(const char *a, const char *b, const char *const end_a, const char *const end_b, const int step) {
    assert(a != NULL);
    assert(b != NULL);

    while (a != end_a && b != end_b) {
        // debug("a/b : [%c]/[%c]\n", *a, *b);
        if (!isalpha(*a)) {
            a += step;
            continue;
        }
        if (!isalpha(*b)) {
            b += step;
            continue;
        }
        if (tolower(*a) != tolower(*b)) {
            return tolower(*a) - tolower(*b);
        }
        a += step;
        b += step;
    }
    return int((end_a - a) * step - (end_b - b) * step);
}

int str_cmp(const line_data *const a, const line_data*const b) {
    assert(a != NULL);
    assert(b != NULL);

    const char *end_a = strchr(a->ptr, '\0');
    const char *end_b = strchr(b->ptr, '\0');
    return str_cmp__(a->ptr, b->ptr, end_a, end_b, 1);
}

int str_cmp_rev(line_data *a, line_data *b) {
    assert(a != NULL);
    assert(b != NULL);

    char *end_a = strchr(a->ptr, '\0');
    char *end_b = strchr(b->ptr, '\0');
    return str_cmp__(end_a, end_b, a->ptr, b->ptr, -1);
}

bool letters_in_string(char *string, const char end_char) {
    assert(string != NULL);

    while (*string != end_char) {
        if (isalpha(*string)) {
            return true;
        }
        string++;
    }
    return false;
}

void swap_brut(void *a, void *b, const size_t nmemb) {
    for (size_t i = 0; i < nmemb; i++) {
        char c = *((char *) a + i);
        *((char *) a + i) = *((char *) b + i);
        *((char *) b + i) = c;
    }
}

void swap_opt(void *a, void *b, size_t nmemb) {
    char *a_char = (char *) a;
    char *b_char = (char *) b;
    while (nmemb >= 8) {
        long long c = *(long long *) a_char;
        *((long long *) a_char) = *(long long *) b_char;
        *((long long *) b_char) = c;
        a_char += 8;
        b_char += 8;
        nmemb -= 8;
    }
    while (nmemb >= 4) {
        int c = *(int *) a_char;
        *((int *) a_char) = *((int *) b_char);
        *((int *) b_char) = c;
        a_char += 4;
        b_char += 4;
        nmemb -= 4;
    }
    while (nmemb >= 1) {
        char c = *a_char;
        *a_char = *b_char;
        *b_char = c;
        a_char += 1;
        b_char += 1;
        nmemb -= 1;
    }
}

void bubble_sort(void *const base, const size_t size, const size_t nmemb, int (*compare_func)(const void *a, const void *b)) {
    assert(base != NULL);

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size - 1; j++) {
            int res = compare_func((char *) base + j * nmemb, (char *) base + (j + 1) * nmemb);
            if (res > 0) {
                swap_opt((char *) base + j * nmemb, (char *) base + (j + 1) * nmemb, nmemb);
            }
        }
    }
}


void *partition(void *low, size_t n, size_t nmemb, int (*compare_func)(const void *a, const void *b)) {
    assert(n != 0);

    char *high = (char *) low + (n - 1) * nmemb;
    char *pivot = (char *) high;

    char *i = (char *) low - 1 * nmemb;

    for (char *j = (char *) low; j <= high - nmemb; j += 1 * nmemb) {
        if (compare_func((char *) j, (char *) pivot) < 0) {
            i += 1 * nmemb;
            swap_opt(i, j, nmemb);
        }
    }

    swap_opt(i + 1 * nmemb, high, nmemb);
    return i + 1 * nmemb;
}

void quick_sort(void *low, size_t n, size_t nmemb, int (*compare_func)(const void *a, const void *b)) {
    char *high = (char *) low + (n - 1) * nmemb;

    if (low < high) {
        char *pi = (char *) partition(low, n, nmemb, compare_func);

        quick_sort(low, (size_t) ((char *)pi - (char *)low) / nmemb, nmemb, compare_func);
        quick_sort(pi + 1 * nmemb, (size_t) ((char *) high - (char *) pi) / nmemb, nmemb, compare_func);
    }
}

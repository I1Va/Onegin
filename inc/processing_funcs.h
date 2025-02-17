#ifndef PROCESSING_FUNCS_H
#define PROCESSING_FUNCS_H

#include "storage_funcs.h"
#include <cstddef>
#include <stdio.h>

typedef int (*cmp)(const void *a, const void *b);

int str_cmp(const line_data *const a, const line_data*const b);

int str_cmp_rev(line_data *a, line_data *b);

int str_cmp__(const char *a, const char *b, const char *const end_a, const char *const end_b, const int step);

int str_cpy(char *a, char *b);

void swap_brut(void *a, void *b, const size_t nmemb);

void swap_opt(void *a, void *b, const size_t nmemb);

void bubble_sort(void *base, size_t size, size_t nmemb, int (*compare_func)(const void *a, const void *b));

size_t ni_str_len(const char *a);

char *ni_strncpy(char *destination, const char *source, size_t num);

char *ni_strcat(char *dest, const char *src);

char *ni_strstr(char *haystack, char *needle);

bool str_contains_char(const char *const str, const char c);

bool is_intersection_str(char *source, const char* pattern);

const char *start_token(const char *str, const char *const delims);

const char *end_token(const char *str, const char *const delims);

const char *ni_strtok(const char *const str, const char *const delims);

size_t str_cnt_chr(const char *string, const char c, size_t n);

void string_to_lower(char *string);

bool letters_in_string(char *string, const char end_char);

char *remove_extra_spaces(char *string);

void *pivot_random(void *base, const size_t n, const size_t nmemb,
    int (*compare_func)(const void *a, const void *b));

void *pivot_simp(void *base, const size_t n, const size_t nmemb,
    int (*compare_func)(const void *a, const void *b));

void *partition(void *low, size_t n, size_t nmemb,
    int (*compare_func)(const void *a, const void *b),
    void *(*pivot_func)(void *base, const size_t n, const size_t nmemb,
        int (*compare_func)(const void *a, const void *b)));

void quick_sort(void *low, const size_t n, const size_t nmemb,        \
    int (*compare_func)(const void *a, const void *b),
    void *(*pivot_func)(void *base, const size_t n, const size_t nmemb,
        int (*compare_func)(const void *a, const void *b)
    ) = NULL);

#endif // PROCESSING_FUNCS_H
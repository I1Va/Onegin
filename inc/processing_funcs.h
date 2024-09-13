#ifndef PROCESSING_FUNCS_H
#define PROCESSING_FUNCS_H

#include "storage_funcs.h"
#include <stdio.h>



int str_cmp__(const char *a, const char *b, const char *const end_a, const char *const end_b, const int step);

int str_cmp(const char *a, const char *b);

int str_cmp_rev(const char *a, const char *b);

int str_cpy(char *a, char *b);

int str_swap(char **a, char **b);

char ** bubble_sort(const text_data* data, bool reverse);

size_t ni_str_len(const char *a);

char *ni_strncpy(char *destination, const char *source, size_t num);

char *ni_strcat(char *dest, const char *src);

char *ni_strstr(char *haystack, char *needle);

bool str_contains_char(const char *const str, const char c);

bool is_intersection_str(char *source, const char* pattern);

const char *start_token(const char *str, const char *const delims);

const char *end_token(const char *str, const char *const delims);

const char *ni_strtok(const char *const str, const char *const delims);

size_t str_cnt_chr(const char *string, const char c);

void string_to_lower(char *string);

bool letters_in_string(char *string, const char end_char);

char *remove_extra_spaces(char *string);

#endif // PROCESSING_FUNCS_H
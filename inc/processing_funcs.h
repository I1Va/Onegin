#include "storage_funcs.h"
#include <stdio.h>



int str_cmp(char *a, char *b);

int str_cpy(char *a, char *b);

int str_swap(char *a, char *b);

void bubble_sort(char data[][MAX_LINE_SZ]);

size_t ni_str_len(const char *a);

char *ni_strncpy(char *destination, const char *source, size_t num);

char *ni_strcat(char *dest, const char *src);

char *ni_strstr(char *haystack, char *needle);

bool str_contains_char(const char *str, const char c);

bool is_intersection_str(char *source, const char* pattern);

const char *start_token(const char *str, const char *const delims);

const char *end_token(const char *str, const char *const delims);

const char *ni_strtok(const char *const str, const char *const delims);

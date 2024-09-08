#ifndef STORAGE_FUNCS_H
#define STORAGE_FUNCS_H

#include <string.h>
#include <stdio.h>

const size_t MAX_LINE_SZ = 512;
const size_t MAX_LINES_CNT = 512;

int input_data(FILE* stream, char data[][MAX_LINE_SZ]);

int remove_extra_spaces(char *line);

#endif // STORAGE_FUNCS_H
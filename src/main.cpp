#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "processing_funcs.h"
#include "storage_funcs.h"
#include "output_funcs.h"

int main() {
    // TODO: протестить сампоисные строковые функции
    // onegin_eng.txt
    text_data* data = input_data("./test.txt");
    data->arr_sorted = bubble_sort(data);

    print_text_arr(data->arr_sorted, data->n_lines);

    return EXIT_SUCCESS;
}

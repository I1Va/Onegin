#include "error_processing.h"

// struct opt_file { // TODO: реализовать структуру option
//     char *option;
//     char *fmt;
//     char *name;
// };

struct path_data {
    char *input_path;
    char *output_path;
};

path_data *path_data_constructor(const char *src_inp_file, const char *src_out_file);

void path_data_destructor(path_data *pathes);

void main_mode_launch(const char input_file_path[], const char output_file_path[], err_code *const ReturnErr);

path_data *mode_launcher(const int argc, const char *argv[], err_code *const ReturnErr);

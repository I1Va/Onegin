#include "error_processing.h"

// struct opt_file { // TODO: реализовать структуру option
//     char *option;
//     char *fmt;
//     char *name;
// };

void main_mode_launch(const char input_file_path[], const char output_file_path[], err_code *const return_err);

void mode_launcher(const int argc, const char *argv[], err_code *const return_err);

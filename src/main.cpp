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
#include "general.h"
#include "output_funcs.h"
#include "error_processing.h"
#include "args_processing.h"

int main(const int argc, const char *argv[]) {
    err_code LastErr = ERR_OK;
    mode_launcher(argc, argv, &LastErr);

    if (LastErr != ERR_OK) {
        DEBUG_ERROR(LastErr);
        return EXIT_FAILURE;
    }


     // TODO: я нихрена не понимаю, что происходит в программе
                                            //       Ты просто взвалил обязанности мейна на другую функцию
                                            //       Поэтому смысла вообще нет в твоём err_code здесь

    // TODO: Сделай так, чтобы мейн состоял из объявления структуры,
    //       конструктора для её заполнения, функция, которая принимает структуру и сортирует строки
    //       и деструктор
}

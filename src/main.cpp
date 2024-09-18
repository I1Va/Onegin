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

#include <time.h>


int main(const int argc, const char *argv[]) {
    err_code LastErr = ERR_OK;
    TIMER_START mode_launcher(argc, argv, &LastErr); TIMER_END(stderr)

    if (LastErr != ERR_OK) {
        DEBUG_ERROR(LastErr);
        return EXIT_FAILURE;
    }
}

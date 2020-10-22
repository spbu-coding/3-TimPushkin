#include <stdlib.h>
#include <stdio.h>

#include "error_handle.h"

void error_handle(const char* const error_message) {
    fprintf(stderr, "%s", error_message);
    exit(1);
}

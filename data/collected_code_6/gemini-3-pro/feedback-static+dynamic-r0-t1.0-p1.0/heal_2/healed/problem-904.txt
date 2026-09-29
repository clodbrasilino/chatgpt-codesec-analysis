#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) != -1) {
        char *endptr;
        int input_number = (int)strtol(buffer, &endptr, 10);
        
        if (endptr == buffer) {
            free(buffer);
            return 1;
        }

        if (is_even(input_number)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    } else {
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}
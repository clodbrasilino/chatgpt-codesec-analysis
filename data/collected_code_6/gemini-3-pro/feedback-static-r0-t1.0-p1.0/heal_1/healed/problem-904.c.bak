#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *endptr;
        int input_number = (int)strtol(buffer, &endptr, 10);
        
        if (endptr == buffer) {
            return 1;
        }

        if (is_even(input_number)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    } else {
        return 1;
    }

    return 0;
}
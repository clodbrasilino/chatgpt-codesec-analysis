#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_odd(int number) {
    return (number & 1) != 0;
}

int main(void) {
    char input[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'number' can be reduced. [variableScope]
     */
    int number;

    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        number = (int)strtol(input, &endptr, 10);

        if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
            return EXIT_FAILURE;
        }

        if (is_odd(number)) {
            printf("Odd\n");
        } else {
            printf("Even\n");
        }

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
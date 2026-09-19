#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'input_number' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'input_number' can be reduced. [variableScope]
     */
    int input_number = 0;
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *endptr;
        input_number = (int)strtol(buffer, &endptr, 10);
        
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
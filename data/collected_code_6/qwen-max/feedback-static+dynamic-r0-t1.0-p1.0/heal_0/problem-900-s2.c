#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int starts_with_number(const char *str, int number) {
    char num_str[12];
    sprintf(num_str, "%d", number);
    return strncmp(str, num_str, strlen(num_str)) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string> <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_string = argv[1];
    int input_number = atoi(argv[2]);

    if (starts_with_number(input_string, input_number)) {
        printf("The string '%s' starts with the number %d.\n", input_string, input_number);
    } else {
        printf("The string '%s' does not start with the number %d.\n", input_string, input_number);
    }

    return EXIT_SUCCESS;
}
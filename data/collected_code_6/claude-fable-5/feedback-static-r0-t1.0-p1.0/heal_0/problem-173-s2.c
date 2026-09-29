#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *remove_non_alnum(char *str)
{
    size_t read;
    size_t write;

    if (str == NULL) {
        return NULL;
    }

    write = 0;
    for (read = 0; str[read] != '\0'; read++) {
        if (isalnum((unsigned char)str[read])) {
            str[write] = str[read];
            write++;
        }
    }
    str[write] = '\0';

    return str;
}

int main(void)
{
    char input[] = "Hello, World! 123 #$%^ test_case-42";
    char *result;

    result = remove_non_alnum(input);
    if (result == NULL) {
        fprintf(stderr, "Error: NULL input string\n");
        return EXIT_FAILURE;
    }

    if (printf("Result: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *remove_non_alnum(char *str)
{
    size_t read_idx;
    size_t write_idx;

    if (str == NULL) {
        return NULL;
    }

    write_idx = 0;
    for (read_idx = 0; str[read_idx] != '\0'; read_idx++) {
        if (isalnum((unsigned char)str[read_idx])) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
    }
    str[write_idx] = '\0';

    return str;
}

int main(void)
{
    char buffer[] = "Hello, World! 123 #$% foo_bar";
    char *result;

    result = remove_non_alnum(buffer);
    if (result == NULL) {
        fprintf(stderr, "Error: null string provided\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
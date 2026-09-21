#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str) != 0) {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    /* Possible weaknesses found:
     *  Although the value stored to 'length' is used in the enclosing expression, the value is never actually read from 'length' [deadcode.DeadStores]
     */
    while ((length = getline(&line, &capacity, stdin)) != -1) {
        count += count_numeric_values(line);
    }

    if (ferror(stdin) != 0) {
        fprintf(stderr, "Failed to read input.\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    printf("%zu\n", count);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_std_occurrences(const char *str)
{
    const char target[] = "std";
    size_t count = 0;
    const char *current = str;

    if (str == NULL) {
        return 0;
    }

    while ((current = strstr(current, target)) != NULL) {
        ++count;
        ++current;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    printf("%zu\n", count_std_occurrences(input));

    free(input);
    return EXIT_SUCCESS;
}
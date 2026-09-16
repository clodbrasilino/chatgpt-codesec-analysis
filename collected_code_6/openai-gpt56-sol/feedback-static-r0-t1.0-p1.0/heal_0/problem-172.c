#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_std_occurrences(const char *string)
{
    const char target[] = "std";
    size_t count = 0;
    const char *position = string;

    if (string == NULL) {
        return 0;
    }

    while ((position = strstr(position, target)) != NULL) {
        ++count;
        ++position;
    }

    return count;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }

    printf("%zu\n", count_std_occurrences(string));

    free(string);
    return EXIT_SUCCESS;
}
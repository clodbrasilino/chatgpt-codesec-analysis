#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_first_and_last(char *str, size_t length, char target)
{
    size_t first = length;
    size_t last = length;

    if (str == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == target) {
            if (first == length) {
                first = i;
            }
            last = i;
        }
    }

    if (first == length) {
        return 0;
    }

    if (last != first) {
        memmove(str + last, str + last + 1, length - last);
        --length;
    }

    memmove(str + first, str + first + 1, length - first);
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char target;
    int result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (scanf("%c", &target) != 1) {
        free(line);
        return EXIT_FAILURE;
    }

    result = remove_first_and_last(line, (size_t)length, target);
    if (result < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", line) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
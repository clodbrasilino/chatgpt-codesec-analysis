#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_first_and_last(char *str, char target)
{
    char *first;
    char *last;

    if (str == NULL) {
        return -1;
    }

    first = strchr(str, target);
    if (first == NULL) {
        return 0;
    }

    last = strrchr(str, target);
    if (last != first) {
        memmove(last, last + 1, strlen(last + 1) + 1);
    }

    memmove(first, first + 1, strlen(first + 1) + 1);
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char target;
    int result;

    if (getline(&line, &capacity, stdin) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    line[strcspn(line, "\n")] = '\0';

    if (scanf("%c", &target) != 1) {
        free(line);
        return EXIT_FAILURE;
    }

    result = remove_first_and_last(line, target);
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
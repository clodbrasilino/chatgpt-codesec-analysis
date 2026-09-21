#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
        --end;
    }
}

static int left_rotate_string(char *string, size_t positions)
{
    size_t length;

    if (string == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    if (length == 0U) {
        return 0;
    }

    positions %= length;
    if (positions == 0U) {
        return 0;
    }

    reverse_range(string, 0U, positions - 1U);
    reverse_range(string, positions, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;
    unsigned long long positions;
    char extra;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    if (scanf("%llu%c", &positions, &extra) != 2 || extra != '\n') {
        free(line);
        return EXIT_FAILURE;
    }

    if (left_rotate_string(line, (size_t)(positions % (SIZE_MAX + 1ULL))) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}
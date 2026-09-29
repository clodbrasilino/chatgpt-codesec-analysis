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

static int left_rotate(char *string, size_t positions)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char rotation_text[64];
    char *end = NULL;
    unsigned long long parsed_rotation;
    size_t rotation;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");
    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        return EXIT_FAILURE;
    }

    if (fgets(rotation_text, sizeof rotation_text, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    parsed_rotation = strtoull(rotation_text, &end, 10);
    if (end == rotation_text) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0' || parsed_rotation > (unsigned long long)SIZE_MAX) {
        return EXIT_FAILURE;
    }

    rotation = (size_t)parsed_rotation;

    if (left_rotate(input, rotation) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
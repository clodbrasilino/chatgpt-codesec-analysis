#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int reverse_string(char *str)
{
    size_t len;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }

    return 0;
}

static int reverse_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (reverse_string(list[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *words[] = {"hello", "world", "reverse", "strings", "example"};
    size_t count = sizeof(words) / sizeof(words[0]);
    char **list;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    int status = EXIT_SUCCESS;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(words[i]) + 1;
        list[i] = malloc(len);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            while (i > 0) {
                i--;
                free(list[i]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list[i], words[i], len);
    }

    printf("Original strings:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        status = EXIT_FAILURE;
    } else {
        printf("Reversed strings:\n");
        for (i = 0; i < count; i++) {
            printf("%s\n", list[i]);
        }
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return status;
}
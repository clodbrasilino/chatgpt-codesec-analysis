#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *str)
{
    char *src;
    char *dst;

    if (str == NULL) {
        return;
    }

    src = str;
    dst = str;

    while (*src != '\0') {
        if (!isdigit((unsigned char)*src)) {
            *dst = *src;
            ++dst;
        }
        ++src;
    }
    *dst = '\0';
}

static void remove_digits_from_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        remove_digits(list[i]);
    }
}

int main(void)
{
    static const char *const samples[] = {
        "abc123def",
        "no digits here",
        "9876543210",
        "h3ll0 w0rld",
        ""
    };
    const size_t count = sizeof(samples) / sizeof(samples[0]);
    char **list;
    size_t i;
    int status;

    status = EXIT_SUCCESS;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "error: out of memory\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        list[i] = NULL;
    }

    for (i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        list[i] = malloc(strlen(samples[i]) + 1U);
        if (list[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            status = EXIT_FAILURE;
            goto cleanup;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(list[i], samples[i]);
    }

    remove_digits_from_list(list, count);

    for (i = 0; i < count; ++i) {
        if (printf("%s\n", list[i]) < 0) {
            fprintf(stderr, "error: failed to write output\n");
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

cleanup:
    for (i = 0; i < count; ++i) {
        free(list[i]);
    }
    free(list);

    return status;
}
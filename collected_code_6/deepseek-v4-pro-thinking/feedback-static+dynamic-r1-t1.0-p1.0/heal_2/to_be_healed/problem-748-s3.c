#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *add_spaces(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    const char *p = input;
    size_t space_cnt = 0;

    while (*p) {
        if (isupper((unsigned char)*p) && p != input) {
            space_cnt++;
        }
        p++;
    }

    size_t len = (size_t)(p - input);

    if (len > (size_t)-1 - space_cnt) {
        return NULL;
    }

    size_t total = len + space_cnt;
    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src = 0;
    size_t dst = 0;
    p = input;

    while (*p) {
        if (isupper((unsigned char)*p) && p != input) {
            size_t copy_len = (size_t)(p - input) - src;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst, input + src, copy_len);
            dst += copy_len;
            result[dst++] = ' ';
            src = (size_t)(p - input);
        }
        p++;
    }

    size_t remaining = len - src;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + dst, input + src, remaining);
    dst += remaining;
    result[dst] = '\0';

    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    char *spaced = add_spaces(input);

    if (spaced == NULL) {
        fprintf(stderr, "Error processing input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", spaced);
    free(spaced);
    return EXIT_SUCCESS;
}
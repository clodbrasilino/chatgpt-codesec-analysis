#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    size_t len = 0;
    size_t i;
    size_t ri = 0;
    int upper = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    unsigned char c;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    while (input[len] != '\0') {
        len++;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        c = (unsigned char)input[i];
        if (c == '_' && i + 1 < len && isalpha((unsigned char)input[i + 1])) {
            upper = 1;
            continue;
        }
        if (upper && isalpha(c)) {
            result[ri++] = (char)toupper(c);
        } else {
            result[ri++] = (char)c;
        }
        upper = 0;
    }

    result[ri] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    char *out;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;
    int any = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    const char *defaults[] = { "android_tv", "google_pixel", "apple_watch" };
    size_t count = sizeof(defaults) / sizeof(defaults[0]);
    /* Possible weaknesses found:
     *  The scope of the variable 'k' can be reduced. [variableScope]
     */
    size_t k;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            out = snake_to_camel(argv[i]);
            if (out == NULL) {
                return EXIT_FAILURE;
            }
            printf("%s\n", out);
            free(out);
        }
        return EXIT_SUCCESS;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%4095s", buffer) == 1) {
        any = 1;
        out = snake_to_camel(buffer);
        if (out == NULL) {
            return EXIT_FAILURE;
        }
        printf("%s\n", out);
        free(out);
    }

    if (!any) {
        for (k = 0; k < count; k++) {
            out = snake_to_camel(defaults[k]);
            if (out == NULL) {
                return EXIT_FAILURE;
            }
            printf("%s\n", out);
            free(out);
        }
    }

    return EXIT_SUCCESS;
}
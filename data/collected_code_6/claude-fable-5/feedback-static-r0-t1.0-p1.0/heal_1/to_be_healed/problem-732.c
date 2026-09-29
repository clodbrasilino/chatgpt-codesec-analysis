#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int replace_chars(char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0U; i < len; i++) {
        if ((str[i] == ' ') || (str[i] == ',') || (str[i] == '.')) {
            str[i] = ':';
        }
    }

    return 0;
}

int main(void)
{
    char text[] = "Hello, world. This is a test string.";
    int result;

    result = replace_chars(text);
    if (result != 0) {
        (void)fprintf(stderr, "Error: invalid input string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", text) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 8192

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);

    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char *src = input;
    char *dst = result;
    size_t remaining = len;

    while (*src != '\0' && remaining > 0) {
        if (remaining >= 4 && strncmp(src, "road", 4) == 0) {
            *dst++ = 'r';
            *dst++ = 'd';
            *dst++ = '.';
            src += 4;
            remaining -= 4;
        } else {
            *dst++ = *src++;
            remaining--;
        }
    }
    
    *dst = '\0';

    return result;
}

int main(void) {
    const char *test_string = "123 Old Country road";
    char *result_string = abbreviate_road(test_string);

    if (result_string != NULL) {
        printf("%s\n", result_string);
        free(result_string);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
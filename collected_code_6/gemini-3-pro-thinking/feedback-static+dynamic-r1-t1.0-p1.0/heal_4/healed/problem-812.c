#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 8192

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    const char *end = memchr(input, '\0', MAX_INPUT_LEN);
    if (end == NULL) {
        return NULL;
    }
    size_t len = end - input;

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
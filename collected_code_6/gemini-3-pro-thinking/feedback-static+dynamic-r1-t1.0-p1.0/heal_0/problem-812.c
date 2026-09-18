#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    const char *src = input;
    char *dst = result;

    while (*src != '\0') {
        if (strncmp(src, "road", 4) == 0) {
            memcpy(dst, "rd.", 3);
            dst += 3;
            src += 4;
        } else {
            *dst = *src;
            dst++;
            src++;
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'len<4096' is not redundant
     */
    while (len < MAX_INPUT_LEN) {
        /* Possible weaknesses found:
         *  Either the condition 'len<4096' is redundant or the array 'input[21]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
         *  Array index out of bounds
         */
        if (input[len] == '\0') {
            break;
        }
        len++;
    }

    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    const char *src = input;
    char *dst = result;
    size_t remaining = len;

    while (remaining > 0) {
        if (remaining >= 4 && strncmp(src, "road", 4) == 0) {
            dst[0] = 'r';
            dst[1] = 'd';
            dst[2] = '.';
            dst += 3;
            src += 4;
            remaining -= 4;
        } else {
            *dst = *src;
            dst++;
            src++;
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
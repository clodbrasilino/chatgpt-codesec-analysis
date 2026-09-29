#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 8192

char *abbreviate_road(const char *input);

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (input[len] != '\0' && len < MAX_INPUT_LEN) {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    char *dst = result;

    while (i < len) {
        if (len - i >= 4 && strncmp(&input[i], "road", 4) == 0) {
            dst[0] = 'r';
            dst[1] = 'd';
            dst[2] = '.';
            dst += 3;
            i += 4;
        } else {
            *dst = input[i];
            dst++;
            i++;
        }
    }
    *dst = '\0';

    return result;
}

int main(void) {
    const char *original_text = "The old dusty road leads to the new road.";
    char *modified_text = abbreviate_road(original_text);

    if (modified_text != NULL) {
        printf("%s\n", modified_text);
        free(modified_text);
    }

    return 0;
}
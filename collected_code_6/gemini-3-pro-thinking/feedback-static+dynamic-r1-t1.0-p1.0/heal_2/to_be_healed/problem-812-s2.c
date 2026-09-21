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
     *  Array index out of bounds
     *  Either the condition 'len<8192' is redundant or the array 'input[42]' is accessed at index 8191, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len<8192' is not redundant
     */
    while (len < MAX_INPUT_LEN && input[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (len - i >= 4 && strncmp(&input[i], "road", 4) == 0) {
            result[j++] = 'r';
            result[j++] = 'd';
            result[j++] = '.';
            i += 4;
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';

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
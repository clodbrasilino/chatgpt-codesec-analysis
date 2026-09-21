#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    const size_t max_len = 4096;
    size_t length = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Array index 'length' is used before limits check. [arrayIndexThenCheck]
     *  Either the condition 'length==max_len' is redundant or the array 'input[16]' is accessed at index 4096, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (input[length] != '\0' && length < max_len) {
        length++;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'length==max_len' is not redundant
     */
    if (length == max_len) {
        return NULL;
    }

    size_t underscore_count = 0;
    for (size_t i = 1; i < length; i++) {
        if (isupper((unsigned char)input[i])) {
            underscore_count++;
        }
    }

    size_t output_size = length + underscore_count + 1;
    char *output = malloc(output_size);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0) {
                output[out_idx++] = '_';
            }
            output[out_idx++] = (char)tolower((unsigned char)input[i]);
        } else {
            output[out_idx++] = input[i];
        }
    }
    output[out_idx] = '\0';

    return output;
}

int main(void) {
    const char *camel = "camelCaseString";
    char *snake = camel_to_snake(camel);

    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    }

    return 0;
}
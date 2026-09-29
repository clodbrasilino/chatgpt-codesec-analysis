#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input_len < MAX_INPUT_LEN && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    size_t result_capacity = input_len + 4;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < input_len) {
        if (i + 4 <= input_len &&
            (unsigned char)input[i + 0] == 'r' &&
            (unsigned char)input[i + 1] == 'o' &&
            (unsigned char)input[i + 2] == 'a' &&
            (unsigned char)input[i + 3] == 'd') {
            
            int left_boundary = (i == 0) || !isalpha((unsigned char)input[i - 1]);
            int right_boundary = (i + 4 >= input_len) || !isalpha((unsigned char)input[i + 4]);
            
            if (left_boundary && right_boundary) {
                if (j + 3 >= result_capacity) {
                    result_capacity *= 2;
                    char *tmp = realloc(result, result_capacity);
                    if (tmp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = tmp;
                }
                result[j++] = input[i];
                result[j++] = 'd';
                result[j++] = '.';
                i += 4;
                continue;
            }
        }
        if (j + 1 >= result_capacity) {
            result_capacity *= 2;
            char *tmp = realloc(result, result_capacity);
            if (tmp == NULL) {
                free(result);
                return NULL;
            }
            result = tmp;
        }
        result[j++] = input[i++];
    }
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "123 road street",
        "road road road",
        "main street road",
        "roads and driveways",
        "Road",
        NULL
    };

    for (int i = 0; i < 6; i++) {
        char *result = abbreviate_road(tests[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("(null or allocation failed)\n");
        }
    }

    return 0;
}
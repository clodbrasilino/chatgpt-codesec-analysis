#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
        if (input_len > 4096) {
            return NULL;
        }
    }

    size_t result_capacity = input_len + 4;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < input_len) {
        if (i + 3 < input_len &&
            tolower((unsigned char)input[i]) == 'r' &&
            tolower((unsigned char)input[i + 1]) == 'o' &&
            tolower((unsigned char)input[i + 2]) == 'a' &&
            tolower((unsigned char)input[i + 3]) == 'd') {
            
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
    const char *test1 = "123 road street";
    const char *test2 = "road road road";
    const char *test3 = "main street road";
    const char *test4 = "roads and driveways";
    const char *test5 = "Road";
    const char *test6 = NULL;

    char *results[6];
    results[0] = abbreviate_road(test1);
    results[1] = abbreviate_road(test2);
    results[2] = abbreviate_road(test3);
    results[3] = abbreviate_road(test4);
    results[4] = abbreviate_road(test5);
    results[5] = abbreviate_road(test6);

    for (int i = 0; i < 6; i++) {
        if (results[i] != NULL) {
            printf("%s\n", results[i]);
            free(results[i]);
        } else {
            printf("(null or allocation failed)\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t result_size = input_len * 2 + 1;
    
    if (result_size < input_len) {
        return NULL;
    }
    
    char *result = malloc(result_size);
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
            
            if ((i == 0 || !isalpha((unsigned char)input[i - 1])) &&
                (i + 4 >= input_len || !isalpha((unsigned char)input[i + 4]))) {
                if (j + 3 >= result_size) {
                    size_t new_size = result_size * 2;
                    char *temp = realloc(result, new_size);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    result_size = new_size;
                }
                result[j++] = input[i];
                result[j++] = 'd';
                result[j++] = '.';
                i += 4;
                continue;
            }
        }
        if (j + 1 >= result_size) {
            size_t new_size = result_size * 2;
            char *temp = realloc(result, new_size);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            result = temp;
            result_size = new_size;
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

#define MAX_TESTS 6
#define MAX_RESULT_LEN 8192

int main(void) {
    const char *tests[MAX_TESTS];
    tests[0] = "123 road street";
    tests[1] = "road road road";
    tests[2] = "main street road";
    tests[3] = "roads and driveways";
    tests[4] = "Road";
    tests[5] = NULL;

    char *results[MAX_TESTS];

    for (int i = 0; i < MAX_TESTS; i++) {
        if (tests[i] != NULL && strlen(tests[i]) >= MAX_RESULT_LEN) {
            results[i] = NULL;
        } else {
            results[i] = abbreviate_road(tests[i]);
        }
    }

    for (int i = 0; i < MAX_TESTS; i++) {
        if (tests[i] == NULL) {
            printf("(null input)\n");
        } else if (results[i] == NULL) {
            printf("(allocation failed)\n");
        } else {
            printf("%s\n", results[i]);
            free(results[i]);
        }
    }

    return 0;
}
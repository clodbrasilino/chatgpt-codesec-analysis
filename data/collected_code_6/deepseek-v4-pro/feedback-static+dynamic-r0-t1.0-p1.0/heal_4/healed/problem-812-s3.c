#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_word_boundary(const char *input, size_t pos, size_t input_len) {
    if (pos == 0 || pos >= input_len) {
        return 1;
    }
    return !isalpha((unsigned char)input[pos]);
}

static int is_full_word(const char *input, size_t start, size_t end, size_t input_len) {
    return is_word_boundary(input, start, input_len) && 
           is_word_boundary(input, end, input_len);
}

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0' && input_len < 8192) {
        input_len++;
    }
    
    if (input_len >= 8192) {
        return NULL;
    }

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
        if (i + 4 <= input_len) {
            if (tolower((unsigned char)input[i]) == 'r' &&
                tolower((unsigned char)input[i + 1]) == 'o' &&
                tolower((unsigned char)input[i + 2]) == 'a' &&
                tolower((unsigned char)input[i + 3]) == 'd') {
                
                if (is_full_word(input, i, i + 4, input_len)) {
                    if (j + 3 >= result_size) {
                        size_t new_size = result_size * 2;
                        if (new_size <= result_size) {
                            free(result);
                            return NULL;
                        }
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
        }
        if (j + 2 >= result_size) {
            size_t new_size = result_size * 2;
            if (new_size <= result_size) {
                free(result);
                return NULL;
            }
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

int main(void) {
    const char *tests[] = {
        "123 road street",
        "road road road",
        "main street road",
        "roads and driveways",
        "Road",
        NULL
    };
    
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    char *results[6];

    for (size_t i = 0; i < num_tests && i < 6; i++) {
        results[i] = abbreviate_road(tests[i]);
    }

    for (size_t i = 0; i < num_tests && i < 6; i++) {
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
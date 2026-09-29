#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }

    size_t len = strnlen(input, 4096);
    if (len == 0 || len >= 4096) {
        char* result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t capacity = len + 1;
    char* result = (char*)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    size_t word_start = 0;
    size_t word_length = 0;
    int in_word = 0;

    while (i <= len) {
        if (i < len && isalnum((unsigned char)input[i])) {
            if (!in_word) {
                word_start = i;
                word_length = 1;
                in_word = 1;
            } else {
                word_length++;
            }
        } else {
            if (in_word) {
                if (word_length != (size_t)k) {
                    if (j > 0) {
                        if (j + 1 >= capacity) {
                            size_t new_capacity = capacity * 2;
                            if (new_capacity <= capacity) {
                                free(result);
                                return NULL;
                            }
                            char* temp = (char*)realloc(result, new_capacity);
                            if (temp == NULL) {
                                free(result);
                                return NULL;
                            }
                            result = temp;
                            capacity = new_capacity;
                        }
                        result[j++] = ' ';
                    }
                    if (j + word_length >= capacity) {
                        size_t new_capacity = capacity + word_length + 1;
                        if (new_capacity <= capacity) {
                            free(result);
                            return NULL;
                        }
                        char* temp = (char*)realloc(result, new_capacity);
                        if (temp == NULL) {
                            free(result);
                            return NULL;
                        }
                        result = temp;
                        capacity = new_capacity;
                    }
                    if (word_length > 0) {
                        if (j + word_length > capacity) {
                            free(result);
                            return NULL;
                        }
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(result + j, input + word_start, word_length);
                        j += word_length;
                    }
                }
                in_word = 0;
                word_length = 0;
            }
        }
        i++;
    }

    if (j >= capacity) {
        size_t new_capacity = j + 1;
        if (new_capacity <= capacity) {
            free(result);
            return NULL;
        }
        char* temp = (char*)realloc(result, new_capacity);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
    }
    result[j] = '\0';

    char* final_result = (char*)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main() {
    char input[] = "This is a test string with words of different lengths";
    int k = 2;
    
    char* result = remove_words_with_length(input, k);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    } else {
        printf("Error processing string\n");
    }

    char input2[] = "hello world this is a test";
    k = 5;
    result = remove_words_with_length(input2, k);
    if (result != NULL) {
        printf("Original: %s\n", input2);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}
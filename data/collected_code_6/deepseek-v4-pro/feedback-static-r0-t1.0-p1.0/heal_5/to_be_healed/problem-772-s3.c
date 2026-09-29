#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* str, int k) {
    if (str == NULL || k <= 0) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        if (len >= SIZE_MAX / 2) {
            return NULL;
        }
        len++;
    }

    /* Possible weaknesses found:
     *  max_len is assigned 'len+1' here.
     */
    size_t max_len = len + 1;
    /* Possible weaknesses found:
     *  Condition 'max_len<len' is always false [knownConditionTrueFalse]
     *  Condition 'max_len<len' is always false
     */
    if (max_len < len) {
        return NULL;
    }

    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int word_length = 0;
    int word_start = -1;

    while (i <= len) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (word_start == -1) {
                word_start = (int)i;
            }
            word_length++;
        } else {
            if (word_start != -1) {
                if (word_length != k) {
                    if (j > 0 && result[j-1] != ' ') {
                        if (j < max_len - 1) {
                            result[j++] = ' ';
                        }
                    }
                    size_t remaining = max_len - j - 1;
                    size_t copy_len = (size_t)word_length;
                    if (copy_len > remaining) {
                        copy_len = remaining;
                    }
                    if (copy_len > 0 && j + copy_len <= max_len) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(result + j, str + word_start, copy_len);
                        j += copy_len;
                    }
                }
                word_start = -1;
                word_length = 0;
            }
        }
        i++;
    }

    if (j < max_len) {
        result[j] = '\0';
    } else {
        result[max_len - 1] = '\0';
    }

    return result;
}

int main(void) {
    const char* input = "hello world this is a test string";
    int k = 2;
    
    char* result = remove_words_with_length(input, k);
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("After removing words of length %d: %s\n", k, result);
        free(result);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_words_with_length(const char* input, int k) {
    if (input == NULL || k <= 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int word_start = -1;
    int word_length = 0;

    while (i <= len) {
        if (isalnum((unsigned char)input[i])) {
            if (word_start == -1) {
                word_start = i;
                word_length = 1;
            } else {
                word_length++;
            }
        } else {
            if (word_start != -1) {
                if (word_length != k) {
                    if (j > 0 && result[j-1] != ' ') {
                        result[j++] = ' ';
                    }
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(result + j, input + word_start, word_length);
                    j += word_length;
                }
                word_start = -1;
                word_length = 0;
            }
        }
        i++;
    }

    if (j > 0 && result[j-1] == ' ') {
        j--;
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
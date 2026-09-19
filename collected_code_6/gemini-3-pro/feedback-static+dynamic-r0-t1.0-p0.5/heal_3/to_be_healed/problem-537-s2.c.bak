#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 1000
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char* str) {
    if (str == NULL) {
        return strdup("None");
    }

    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    int word_count = 0;
    const char* p = str;
    char buffer[MAX_WORD_LEN];
    int buf_idx = 0;
    char* result = NULL;

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = tolower((unsigned char)*p);
            }
        } else if (buf_idx > 0) {
            buffer[buf_idx] = '\0';
            
            for (int i = 0; i < word_count; i++) {
                if (strcmp(words[i], buffer) == 0) {
                    result = strdup(buffer);
                    goto cleanup;
                }
            }

            if (word_count < MAX_WORDS) {
                words[word_count] = strdup(buffer);
                if (words[word_count] == NULL) {
                    goto cleanup;
                }
                word_count++;
            }
            buf_idx = 0;
        }
        p++;
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], buffer) == 0) {
                result = strdup(buffer);
                goto cleanup;
            }
        }
    }

cleanup:
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    if (result == NULL) {
        result = strdup("None");
    }

    return result;
}

int main(void) {
    char buffer[65536];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char* repeated_word = find_first_repeated_word(buffer);
        if (repeated_word != NULL) {
            printf("%s", repeated_word);
            free(repeated_word);
        }
    } else {
        printf("None");
    }

    return 0;
}
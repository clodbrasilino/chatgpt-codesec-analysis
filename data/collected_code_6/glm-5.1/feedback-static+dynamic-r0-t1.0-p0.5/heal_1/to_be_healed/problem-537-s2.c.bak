#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

/* Possible weaknesses found:
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 */
char *find_first_repeated_word(char *str) {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = 0;
    char buffer[MAX_WORD_LEN];
    int buf_idx = 0;

    if (str == NULL) {
        return NULL;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = tolower((unsigned char)str[i]);
            }
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                for (int j = 0; j < count; j++) {
                    if (strcmp(words[j], buffer) == 0) {
                        char *result = malloc(strlen(buffer) + 1);
                        if (result == NULL) {
                            return NULL;
                        }
                        strcpy(result, buffer);
                        return result;
                    }
                }
                if (count < MAX_WORDS) {
                    strcpy(words[count], buffer);
                    count++;
                }
                buf_idx = 0;
            }
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int j = 0; j < count; j++) {
            if (strcmp(words[j], buffer) == 0) {
                char *result = malloc(strlen(buffer) + 1);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, buffer);
                return result;
            }
        }
    }

    return NULL;
}

int main() {
    char str[] = "This is a test test string to find repeated word.";
    char *repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;
    char *output, *temp;
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    int i, j, found;

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        found = 0;
        for (i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(words[word_count++], token, MAX_WORD_LENGTH - 1);
        }
        token = strtok(NULL, " ");
    }

    temp = output = (char *)malloc(strlen(input) + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < word_count; ++i) {
        strcpy(temp, words[i]);
        temp += strlen(words[i]);
        if (i < word_count - 1) {
            *temp++ = ' ';
        }
    }
    *temp = '\0';

    return output;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *result = remove_duplicates(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}
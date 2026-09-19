#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  */

char* findFirstRepeatedWord(const char* input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {""};
    int word_count = 0;
    const char* p = input;
    while (*p) {
        const char* start = p;
        while (*p && *p != ' ' && *p != '\n' && *p != '\t') {
            p++;
        }
        if (start != p) {
            for (int i = 0; i < word_count; ++i) {
                if (strncmp(words[i], start, p - start) == 0) {
                    char* result = malloc(p - start + 1);
                    if (result) {
                        strncpy(result, start, p - start);
                        result[p - start] = '\0';
                        return result;
                    } else {
                        return NULL;
                    }
                }
            }
            if (word_count < MAX_WORDS) {
                strncpy(words[word_count], start, p - start);
                words[word_count][p - start] = '\0';
                word_count++;
            }
        }
        while (*p && (*p == ' ' || *p == '\n' || *p == '\t')) {
            p++;
        }
    }
    return NULL;
}

int main() {
    const char* inputs[] = {"ab ab", "ab", "ca ca", "This is a test test string to find the first repeated word"};
    for (int i = 0; i < 4; ++i) {
        char* result = findFirstRepeatedWord(inputs[i]);
        if (result) {
            printf("First repeated word: %s\n", result);
            free(result);
        } else {
            printf("No repeated words found.\n");
        }
    }
    return 0;
}
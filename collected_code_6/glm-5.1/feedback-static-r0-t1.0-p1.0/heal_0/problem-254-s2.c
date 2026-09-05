#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** find_words(const char* str, size_t* count) {
    size_t capacity = 10;
    size_t num_words = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }

    const char* p = str;
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p) {
            const char* start = p;
            while (*p && !isspace((unsigned char)*p)) {
                p++;
            }
            size_t len = p - start;
            if (len > 0 && (start[0] == 'a' || start[0] == 'e' || start[0] == 'A' || start[0] == 'E')) {
                if (num_words >= capacity) {
                    capacity *= 2;
                    char** temp = realloc(result, capacity * sizeof(char*));
                    if (temp == NULL) {
                        for (size_t i = 0; i < num_words; i++) {
                            free(result[i]);
                        }
                        free(result);
                        *count = 0;
                        return NULL;
                    }
                    result = temp;
                }
                result[num_words] = malloc(len + 1);
                if (result[num_words] == NULL) {
                    for (size_t i = 0; i < num_words; i++) {
                        free(result[i]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
                memcpy(result[num_words], start, len);
                result[num_words][len] = '\0';
                num_words++;
            }
        }
    }

    *count = num_words;
    return result;
}

void free_words(char** words, size_t count) {
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char* text = "Apple banana elephant dog Eagle cat antenna";
    size_t count = 0;
    char** words = find_words(text, &count);

    if (words != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, count);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char **find_words(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    size_t capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        while (i < len && !isalpha((unsigned char)str[i])) {
            i++;
        }

        if (i < len) {
            char start = tolower((unsigned char)str[i]);
            if (start == 'a' || start == 'e') {
                size_t word_start = i;
                while (i < len && isalpha((unsigned char)str[i])) {
                    i++;
                }
                size_t word_len = i - word_start;
                
                char *word = malloc(word_len + 1);
                if (word == NULL) {
                    for (size_t j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }

                memcpy(word, str + word_start, word_len);
                word[word_len] = '\0';

                if (*count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(result, capacity * sizeof(char *));
                    if (temp == NULL) {
                        free(word);
                        for (size_t j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        *count = 0;
                        return NULL;
                    }
                    result = temp;
                }

                result[*count] = word;
                (*count)++;
            } else {
                while (i < len && isalpha((unsigned char)str[i])) {
                    i++;
                }
            }
        }
    }

    return result;
}

int main(void) {
    const char *text = "Apple and elephant are amazing and elegant animals.";
    size_t count = 0;
    char **words = find_words(text, &count);

    if (words != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
        free(words);
    }

    return 0;
}
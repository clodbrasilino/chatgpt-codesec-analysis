#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words_starting_with_ae(const char *str, int *count) {
    *count = 0;
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err = memcpy_s(buffer, len + 1, str, len + 1);
    if (err != 0) {
        free(buffer);
        return NULL;
    }

    int capacity = 10;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        free(buffer);
        return NULL;
    }

    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        if (tolower((unsigned char)token[0]) == 'a' || tolower((unsigned char)token[0]) == 'e') {
            if (*count >= capacity) {
                capacity *= 2;
                char **new_result = (char **)realloc(result, capacity * sizeof(char *));
                if (new_result == NULL) {
                    for (int i = 0; i < *count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    free(buffer);
                    return NULL;
                }
                result = new_result;
            }

            size_t token_len = strnlen(token, len + 1) + 1;
            result[*count] = (char *)malloc(token_len);
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                free(buffer);
                return NULL;
            }
            
            errno_t token_err = memcpy_s(result[*count], token_len, token, token_len);
            if (token_err != 0) {
                free(result[*count]);
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                free(buffer);
                return NULL;
            }
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    free(buffer);
    return result;
}

/* Possible weaknesses found:
 *  'memcpy' declared here
 */
void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *text = "An elephant is always exploring every area.";
    int count = 0;

    char **words = find_words_starting_with_ae(text, &count);

    if (words != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, count);
    }

    return 0;
}
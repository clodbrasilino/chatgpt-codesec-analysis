#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* str, size_t* count) {
    *count = 0;
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char** result = malloc(sizeof(char*));
        if (result == NULL) {
            return NULL;
        }
        result[0] = calloc(1, sizeof(char));
        if (result[0] == NULL) {
            free(result);
            return NULL;
        }
        return result;
    }

    size_t capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    const char* start = str;
    for (const char* p = str; ; p++) {
        if (*p == '\0' || (isupper((unsigned char)*p) && p != str)) {
            size_t token_len = p - start;
            char* token = malloc(token_len + 1);
            if (token == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            memcpy(token, start, token_len);
            token[token_len] = '\0';

            if (*count >= capacity) {
                capacity *= 2;
                char** new_result = realloc(result, capacity * sizeof(char*));
                if (new_result == NULL) {
                    free(token);
                    for (size_t i = 0; i < *count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                result = new_result;
            }

            result[*count] = token;
            (*count)++;

            if (*p == '\0') {
                break;
            }
            start = p;
        }
    }

    char** final_result = realloc(result, (*count) * sizeof(char*));
    if (final_result != NULL) {
        result = final_result;
    }

    return result;
}

void free_split_result(char** result, size_t count) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;

    char** result = split_at_uppercase(input, &count);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }

    free_split_result(result, count);

    return EXIT_SUCCESS;
}
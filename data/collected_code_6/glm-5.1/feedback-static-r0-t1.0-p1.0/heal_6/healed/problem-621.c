#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* increment_string(const char* str, int k) {
    if (str == NULL) {
        char* res = malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    size_t capacity = len + 1;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            long num = 0;

            while (i < len && isdigit((unsigned char)str[i])) {
                num = num * 10 + (str[i] - '0');
                if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10)) {
                    while (i < len && isdigit((unsigned char)str[i])) {
                        if (j + 2 > capacity) {
                            size_t new_capacity = capacity * 2;
                            char* new_result = realloc(result, new_capacity);
                            if (new_result == NULL) { free(result); return NULL; }
                            result = new_result;
                            capacity = new_capacity;
                        }
                        result[j++] = str[i++];
                    }
                    goto next_char;
                }
                i++;
            }

            num += k;

            int written = snprintf(NULL, 0, "%ld", num);
            if (written <= 0) {
                free(result);
                return NULL;
            }

            if (j + written + 1 > capacity) {
                size_t new_capacity = (j + written + 1) * 2;
                char* new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                capacity = new_capacity;
            }

            snprintf(result + j, written + 1, "%ld", num);
            j += written;
        } else {
            if (j + 2 > capacity) {
                size_t new_capacity = capacity * 2;
                char* new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                capacity = new_capacity;
            }

            result[j++] = str[i++];
        }
        next_char:;
    }

    result[j] = '\0';
    
    if (j + 1 < capacity) {
        char* trimmed = realloc(result, j + 1);
        if (trimmed != NULL) {
            result = trimmed;
        }
    }

    return result;
}

int main(void) {
    char* s1 = increment_string("abc123def45", 5);
    if (s1 != NULL) {
        printf("%s\n", s1);
        free(s1);
    }

    char* s2 = increment_string("no numbers here", 10);
    if (s2 != NULL) {
        printf("%s\n", s2);
        free(s2);
    }

    char* s3 = increment_string("99 bottles", 1);
    if (s3 != NULL) {
        printf("%s\n", s3);
        free(s3);
    }

    char* s4 = increment_string(NULL, 5);
    if (s4 != NULL) {
        s4[0] = '\0';
        printf("NULL input handled: %s\n", s4);
        free(s4);
    }

    return 0;
}
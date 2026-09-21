#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* increment_string(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    size_t capacity = len + 1;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            long num = 0;
            int overflow = 0;

            while (i < len && isdigit((unsigned char)str[i])) {
                int digit = str[i] - '0';
                if (num > (LONG_MAX - digit) / 10) {
                    overflow = 1;
                    while (i < len && isdigit((unsigned char)str[i])) {
                        i++;
                    }
                    break;
                }
                num = num * 10 + digit;
                i++;
            }

            if (overflow) {
                if (j + 1 > capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity < j + 1) new_capacity = j + 1;
                    char* new_result = (char*)realloc(result, new_capacity);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }
                result[j++] = '?';
            } else {
                num += k;

                int written = snprintf(NULL, 0, "%ld", num);
                if (written <= 0) {
                    free(result);
                    return NULL;
                }

                if (j + written + 1 > capacity) {
                    size_t new_capacity = j + written + 1;
                    char* new_result = (char*)realloc(result, new_capacity);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }

                snprintf(result + j, written + 1, "%ld", num);
                j += written;
            }
        } else {
            if (j + 2 > capacity) {
                size_t new_capacity = j + 2;
                char* new_result = (char*)realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                capacity = new_capacity;
            }

            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
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
    if (s4 == NULL) {
        printf("Handled safely\n");
    } else {
        free(s4);
    }

    return 0;
}
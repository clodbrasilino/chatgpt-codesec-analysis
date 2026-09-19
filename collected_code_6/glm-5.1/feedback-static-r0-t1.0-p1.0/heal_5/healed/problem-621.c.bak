#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* increment_string(const char* str, int k) {
    if (str == NULL) {
        return strdup("");
    }

    size_t len = strlen(str);
    size_t capacity = len + 1;
    char* result = (char*)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;

            long num = 0;
            while (i < len && isdigit((unsigned char)str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }

            num += k;

            int written = snprintf(NULL, 0, "%ld", num);
            if (written <= 0) {
                free(result);
                return NULL;
            }

            size_t needed = j + written + 1;
            if (needed > capacity) {
                capacity = needed * 2;
                char* new_result = (char*)realloc(result, capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }

            j += snprintf(result + j, capacity - j, "%ld", num);
            (void)start;
        } else {
            if (j + 2 > capacity) {
                capacity = (j + 2) * 2;
                char* new_result = (char*)realloc(result, capacity);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
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
        printf("Memory allocation failed\n");
    } else {
        if (s4[0] != '\0') {
            printf("%s\n", s4);
        } else {
            printf("NULL input handled\n");
        }
        free(s4);
    }

    return 0;
}
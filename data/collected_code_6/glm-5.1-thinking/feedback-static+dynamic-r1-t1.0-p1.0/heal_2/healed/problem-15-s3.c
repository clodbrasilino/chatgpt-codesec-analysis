#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, size_t *out_count) {
    if (str == NULL || out_count == NULL) {
        return NULL;
    }

    size_t count = 0;
    const char *p = str;

    while (*p != '\0') {
        if (!islower((unsigned char)*p)) {
            count++;
            while (*p != '\0' && !islower((unsigned char)*p)) {
                p++;
            }
        } else {
            p++;
        }
    }

    if (count + 1 <= count || count + 1 > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    p = str;

    while (*p != '\0') {
        if (!islower((unsigned char)*p)) {
            const char *start = p;
            while (*p != '\0' && !islower((unsigned char)*p)) {
                p++;
            }
            size_t len = p - start;
            
            if (len + 1 <= len) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }

            result[index] = malloc(len + 1);
            if (result[index] == NULL) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }

            memcpy(result[index], start, len);
            result[index][len] = '\0';
            index++;
        } else {
            p++;
        }
    }

    result[index] = NULL;
    *out_count = count;
    return result;
}

int main(void) {
    const char *input = "HelloWorldABCdefGHI";
    size_t count = 0;
    char **parts = split_at_lowercase(input, &count);

    if (parts != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }

    return 0;
}
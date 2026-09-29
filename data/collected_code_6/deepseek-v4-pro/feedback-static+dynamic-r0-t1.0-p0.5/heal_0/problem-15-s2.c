#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int len = strlen(str);
    int capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int segment_start = 0;
    int segment_count = 0;
    int i;

    for (i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            int segment_len = i - segment_start;
            if (segment_len > 0) {
                char *segment = malloc((segment_len + 1) * sizeof(char));
                if (segment == NULL) {
                    for (int j = 0; j < segment_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                strncpy(segment, str + segment_start, segment_len);
                segment[segment_len] = '\0';

                if (segment_count >= capacity) {
                    capacity *= 2;
                    char **new_result = realloc(result, capacity * sizeof(char *));
                    if (new_result == NULL) {
                        free(segment);
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }

                result[segment_count++] = segment;
            }
            segment_start = i + 1;
        }
    }

    if (segment_count == 0) {
        free(result);
        *count = 0;
        return NULL;
    }

    *count = segment_count;
    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_lowercase(test_string, &count);

    if (parts != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("No segments found or error occurred\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, int *count) {
    if (count == NULL) {
        return NULL;
    }

    *count = 0;

    if (str == NULL) {
        return NULL;
    }

    int len = strlen(str);
    int capacity = 4;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int segment_start = 0;
    int num_segments = 0;

    for (int i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            int segment_len = i - segment_start;
            if (segment_len > 0) {
                if (num_segments >= capacity) {
                    capacity *= 2;
                    char **temp = (char **)realloc(result, capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < num_segments; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }

                result[num_segments] = (char *)malloc((segment_len + 1) * sizeof(char));
                if (result[num_segments] == NULL) {
                    for (int j = 0; j < num_segments; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                strncpy(result[num_segments], str + segment_start, segment_len);
                result[num_segments][segment_len] = '\0';
                num_segments++;
            }
            segment_start = i + 1;
        }
    }

    *count = num_segments;
    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;

    char **segments = split_at_lowercase(test_string, &count);

    printf("Original string: %s\n", test_string);
    printf("Number of segments: %d\n", count);

    for (int i = 0; i < count; i++) {
        printf("Segment %d: %s\n", i, segments[i]);
        free(segments[i]);
    }

    free(segments);

    return 0;
}
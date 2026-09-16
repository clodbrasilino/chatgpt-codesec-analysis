#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *input, size_t *count)
{
    size_t len;
    size_t capacity = 8;
    size_t num = 0;
    size_t start = 0;
    size_t i;
    char **result;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    len = strlen(input);

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        if (i == len || (i > 0 && isupper((unsigned char)input[i]))) {
            size_t seglen = i - start;
            char *segment;

            if (seglen == 0) {
                start = i;
                continue;
            }

            segment = malloc(seglen + 1);
            if (segment == NULL) {
                size_t j;
                for (j = 0; j < num; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            memcpy(segment, input + start, seglen);
            segment[seglen] = '\0';

            if (num >= capacity) {
                size_t new_capacity = capacity * 2;
                char **tmp = realloc(result, new_capacity * sizeof(char *));
                if (tmp == NULL) {
                    size_t j;
                    free(segment);
                    for (j = 0; j < num; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                result = tmp;
                capacity = new_capacity;
            }

            result[num] = segment;
            num++;
            start = i;
        }
    }

    *count = num;
    return result;
}

void free_split(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int main(void)
{
    const char *text = "helloWorldThisIsATest";
    size_t count = 0;
    size_t i;
    char **parts;

    parts = split_at_uppercase(text, &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", parts[i]) < 0) {
            free_split(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);
    return EXIT_SUCCESS;
}
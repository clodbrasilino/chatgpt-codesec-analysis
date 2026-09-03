#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    char **result = NULL;
    int capacity = 0;
    int size = 0;
    const char *cursor = input;
    int status;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    *count = 0;
    result = malloc(sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    capacity = 1;

    while (*cursor != '\0') {
        const char *start = cursor;
        const char *end = NULL;

        if (regexec(&regex, cursor, 2, matches, 0) == 0) {
            if (matches[0].rm_so == 0) {
                cursor++;
                while (*cursor != '\0') {
                    if (regexec(&regex, cursor, 2, matches, 0) == 0) {
                        if (matches[0].rm_so == 0) {
                            cursor++;
                        } else {
                            end = cursor + matches[0].rm_so;
                            break;
                        }
                    } else {
                        end = cursor + strlen(cursor);
                        break;
                    }
                }
                if (*cursor == '\0') {
                    end = cursor;
                }
            } else {
                end = cursor + matches[0].rm_so;
            }
        } else {
            end = cursor + strlen(cursor);
        }

        if (end > start) {
            size_t len = end - start;
            char *segment = malloc(len + 1);
            if (segment == NULL) {
                for (int i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            strncpy(segment, start, len);
            segment[len] = '\0';

            if (size >= capacity) {
                char **temp = realloc(result, capacity * 2 * sizeof(char *));
                if (temp == NULL) {
                    free(segment);
                    for (int i = 0; i < size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                capacity *= 2;
            }
            result[size++] = segment;
        }

        if (end > cursor) {
            cursor = end;
        } else {
            cursor++;
        }
    }

    *count = size;
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "helloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}
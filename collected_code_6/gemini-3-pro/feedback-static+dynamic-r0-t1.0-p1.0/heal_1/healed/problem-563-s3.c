#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_quoted_strings(const char* input_string, int* count) {
    if (input_string == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    int capacity = 10;
    char** result = (char**)malloc(capacity * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    const char* p = input_string;
    while (*p != '\0') {
        if (*p == '"') {
            p++;
            const char* start = p;
            while (*p != '\0' && *p != '"') {
                p++;
            }

            if (*p == '"') {
                size_t len = p - start;
                char* extracted = (char*)malloc((len + 1) * sizeof(char));
                if (extracted == NULL) {
                    for (int i = 0; i < *count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }

                memcpy(extracted, start, len);
                extracted[len] = '\0';

                if (*count >= capacity) {
                    capacity *= 2;
                    char** temp = (char**)realloc(result, capacity * sizeof(char*));
                    if (temp == NULL) {
                        free(extracted);
                        for (int i = 0; i < *count; i++) {
                            free(result[i]);
                        }
                        free(result);
                        *count = 0;
                        return NULL;
                    }
                    result = temp;
                }

                result[*count] = extracted;
                (*count)++;
            } else {
                break;
            }
        }
        if (*p != '\0') {
            p++;
        }
    }

    return result;
}

int main(void) {
    const char* str = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    int count = 0;

    char** extracted_strings = extract_quoted_strings(str, &count);

    if (extracted_strings != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", extracted_strings[i]);
            free(extracted_strings[i]);
        }
        free(extracted_strings);
    } else {
        printf("Failed to extract strings or no strings found.\n");
    }

    return 0;
}
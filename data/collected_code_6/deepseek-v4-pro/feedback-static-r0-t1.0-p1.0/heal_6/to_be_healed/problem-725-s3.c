#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LENGTH 1024

char** extract_quoted_strings(const char* input, int* match_count) {
    regex_t regex;
    regmatch_t matches[2];
    char** results = NULL;
    int count = 0;
    const char* cursor;
    int status;

    if (input == NULL || match_count == NULL) {
        if (match_count != NULL) {
            *match_count = 0;
        }
        return NULL;
    }

    *match_count = 0;
    cursor = input;

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    results = malloc(sizeof(char*) * MAX_MATCHES);
    if (results == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (count < MAX_MATCHES) {
        status = regexec(&regex, cursor, 2, matches, 0);
        if (status != 0) {
            break;
        }

        int length = matches[1].rm_eo - matches[1].rm_so;
        if (length < 0) {
            length = 0;
        }
        if (length >= MAX_MATCH_LENGTH) {
            length = MAX_MATCH_LENGTH - 1;
        }

        size_t alloc_size = (size_t)length + 1;
        if (alloc_size > MAX_MATCH_LENGTH) {
            alloc_size = MAX_MATCH_LENGTH;
        }

        results[count] = malloc(alloc_size);
        if (results[count] == NULL) {
            for (int i = 0; i < count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            return NULL;
        }

        if (length > 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t cursor_len = strlen(cursor);
            size_t src_offset = (size_t)(matches[1].rm_so);
            
            if (src_offset >= cursor_len) {
                results[count][0] = '\0';
            } else {
                size_t src_avail = cursor_len - src_offset;
                size_t copy_len = (size_t)length;
                if (copy_len > src_avail) {
                    copy_len = src_avail;
                }
                if (copy_len >= alloc_size) {
                    copy_len = alloc_size - 1;
                }
                if (copy_len > 0) {
                    const char* src = cursor + src_offset;
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(results[count], src, copy_len);
                }
                results[count][copy_len] = '\0';
            }
        } else {
            results[count][0] = '\0';
        }

        count++;

        cursor += matches[0].rm_eo;

        if (matches[0].rm_so == matches[0].rm_eo) {
            if (*cursor != '\0') {
                cursor++;
            } else {
                break;
            }
        }

        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (count == 0) {
        free(results);
        return NULL;
    }

    *match_count = count;
    return results;
}

void free_extracted_strings(char** strings, int count) {
    if (strings == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }

    free(strings);
}

int main() {
    const char* test_string = "This is \"first\" and \"second\" and \"third\"";
    int count = 0;
    char** extracted = extract_quoted_strings(test_string, &count);

    if (extracted != NULL) {
        printf("Found %d quoted strings:\n", count);
        for (int i = 0; i < count; i++) {
            printf("[%d]: %s\n", i, extracted[i]);
        }
        free_extracted_strings(extracted, count);
    } else {
        printf("No matches found or error occurred.\n");
    }

    return 0;
}
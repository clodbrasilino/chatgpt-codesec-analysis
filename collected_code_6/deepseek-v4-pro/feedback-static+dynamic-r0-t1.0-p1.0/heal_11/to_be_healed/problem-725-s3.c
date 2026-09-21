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
        return NULL;
    }

    *match_count = 0;

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    results = malloc(sizeof(char*) * MAX_MATCHES);
    if (results == NULL) {
        regfree(&regex);
        return NULL;
    }

    for (int i = 0; i < MAX_MATCHES; i++) {
        results[i] = NULL;
    }

    cursor = input;

    while (count < MAX_MATCHES) {
        status = regexec(&regex, cursor, 2, matches, 0);
        if (status != 0) {
            break;
        }

        int length = matches[1].rm_eo - matches[1].rm_so;
        if (length < 0) {
            break;
        }

        size_t copy_length = (size_t)length;

        if (copy_length > MAX_MATCH_LENGTH - 1) {
            copy_length = MAX_MATCH_LENGTH - 1;
        }

        const char* src = cursor + matches[1].rm_so;
        size_t src_len = strnlen(src, copy_length);
        if (src_len < copy_length) {
            copy_length = src_len;
        }

        results[count] = malloc(sizeof(char) * (copy_length + 1));
        if (results[count] == NULL) {
            for (int i = 0; i < count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            return NULL;
        }

        if (copy_length > 0) {
            char* dest = results[count];
            /* Possible weaknesses found:
             *  available is assigned 'copy_length+1' here.
             */
            size_t available = copy_length + 1;
            /* Possible weaknesses found:
             *  Condition 'copy_length<available' is always true [knownConditionTrueFalse]
             *  Condition 'copy_length<available' is always true
             */
            if (copy_length < available) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, src, copy_length);
            }
        }
        results[count][copy_length] = '\0';

        count++;

        cursor += matches[0].rm_eo;

        if (matches[0].rm_so == matches[0].rm_eo) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
        }

        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    *match_count = count;

    if (count == 0) {
        free(results);
        return NULL;
    }

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
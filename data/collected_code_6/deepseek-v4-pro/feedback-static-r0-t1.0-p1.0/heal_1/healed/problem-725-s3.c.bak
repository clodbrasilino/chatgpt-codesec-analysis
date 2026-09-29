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
    const char* cursor = input;
    int status;

    if (input == NULL || match_count == NULL) {
        if (match_count != NULL) {
            *match_count = 0;
        }
        return NULL;
    }

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        *match_count = 0;
        return NULL;
    }

    results = malloc(sizeof(char*) * MAX_MATCHES);
    if (results == NULL) {
        regfree(&regex);
        *match_count = 0;
        return NULL;
    }

    while (count < MAX_MATCHES) {
        status = regexec(&regex, cursor, 2, matches, 0);
        if (status != 0) {
            break;
        }

        int length = matches[1].rm_eo - matches[1].rm_so;
        if (length >= MAX_MATCH_LENGTH) {
            length = MAX_MATCH_LENGTH - 1;
        }

        results[count] = malloc(sizeof(char) * (length + 1));
        if (results[count] == NULL) {
            for (int i = 0; i < count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *match_count = 0;
            return NULL;
        }

        strncpy(results[count], cursor + matches[1].rm_so, length);
        results[count][length] = '\0';
        count++;

        cursor += matches[0].rm_eo;

        if (matches[0].rm_so == matches[0].rm_eo) {
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

int main(void) {
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
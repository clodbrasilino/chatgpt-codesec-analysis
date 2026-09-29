#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t match[1];
    char *string = strdup(input);
    int len = strlen(string), offset = 0, start = 0, match_count = 0;
    char **result = NULL;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE)) {
        free(string);
        return NULL;
    }

    while (regexec(&regex, string + offset, 1, match, 0) == 0) {
        if (match[0].rm_so > 0 && (start + match[0].rm_so) > start) {
            /* Possible weaknesses found:
             *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
             */
            result = realloc(result, sizeof(char*) * (match_count + 1));
            /* Possible weaknesses found:
             *  Assuming that condition '!result' is not redundant
             */
            if (!result) {
                for (int i = 0; i < match_count; i++) {
                    /* Possible weaknesses found:
                     *  Null pointer dereference
                     *  Either the condition '!result' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
                     */
                    free(result[i]);
                }
                free(result);
                free(string);
                regfree(&regex);
                return NULL;
            }
            result[match_count] = strndup(string + start, (start + match[0].rm_so) - start);
            if (!result[match_count]) {
                for (int i = 0; i < match_count; i++) {
                    free(result[i]);
                }
                free(result);
                free(string);
                regfree(&regex);
                return NULL;
            }
            match_count++;
        }
        start += match[0].rm_eo;
        offset += match[0].rm_eo;
    }

    if (len - start > 0) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = realloc(result, sizeof(char*) * (match_count + 1));
        /* Possible weaknesses found:
         *  Assuming that condition '!result' is not redundant
         */
        if (!result) {
            for (int i = 0; i < match_count; i++) {
                /* Possible weaknesses found:
                 *  Null pointer dereference
                 *  Either the condition '!result' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
                 */
                free(result[i]);
            }
            free(result);
            free(string);
            regfree(&regex);
            return NULL;
        }
        result[match_count] = strndup(string + start, len - start);
        if (!result[match_count]) {
            for (int i = 0; i < match_count; i++) {
                free(result[i]);
            }
            free(result);
            free(string);
            regfree(&regex);
            return NULL;
        }
        match_count++;
    }

    *count = match_count;
    free(string);
    regfree(&regex);
    return result;
}

void free_array(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    const char *input = "Hello, world! This is a test. Yes, it is.";
    const char *delimiters = "[,!. ]+";
    int count = 0;
    char **result = split_string(input, delimiters, &count);

    if (result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_array(result, count);
    } else {
        printf("Failed to split the string.\n");
    }

    return 0;
}
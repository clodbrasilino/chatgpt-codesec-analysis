#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  */

char** extract_substrings(const char** strings, size_t count, size_t n) {
    if (strings == NULL || count == 0 || n == 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t actual_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            for (size_t j = 0; j < actual_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(strings[i]);
        size_t extract_len = len < n ? len : n;

        if (len >= n) {
            result[actual_count] = (char*)malloc((extract_len + 1) * sizeof(char));
            if (result[actual_count] == NULL) {
                for (size_t j = 0; j < actual_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[actual_count], strings[i], extract_len);
            result[actual_count][extract_len] = '\0';
            actual_count++;
        }
    }

    result[actual_count] = NULL;
    char** temp = (char**)realloc(result, (actual_count + 1) * sizeof(char*));
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    size_t count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    size_t extract_size = 8;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return EXIT_SUCCESS;
}
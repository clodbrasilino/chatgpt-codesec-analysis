#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_element_concatenation(const char** tuple, size_t count, size_t* out_count) {
    if (tuple == NULL || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    if (count < 2) {
        *out_count = 0;
        return NULL;
    }

    size_t result_count = count - 1;
    char** result = (char**)malloc(result_count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < result_count; i++) {
        const char* str1 = tuple[i] != NULL ? tuple[i] : "";
        const char* str2 = tuple[i + 1] != NULL ? tuple[i + 1] : "";

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(str1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(str2);
        size_t total_len = len1 + len2;

        result[i] = (char*)malloc(total_len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_count = 0;
            return NULL;
        }

        snprintf(result[i], total_len + 1, "%s%s", str1, str2);
    }

    *out_count = result_count;
    return result;
}

void free_result(char** arr, size_t count) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main(void) {
    const char* test_tuple[] = {"G", "F", "G", "I", "S", "B", "E", "S", "T"};
    size_t test_count = sizeof(test_tuple) / sizeof(test_tuple[0]);
    size_t out_count = 0;

    char** result = adjacent_element_concatenation(test_tuple, test_count, &out_count);

    if (result != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s ", result[i]);
        }
        printf("\n");
        free_result(result, out_count);
    }

    return 0;
}
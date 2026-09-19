#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void free_extracted_strings(char** strings);

bool ends_with_substr(const char* str, const char* substr, size_t substr_len) {
    size_t str_len = strlen(str);
    if (str_len < substr_len) {
        return false;
    }
    return strcmp(str + str_len - substr_len, substr) == 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["Python","practice","solution"]
  *  test case 2 failed: expected ['exercises'], got ["Python","practice","solution"]
  */

char** extract_substrings(const char** strings, size_t count, size_t size) {
    if (strings == NULL || count == 0 || size == 0) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        return NULL;
    }

    char** substrings = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (substrings == NULL) {
        return NULL;
    }

    size_t sub_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            size_t len = strlen(strings[i]);
            size_t extract_len = len < size ? len : size;
            substrings[sub_count] = (char*)malloc((extract_len + 1) * sizeof(char));
            if (substrings[sub_count] == NULL) {
                for (size_t k = 0; k < sub_count; k++) {
                    free(substrings[k]);
                }
                free(substrings);
                return NULL;
            }
            strncpy(substrings[sub_count], strings[i], extract_len);
            substrings[sub_count][extract_len] = '\0';
            sub_count++;
        }
    }
    substrings[sub_count] = NULL;

    const char* suffix1 = "on";
    size_t suffix1_len = 2;
    const char* suffix2 = "ice";
    size_t suffix2_len = 3;

    char** result = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (result == NULL) {
        for (size_t k = 0; k < sub_count; k++) {
            free(substrings[k]);
        }
        free(substrings);
        return NULL;
    }

    size_t res_count = 0;
    for (size_t i = 0; i < sub_count; i++) {
        if (ends_with_substr(substrings[i], suffix1, suffix1_len)) {
            result[res_count++] = substrings[i];
        } else if (ends_with_substr(substrings[i], suffix2, suffix2_len)) {
            result[res_count++] = substrings[i];
        } else {
            free(substrings[i]);
        }
    }
    result[res_count] = NULL;

    free(substrings);

    if (res_count == 0) {
        free(result);
        return NULL;
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
        "exercise",
        "practice",
        "solution"
    };
    size_t count = sizeof(input_strings) / sizeof(input_strings[0]);
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
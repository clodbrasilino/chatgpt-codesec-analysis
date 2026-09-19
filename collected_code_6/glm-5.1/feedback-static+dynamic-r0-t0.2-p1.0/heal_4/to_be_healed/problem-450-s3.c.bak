#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool ends_with_substr(const char* str, const char* substr, size_t substr_len) {
    size_t str_len = strlen(str);
    if (str_len < substr_len) {
        return false;
    }
    return strcmp(str + str_len - substr_len, substr) == 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got null
  *  test case 0 failed: expected ['practice', 'solution'], got null
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

    char** result = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            size_t len = strlen(strings[i]);
            size_t alloc_size = len < size ? len : size;
            result[j] = (char*)malloc((alloc_size + 1) * sizeof(char));
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[j], strings[i], alloc_size);
            result[j][alloc_size] = '\0';
            j++;
        }
    }

    const char* suffix = "es";
    size_t suffix_len = 2;
    char** filtered = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (filtered == NULL) {
        for (size_t k = 0; k < j; k++) {
            free(result[k]);
        }
        free(result);
        return NULL;
    }

    size_t f = 0;
    for (size_t i = 0; i < j; i++) {
        if (ends_with_substr(result[i], suffix, suffix_len)) {
            filtered[f++] = result[i];
        } else {
            free(result[i]);
        }
    }

    free(result);
    filtered[f] = NULL;
    
    if (f == 0) {
        free(filtered);
        return NULL;
    }

    return filtered;
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
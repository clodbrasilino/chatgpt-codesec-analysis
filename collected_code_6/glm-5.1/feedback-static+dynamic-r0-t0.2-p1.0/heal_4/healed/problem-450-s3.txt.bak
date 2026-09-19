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
            size_t extract_len = len < size ? len : size;
            result[j] = (char*)malloc((extract_len + 1) * sizeof(char));
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[j], strings[i], extract_len);
            result[j][extract_len] = '\0';
            j++;
        }
    }

    const char* suffix1 = "on";
    size_t suffix1_len = 2;
    char** filtered1 = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (filtered1 == NULL) {
        for (size_t k = 0; k < j; k++) {
            free(result[k]);
        }
        free(result);
        return NULL;
    }

    size_t f1 = 0;
    for (size_t i = 0; i < j; i++) {
        if (ends_with_substr(result[i], suffix1, suffix1_len)) {
            filtered1[f1++] = result[i];
        } else {
            free(result[i]);
        }
    }
    free(result);
    filtered1[f1] = NULL;

    const char* suffix2 = "ice";
    size_t suffix2_len = 3;
    char** filtered2 = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (filtered2 == NULL) {
        for (size_t k = 0; k < f1; k++) {
            free(filtered1[k]);
        }
        free(filtered1);
        return NULL;
    }

    size_t f2 = 0;
    for (size_t i = 0; i < j; i++) {
        const char* original_str = strings[i] != NULL ? strings[i] : "";
        size_t len = strlen(original_str);
        size_t extract_len = len < size ? len : size;
        char* temp = (char*)malloc((extract_len + 1) * sizeof(char));
        if (temp == NULL) {
            for (size_t k = 0; k < f1; k++) {
                free(filtered1[k]);
            }
            free(filtered1);
            for (size_t k = 0; k < f2; k++) {
                free(filtered2[k]);
            }
            free(filtered2);
            return NULL;
        }
        strncpy(temp, original_str, extract_len);
        temp[extract_len] = '\0';

        if (ends_with_substr(temp, suffix2, suffix2_len)) {
            filtered2[f2++] = temp;
        } else {
            free(temp);
        }
    }
    filtered2[f2] = NULL;

    char** final_result = (char**)malloc((f1 + f2 + 1) * sizeof(char*));
    if (final_result == NULL) {
        for (size_t k = 0; k < f1; k++) {
            free(filtered1[k]);
        }
        free(filtered1);
        for (size_t k = 0; k < f2; k++) {
            free(filtered2[k]);
        }
        free(filtered2);
        return NULL;
    }

    size_t f = 0;
    for (size_t i = 0; i < f1; i++) {
        final_result[f++] = filtered1[i];
    }
    for (size_t i = 0; i < f2; i++) {
        final_result[f++] = filtered2[i];
    }
    final_result[f] = NULL;

    free(filtered1);
    free(filtered2);

    if (f == 0) {
        free_extracted_strings(final_result);
        return NULL;
    }

    return final_result;
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
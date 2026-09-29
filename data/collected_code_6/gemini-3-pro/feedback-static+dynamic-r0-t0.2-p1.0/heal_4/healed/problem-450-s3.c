#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int check_target_length(const char* str, size_t target_length) {
    size_t len = 0;
    while (len <= target_length && str[len] != '\0') {
        len++;
    }
    return len == target_length;
}

static char* safe_strdup(const char* str, size_t length) {
    char* copy = (char*)malloc(length + 1);
    if (copy != NULL) {
        strncpy(copy, str, length);
        copy[length] = '\0';
    }
    return copy;
}

char** extract_strings(char** input_list, int list_size, size_t target_length, int* out_size) {
    if (input_list == NULL || out_size == NULL || list_size < 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        if (input_list[i] != NULL && check_target_length(input_list[i], target_length)) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < list_size; i++) {
        if (input_list[i] != NULL && check_target_length(input_list[i], target_length)) {
            result[index] = safe_strdup(input_list[i], target_length);
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                *out_size = 0;
                return NULL;
            }
            index++;
        }
    }

    *out_size = count;
    return result;
}

int main(void) {
    char* input_strings[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "bat",
        "exercises",
        "practice",
        "solution",
        "Python"
    };
    int list_size = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t target_length = 8;
    int extracted_size = 0;

    char** extracted = extract_strings(input_strings, list_size, target_length, &extracted_size);

    if (extracted != NULL) {
        for (int i = 0; i < extracted_size; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    return 0;
}
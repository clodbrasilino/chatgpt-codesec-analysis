#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size <= 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int valid_count = 0;

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strlen(strings[i]);
        if (len < (size_t)size) {
            continue;
        }

        result[valid_count] = (char*)malloc(size + 1);
        if (result[valid_count] == NULL) {
            for (int j = 0; j < valid_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        memcpy(result[valid_count], strings[i], size);
        result[valid_count][size] = '\0';
        valid_count++;
    }

    result[valid_count] = NULL;

    char** shrunk_result = (char**)realloc(result, (valid_count + 1) * sizeof(char*));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char* input_strings_0[] = {"Python", "list", "exercise", "practice", "solution", NULL};
    char* input_strings_1[] = {"Python", "list", "exerci", "practi", "soluti", NULL};
    char* input_strings_2[] = {"Python", "list", "exercises", "practice", "solution", NULL};

    int count_0 = 5, size_0 = 8;
    int count_1 = 5, size_1 = 8;
    int count_2 = 5, size_2 = 9;

    char** extracted_0 = extract_substrings(input_strings_0, count_0, size_0);
    if (extracted_0 != NULL) {
        for (int i = 0; extracted_0[i] != NULL; i++) {
            printf("%s\n", extracted_0[i]);
        }
        free_extracted_strings(extracted_0);
    }

    printf("---\n");

    char** extracted_1 = extract_substrings(input_strings_1, count_1, size_1);
    if (extracted_1 != NULL) {
        for (int i = 0; extracted_1[i] != NULL; i++) {
            printf("%s\n", extracted_1[i]);
        }
        free_extracted_strings(extracted_1);
    }

    printf("---\n");

    char** extracted_2 = extract_substrings(input_strings_2, count_2, size_2);
    if (extracted_2 != NULL) {
        for (int i = 0; extracted_2[i] != NULL; i++) {
            printf("%s\n", extracted_2[i]);
        }
        free_extracted_strings(extracted_2);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  */

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size < 0) {
        return NULL;
    }

    int result_count = 0;
    int* valid_indices = (int*)malloc(count * sizeof(int));
    if (valid_indices == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= (size_t)size) {
            valid_indices[result_count++] = i;
        }
    }

    if (result_count == 0) {
        free(valid_indices);
        char** empty_result = (char**)malloc(sizeof(char*));
        if (empty_result) {
            empty_result[0] = NULL;
        }
        return empty_result;
    }

    char** result = (char**)malloc((result_count + 1) * sizeof(char*));
    if (result == NULL) {
        free(valid_indices);
        return NULL;
    }

    for (int i = 0; i < result_count; i++) {
        int idx = valid_indices[i];
        result[i] = (char*)malloc(size + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(valid_indices);
            return NULL;
        }
        strncpy(result[i], strings[idx], size);
        result[i][size] = '\0';
    }

    result[result_count] = NULL;
    free(valid_indices);
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
    char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    int count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    int extract_size = 8;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  */

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size <= 0) {
        return NULL;
    }

    int match_count = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            size_t len = 0;
            while (strings[i][len] != '\0') {
                len++;
            }
            if (len >= (size_t)size) {
                match_count++;
            }
        }
    }

    char** result = (char**)malloc((match_count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int res_idx = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = 0;
        while (strings[i][len] != '\0') {
            len++;
        }
        if (len < (size_t)size) {
            continue;
        }

        result[res_idx] = (char*)malloc((size_t)size + 1);
        if (result[res_idx] == NULL) {
            for (int j = 0; j < res_idx; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        for (int k = 0; k < size; k++) {
            result[res_idx][k] = strings[i][k];
        }
        result[res_idx][size] = '\0';
        res_idx++;
    }

    result[res_idx] = NULL;
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
        return 1;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return 0;
}
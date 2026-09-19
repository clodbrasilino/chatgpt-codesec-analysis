#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got ["Python","list","exercises","practice","solution"]
  *  test case 0 failed: expected ['practice', 'solution'], got ["Python","list","exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","list","exerci","practi","soluti"]
  */

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size <= 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int actual_count = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strlen(strings[i]);
        size_t extract_len = (size_t)size < len ? (size_t)size : len;

        result[actual_count] = (char*)malloc(extract_len + 1);
        if (result[actual_count] == NULL) {
            for (int j = 0; j < actual_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        strncpy(result[actual_count], strings[i], extract_len);
        result[actual_count][extract_len] = '\0';
        actual_count++;
    }

    result[actual_count] = NULL;
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

    int extract_size = 9;
    char** extracted = extract_substrings(input_strings, count, extract_size);

    if (extracted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return 0;
}
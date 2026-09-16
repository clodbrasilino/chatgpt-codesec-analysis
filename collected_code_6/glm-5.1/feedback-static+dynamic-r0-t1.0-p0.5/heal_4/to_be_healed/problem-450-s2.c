#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  */

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size < 0) {
        return NULL;
    }

    if (size == 0) {
        char** result = (char**)malloc(1 * sizeof(char*));
        if (result == NULL) {
            return NULL;
        }
        result[0] = NULL;
        return result;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int result_count = 0;

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strlen(strings[i]);
        
        if (len >= (size_t)size) {
            size_t extract_len = (size_t)size;
            result[result_count] = (char*)malloc(extract_len + 1);
            if (result[result_count] == NULL) {
                for (int j = 0; j < result_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[result_count], strings[i], extract_len);
            result[result_count][extract_len] = '\0';
            result_count++;
        }
    }

    result[result_count] = NULL;
    
    char** trimmed_result = (char**)realloc(result, (result_count + 1) * sizeof(char*));
    if (trimmed_result != NULL) {
        result = trimmed_result;
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
    char* input_strings_0[] = {"exercises", "practice", "solution", NULL};
    int count_0 = 3;
    int size_0 = 7;
    char** extracted_0 = extract_substrings(input_strings_0, count_0, size_0);
    if (extracted_0 != NULL) {
        for (int i = 0; extracted_0[i] != NULL; i++) {
            printf("%s\n", extracted_0[i]);
        }
        free_extracted_strings(extracted_0);
    }
    printf("---\n");

    char* input_strings_1[] = {"Python", "exercises", "practice", "solution", NULL};
    int count_1 = 4;
    int size_1 = 6;
    char** extracted_1 = extract_substrings(input_strings_1, count_1, size_1);
    if (extracted_1 != NULL) {
        for (int i = 0; extracted_1[i] != NULL; i++) {
            printf("%s\n", extracted_1[i]);
        }
        free_extracted_strings(extracted_1);
    }
    printf("---\n");

    char* input_strings_2[] = {"exercises", NULL};
    int count_2 = 1;
    int size_2 = 9;
    char** extracted_2 = extract_substrings(input_strings_2, count_2, size_2);
    if (extracted_2 != NULL) {
        for (int i = 0; extracted_2[i] != NULL; i++) {
            printf("%s\n", extracted_2[i]);
        }
        free_extracted_strings(extracted_2);
    }

    return 0;
}
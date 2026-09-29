#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prefix_of_any(const char *str, size_t str_len, char **list, int list_count, int size) {
    for (int i = 0; i < list_count; i++) {
        if (list[i] == NULL) {
            continue;
        }
        size_t len = strlen(list[i]);
        if (len < (size_t)size) {
            continue;
        }
        if (strncmp(str, list[i], (size_t)size) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise","practice","solution"]
  *  test case 1 failed: expected ['Python'], got ["Python","exerci","practi","soluti"]
  */

char **extract_strings(char **input, int count, int size, int *output_count) {
    if (input == NULL || count <= 0 || size <= 0 || output_count == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    int extracted = 0;
    for (int i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strlen(input[i]);
        if (len < (size_t)size) {
            continue;
        }
        
        /* Possible weaknesses found:
         *  Variable 'substr' can be declared as pointer to const [constVariablePointer]
         */
        char *substr = input[i];
        if (is_prefix_of_any(substr, size, result, extracted, size)) {
            continue;
        }
        
        result[extracted] = (char *)malloc(((size_t)size + 1) * sizeof(char));
        if (result[extracted] == NULL) {
            for (int j = 0; j < extracted; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }
        memcpy(result[extracted], input[i], (size_t)size);
        result[extracted][size] = '\0';
        extracted++;
    }

    if (extracted == 0) {
        free(result);
        *output_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)extracted * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < extracted; j++) {
            free(result[j]);
        }
        free(result);
        *output_count = 0;
        return NULL;
    }

    *output_count = extracted;
    return final_result;
}

int main(void) {
    char *strings[] = {"Python", "exercise", "practice", "solution"};
    int count = sizeof(strings) / sizeof(strings[0]);
    int output_count = 0;
    int extract_size = 6;

    char **extracted = extract_strings(strings, count, extract_size, &output_count);

    if (extracted != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted or error occurred\n");
    }

    return 0;
}
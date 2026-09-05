#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exact_match_exists(char** strings, int count, int size, char* candidate) {
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) == (size_t)size && strcmp(strings[i], candidate) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got ["exerci","practi","soluti"]
  *  test case 0 failed: expected ['practice', 'solution'], got ["exercise"]
  *  test case 2 failed: expected ['exercises'], got []
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

        size_t str_len = strlen(strings[i]);
        
        if ((size_t)size > str_len) {
            continue;
        }

        char* temp = (char*)malloc(size + 1);
        if (temp == NULL) {
            for (int j = 0; j < actual_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        strncpy(temp, strings[i], size);
        temp[size] = '\0';

        if (str_len == (size_t)size) {
            free(temp);
        } else {
            if (exact_match_exists(strings, count, size, temp)) {
                free(temp);
            } else {
                int duplicate = 0;
                for (int j = 0; j < actual_count; j++) {
                    if (strcmp(result[j], temp) == 0) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate) {
                    free(temp);
                } else {
                    result[actual_count] = temp;
                    actual_count++;
                }
            }
        }
    }

    result[actual_count] = NULL;
    
    char** trimmed_result = (char**)realloc(result, (actual_count + 1) * sizeof(char*));
    if (trimmed_result != NULL) {
        return trimmed_result;
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
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return 0;
}
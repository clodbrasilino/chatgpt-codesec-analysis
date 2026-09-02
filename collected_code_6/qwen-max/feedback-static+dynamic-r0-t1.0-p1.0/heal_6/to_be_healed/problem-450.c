#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *source[], int count, const size_t sizes[]) {
    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) return NULL;
    
    for (int i = 0; i < count; i++) {
        result[i] = (char *)malloc(sizes[i] + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        strncpy(result[i], source[i], sizes[i]);
        result[i][sizes[i]] = '\0';
    }
    
    return result;
}

void free_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *source[] = {"practice", "solution"};
    const size_t sizes[] = {8, 9};
    int count = 2;

    char **result = extract_strings(source, count, sizes);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }

    free_strings(result, count);

    return 0;
}
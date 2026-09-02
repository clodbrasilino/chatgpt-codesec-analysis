#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char **strings, int *count, const char *remove_char) {
    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        if (strstr(strings[i], remove_char) == NULL) {
            new_count++;
        }
    }
    char **filtered_strings = (char **)malloc(new_count * sizeof(char *));
    if (filtered_strings == NULL) {
        exit(EXIT_FAILURE);
    }
    int index = 0;
    for (int i = 0; i < *count; i++) {
        if (strstr(strings[i], remove_char) == NULL) {
            filtered_strings[index] = strdup(strings[i]);
            if (filtered_strings[index] == NULL) {
                exit(EXIT_FAILURE);
            }
            index++;
        } else {
            free(strings[i]);
        }
    }
    free(strings);
    *count = new_count;
    return filtered_strings;
}

int main() {
    char *strings[] = {"hello", "world", "hell", "word", "test"};
    int count = 5;
    const char *remove_char = "l";
    
    /* Possible weaknesses found:
     *  assignment to expression with array type
     *  array type 'char *[5]' is not assignable
     */
    strings = filter_strings(strings, &count, remove_char);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    /* Possible weaknesses found:
     *  Deallocation of an auto-variable results in undefined behaviour. [autovarInvalidDeallocation]
     */
    free(strings);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

char **remove_words(char **list, size_t list_size, const char **removals, size_t removals_size, size_t *out_size) {
    if (list == NULL || removals == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL) {
            int should_remove = 0;
            for (size_t j = 0; j < removals_size; j++) {
                if (removals[j] != NULL && strcmp(list[i], removals[j]) == 0) {
                    should_remove = 1;
                    break;
                }
            }
            if (!should_remove) {
                result[count] = malloc(strlen(list[i]) + 1);
                if (result[count] == NULL) {
                    for (size_t k = 0; k < count; k++) free(result[k]);
                    free(result);
                    return NULL;
                }
                strcpy(result[count], list[i]);
                count++;
            }
        } else {
            result[count] = NULL;
            count++;
        }
    }

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *list[] = {"red", "green", "blue", "black", "white", "orange"};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    const char *removals_set0[] = {"black"};
    size_t removals_size0 = sizeof(removals_set0) / sizeof(removals_set0[0]);
    size_t out_size0 = 0;
    char **filtered0 = remove_words(list, list_size, removals_set0, removals_size0, &out_size0);
    if (filtered0 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size0; i++) {
            printf("'%s'", filtered0[i]);
            if (i < out_size0 - 1) printf(", ");
        }
        printf("]\n");
        for (size_t i = 0; i < out_size0; i++) free(filtered0[i]);
        free(filtered0);
    } else {
        printf("[]\n");
    }

    const char *removals_set1[] = {"black", "orange"};
    size_t removals_size1 = sizeof(removals_set1) / sizeof(removals_set1[0]);
    size_t out_size1 = 0;
    char **filtered1 = remove_words(list, list_size, removals_set1, removals_size1, &out_size1);
    if (filtered1 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size1; i++) {
            printf("'%s'", filtered1[i]);
            if (i < out_size1 - 1) printf(", ");
        }
        printf("]\n");
        for (size_t i = 0; i < out_size1; i++) free(filtered1[i]);
        free(filtered1);
    } else {
        printf("[]\n");
    }

    const char *removals_set2[] = {"blue", "black"};
    size_t removals_size2 = sizeof(removals_set2) / sizeof(removals_set2[0]);
    size_t out_size2 = 0;
    char **filtered2 = remove_words(list, list_size, removals_set2, removals_size2, &out_size2);
    if (filtered2 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size2; i++) {
            printf("'%s'", filtered2[i]);
            if (i < out_size2 - 1) printf(", ");
        }
        printf("]\n");
        for (size_t i = 0; i < out_size2; i++) free(filtered2[i]);
        free(filtered2);
    } else {
        printf("[]\n");
    }

    return 0;
}
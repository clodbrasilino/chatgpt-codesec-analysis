#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  */

char **remove_words(char **list, size_t list_size, char **removals, size_t removals_size, size_t *out_size) {
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
                result[count] = strdup(list[i]);
                if (result[count] == NULL) {
                    for (size_t k = 0; k < count; k++) {
                        free(result[k]);
                    }
                    free(result);
                    return NULL;
                }
                count++;
            }
        }
    }

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    } else if (count == 0) {
        free(result);
        result = NULL;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *list1[] = {"red", "green", "blue", "black", "white"};
    size_t list_size1 = sizeof(list1) / sizeof(list1[0]);
    char *removals1[] = {"white"};
    size_t removals_size1 = sizeof(removals1) / sizeof(removals1[0]);
    size_t out_size1 = 0;
    char **filtered_list1 = remove_words(list1, list_size1, removals1, removals_size1, &out_size1);
    if (filtered_list1 != NULL) {
        for (size_t i = 0; i < out_size1; i++) {
            printf("%s%s", (i > 0 ? " " : ""), filtered_list1[i]);
            free(filtered_list1[i]);
        }
        printf("\n");
        free(filtered_list1);
    } else if (out_size1 == 0) {
        printf("\n");
    }

    char *list2[] = {"red", "green", "black", "orange", "white"};
    size_t list_size2 = sizeof(list2) / sizeof(list2[0]);
    char *removals2[] = {"white"};
    size_t removals_size2 = sizeof(removals2) / sizeof(removals2[0]);
    size_t out_size2 = 0;
    char **filtered_list2 = remove_words(list2, list_size2, removals2, removals_size2, &out_size2);
    if (filtered_list2 != NULL) {
        for (size_t i = 0; i < out_size2; i++) {
            printf("%s%s", (i > 0 ? " " : ""), filtered_list2[i]);
            free(filtered_list2[i]);
        }
        printf("\n");
        free(filtered_list2);
    } else if (out_size2 == 0) {
        printf("\n");
    }

    char *list3[] = {"red", "green", "blue", "black"};
    size_t list_size3 = sizeof(list3) / sizeof(list3[0]);
    char *removals3[] = {"blue"};
    size_t removals_size3 = sizeof(removals3) / sizeof(removals3[0]);
    size_t out_size3 = 0;
    char **filtered_list3 = remove_words(list3, list_size3, removals3, removals_size3, &out_size3);
    if (filtered_list3 != NULL) {
        for (size_t i = 0; i < out_size3; i++) {
            printf("%s%s", (i > 0 ? " " : ""), filtered_list3[i]);
            free(filtered_list3[i]);
        }
        printf("\n");
        free(filtered_list3);
    } else if (out_size3 == 0) {
        printf("\n");
    }

    return 0;
}
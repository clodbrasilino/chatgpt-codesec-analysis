#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                result[count] = list[i];
                count++;
            }
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

    const char *removals1[] = {"white", "orange"};
    size_t removals_size1 = sizeof(removals1) / sizeof(removals1[0]);

    size_t out_size1 = 0;
    char **filtered_list1 = remove_words(list, list_size, removals1, removals_size1, &out_size1);
    if (filtered_list1 != NULL) {
        for (size_t i = 0; i < out_size1; i++) {
            printf("%s ", filtered_list1[i]);
        }
        printf("\n");
        free(filtered_list1);
    }

    const char *removals2[] = {"black", "orange"};
    size_t removals_size2 = sizeof(removals2) / sizeof(removals2[0]);

    size_t out_size2 = 0;
    char **filtered_list2 = remove_words(list, list_size, removals2, removals_size2, &out_size2);
    if (filtered_list2 != NULL) {
        for (size_t i = 0; i < out_size2; i++) {
            printf("%s ", filtered_list2[i]);
        }
        printf("\n");
        free(filtered_list2);
    }

    const char *removals3[] = {"black", "orange"};
    size_t removals_size3 = sizeof(removals3) / sizeof(removals3[0]);
    
    char *list3[] = {"red", "green", "blue", "white", "black", "orange"};
    size_t list_size3 = sizeof(list3) / sizeof(list3[0]);

    size_t out_size3 = 0;
    char **filtered_list3 = remove_words(list3, list_size3, removals3, removals_size3, &out_size3);
    if (filtered_list3 != NULL) {
        for (size_t i = 0; i < out_size3; i++) {
            printf("%s ", filtered_list3[i]);
        }
        printf("\n");
        free(filtered_list3);
    }

    return 0;
}
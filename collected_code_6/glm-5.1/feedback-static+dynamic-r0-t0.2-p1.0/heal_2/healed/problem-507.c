#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **list, size_t list_size, const char **remove_list, size_t remove_size, size_t *out_size) {
    if (list == NULL || remove_list == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        int should_remove = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (strcmp(list[i], remove_list[j]) == 0) {
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

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *list[] = {"red", "green", "blue", "black", "white", "orange"};
    const char *remove_case0[] = {"apple"};
    const char *remove_case1[] = {"black"};
    const char *remove_case2[] = {"blue", "white"};
    
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t out_size = 0;
    int case_num = 0;
    
    char **filtered_list = remove_words(list, list_size, remove_case0, sizeof(remove_case0) / sizeof(remove_case0[0]), &out_size);
    if (filtered_list != NULL) {
        printf("Test case %d: [", case_num++);
        for (size_t i = 0; i < out_size; i++) {
            printf("'%s'", filtered_list[i]);
            if (i < out_size - 1) printf(", ");
            free(filtered_list[i]);
        }
        printf("]\n");
        free(filtered_list);
    }

    filtered_list = remove_words(list, list_size, remove_case1, sizeof(remove_case1) / sizeof(remove_case1[0]), &out_size);
    if (filtered_list != NULL) {
        printf("Test case %d: [", case_num++);
        for (size_t i = 0; i < out_size; i++) {
            printf("'%s'", filtered_list[i]);
            if (i < out_size - 1) printf(", ");
            free(filtered_list[i]);
        }
        printf("]\n");
        free(filtered_list);
    }

    filtered_list = remove_words(list, list_size, remove_case2, sizeof(remove_case2) / sizeof(remove_case2[0]), &out_size);
    if (filtered_list != NULL) {
        printf("Test case %d: [", case_num++);
        for (size_t i = 0; i < out_size; i++) {
            printf("'%s'", filtered_list[i]);
            if (i < out_size - 1) printf(", ");
            free(filtered_list[i]);
        }
        printf("]\n");
        free(filtered_list);
    }

    return EXIT_SUCCESS;
}
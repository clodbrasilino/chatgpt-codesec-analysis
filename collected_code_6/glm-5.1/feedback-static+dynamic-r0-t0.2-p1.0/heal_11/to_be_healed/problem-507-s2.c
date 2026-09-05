#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

char **remove_words(char * const *list, size_t list_size, char const * const *remove_list, size_t remove_size, size_t *out_size) {
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
        if (list[i] != NULL) {
            for (size_t j = 0; j < remove_size; j++) {
                if (remove_list[j] != NULL && strcmp(list[i], remove_list[j]) == 0) {
                    should_remove = 1;
                    break;
                }
            }
        }
        if (!should_remove) {
            result[count] = strdup(list[i]);
            if (result[count] == NULL) {
                for (size_t k = 0; k < count; k++) {
                    free(result[k]);
                }
                free(result);
                *out_size = 0;
                return NULL;
            }
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    *out_size = count;
    return result;
}

int main(void) {
    const char *list[] = {"red", "green", "blue", "black", "white", "orange"};
    const char *remove_list0[] = {"white", "orange"};
    const char *remove_list1[] = {"black", "orange"};
    const char *remove_list2[] = {"blue", "white"};

    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t remove_size0 = sizeof(remove_list0) / sizeof(remove_list0[0]);
    size_t remove_size1 = sizeof(remove_list1) / sizeof(remove_list1[0]);
    size_t remove_size2 = sizeof(remove_list2) / sizeof(remove_list2[0]);
    size_t out_size = 0;

    char **new_list0 = remove_words((char * const *)list, list_size, (char const * const *)remove_list0, remove_size0, &out_size);
    if (new_list0 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s", new_list0[i]);
            if (i < out_size - 1) {
                printf(" ");
            }
        }
        printf("\n");
        for (size_t i = 0; i < out_size; i++) {
            free(new_list0[i]);
        }
        free(new_list0);
    }

    out_size = 0;
    char **new_list1 = remove_words((char * const *)list, list_size, (char const * const *)remove_list1, remove_size1, &out_size);
    if (new_list1 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s", new_list1[i]);
            if (i < out_size - 1) {
                printf(" ");
            }
        }
        printf("\n");
        for (size_t i = 0; i < out_size; i++) {
            free(new_list1[i]);
        }
        free(new_list1);
    }

    out_size = 0;
    char **new_list2 = remove_words((char * const *)list, list_size, (char const * const *)remove_list2, remove_size2, &out_size);
    if (new_list2 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s", new_list2[i]);
            if (i < out_size - 1) {
                printf(" ");
            }
        }
        printf("\n");
        for (size_t i = 0; i < out_size; i++) {
            free(new_list2[i]);
        }
        free(new_list2);
    }

    return 0;
}
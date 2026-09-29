#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

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
        if (list[i] != NULL) {
            for (size_t j = 0; j < remove_size; j++) {
                if (remove_list[j] != NULL && strcmp(list[i], remove_list[j]) == 0) {
                    should_remove = 1;
                    break;
                }
            }
        }
        if (!should_remove) {
            result[count] = list[i];
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
    char *list[] = {"red", "green", "blue", "black", "white", "orange"};
    const char *remove_list0[] = {"white", "orange"};
    const char *remove_list1[] = {"black", "orange"};
    const char *remove_list2[] = {"blue", "white"};
    
    const char **rem0 = remove_list0;
    const char **rem1 = remove_list1;
    const char **rem2 = remove_list2;
    
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t out_size = 0;
    
    char **new_list0 = remove_words(list, list_size, rem0, sizeof(remove_list0) / sizeof(remove_list0[0]), &out_size);
    if (new_list0 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s ", new_list0[i]);
        }
        printf("\n");
        free(new_list0);
    } else if (out_size == 0) {
        printf("\n");
    }

    char **new_list1 = remove_words(list, list_size, rem1, sizeof(remove_list1) / sizeof(remove_list1[0]), &out_size);
    if (new_list1 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s ", new_list1[i]);
        }
        printf("\n");
        free(new_list1);
    } else if (out_size == 0) {
        printf("\n");
    }

    char **new_list2 = remove_words(list, list_size, rem2, sizeof(remove_list2) / sizeof(remove_list2[0]), &out_size);
    if (new_list2 != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s ", new_list2[i]);
        }
        printf("\n");
        free(new_list2);
    } else if (out_size == 0) {
        printf("\n");
    }

    return 0;
}
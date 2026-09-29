#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
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
        if (list[i] == NULL) {
            continue;
        }
        int should_remove = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (remove_list[j] != NULL && strcmp(list[i], remove_list[j]) == 0) {
                should_remove = 1;
                break;
            }
        }
        if (!should_remove) {
            result[count] = list[i];
            count++;
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
    char *words_case0[] = {"red", "green", "blue", "black"};
    const char *to_remove0[] = {"black"};
    size_t words_size0 = sizeof(words_case0) / sizeof(words_case0[0]);
    size_t remove_size0 = sizeof(to_remove0) / sizeof(to_remove0[0]);
    size_t out_size0 = 0;
    char **filtered0 = remove_words(words_case0, words_size0, to_remove0, remove_size0, &out_size0);
    if (filtered0 != NULL) {
        for (size_t i = 0; i < out_size0; i++) {
            printf("%s ", filtered0[i]);
        }
        printf("\n");
        free(filtered0);
    }

    char *words_case1[] = {"red", "green", "blue", "white"};
    const char *to_remove1[] = {"black"};
    size_t words_size1 = sizeof(words_case1) / sizeof(words_case1[0]);
    size_t remove_size1 = sizeof(to_remove1) / sizeof(to_remove1[0]);
    size_t out_size1 = 0;
    char **filtered1 = remove_words(words_case1, words_size1, to_remove1, remove_size1, &out_size1);
    if (filtered1 != NULL) {
        for (size_t i = 0; i < out_size1; i++) {
            printf("%s ", filtered1[i]);
        }
        printf("\n");
        free(filtered1);
    }

    char *words_case2[] = {"red", "green", "black", "orange"};
    const char *to_remove2[] = {"black"};
    size_t words_size2 = sizeof(words_case2) / sizeof(words_case2[0]);
    size_t remove_size2 = sizeof(to_remove2) / sizeof(to_remove2[0]);
    size_t out_size2 = 0;
    char **filtered2 = remove_words(words_case2, words_size2, to_remove2, remove_size2, &out_size2);
    if (filtered2 != NULL) {
        for (size_t i = 0; i < out_size2; i++) {
            printf("%s ", filtered2[i]);
        }
        printf("\n");
        free(filtered2);
    }

    return 0;
}
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
        for (size_t j = 0; j < remove_size; j++) {
            if (strcmp(list[i], remove_list[j]) == 0) {
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
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const char *remove_list[] = {"banana", "date"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t remove_size = sizeof(remove_list) / sizeof(remove_list[0]);
    size_t out_size = 0;

    char **filtered_list = remove_words(list, list_size, remove_list, remove_size, &out_size);
    if (filtered_list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_size; i++) {
        printf("%s\n", filtered_list[i]);
    }

    free(filtered_list);
    return EXIT_SUCCESS;
}
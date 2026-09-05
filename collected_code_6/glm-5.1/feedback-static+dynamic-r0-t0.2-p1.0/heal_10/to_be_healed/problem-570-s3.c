#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) return 0;
    if (substr[0] == '\0') return 0;
    return strstr(str, substr) != NULL;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(char **list, size_t count, const char *substr, size_t *out_count) {
    if (list == NULL || substr == NULL || out_count == NULL) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && contains_substring(list[i], substr)) {
            free(list[i]);
        } else {
            result[j++] = list[i];
        }
    }

    *out_count = j;

    if (j == 0) {
        free(result);
        free(list);
        result = NULL;
    } else {
        free(list);
    }

    return result;
}

int main(void) {
    size_t count = 5;
    char **list = (char **)malloc(count * sizeof(char *));
    if (list == NULL) {
        return 1;
    }

    list[0] = strdup("Red");
    list[1] = strdup("");
    list[2] = strdup("Green");
    list[3] = strdup("Orange");
    list[4] = strdup("White");

    if (list[0] == NULL || list[1] == NULL || list[2] == NULL || list[3] == NULL || list[4] == NULL) {
        for (size_t i = 0; i < count; i++) {
            if (list[i] != NULL) {
                free(list[i]);
            }
        }
        free(list);
        return 1;
    }

    size_t out_count = 0;
    char **new_list = remove_words(list, count, "an", &out_count);

    if (new_list != NULL) {
        printf("[");
        for (size_t i = 0; i < out_count; i++) {
            printf("'%s'", new_list[i]);
            if (i < out_count - 1) {
                printf(", ");
            }
            free(new_list[i]);
        }
        printf("]\n");
        free(new_list);
    } else {
        printf("[]\n");
    }

    return 0;
}
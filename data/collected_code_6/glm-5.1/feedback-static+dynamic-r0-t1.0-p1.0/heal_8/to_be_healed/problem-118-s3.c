#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

char **string_to_list(const char *str, size_t *list_len) {
    if (str == NULL || list_len == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *ptr = str;
    while (*ptr) {
        ptr += strspn(ptr, " \t\n\r\f\v");
        if (*ptr == '\0') break;
        len++;
        ptr += strcspn(ptr, " \t\n\r\f\v");
    }

    if (len == 0) {
        *list_len = 0;
        return NULL;
    }

    char **list = malloc(len * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    ptr = str;
    size_t idx = 0;
    while (*ptr) {
        ptr += strspn(ptr, " \t\n\r\f\v");
        if (*ptr == '\0') break;
        size_t word_len = strcspn(ptr, " \t\n\r\f\v");
        list[idx] = malloc(word_len + 1);
        if (list[idx] == NULL) {
            for (size_t j = 0; j < idx; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        if (word_len > 0) {
            size_t copy_len = word_len < (word_len + 1) ? word_len : (word_len + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list[idx], ptr, copy_len);
        }
        list[idx][word_len] = '\0';
        idx++;
        ptr += word_len;
    }

    *list_len = idx;
    return list;
}

void free_list(char **list, size_t list_len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list_len; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *test_cases[] = {
        "python programming",
        "lists tuples strings",
        "write a program"
    };
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        size_t list_len = 0;
        char **list = string_to_list(test_cases[i], &list_len);
        printf("[");
        if (list != NULL) {
            for (size_t j = 0; j < list_len; j++) {
                printf("'%s'%s", list[j], (j < list_len - 1) ? ", " : "");
            }
            free_list(list, list_len);
        }
        printf("]\n");
    }

    return 0;
}
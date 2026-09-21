#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  */

char **string_to_list(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }
    if (delim == NULL) {
        delim = " \t\n\r";
    }

    size_t tmp_len = strnlen(str, 1048576) + 1;
    char *tmp = malloc(tmp_len);
    if (tmp == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tmp, str, tmp_len - 1);
    tmp[tmp_len - 1] = '\0';

    char **list = NULL;
    size_t capacity = 0;
    size_t count = 0;

    char *token = strtok(tmp, delim);
    while (token != NULL) {
        if (count >= capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
            char **new_list = realloc(list, (new_capacity + 1) * sizeof(char *));
            if (new_list == NULL) {
                free(tmp);
                for (size_t i = 0; i < count; i++) {
                    free(list[i]);
                }
                free(list);
                return NULL;
            }
            list = new_list;
            capacity = new_capacity;
        }

        size_t token_len = strnlen(token, tmp_len) + 1;
        list[count] = malloc(token_len);
        if (list[count] == NULL) {
            free(tmp);
            for (size_t i = 0; i < count; i++) {
                free(list[i]);
            }
            free(list);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list[count], token, token_len);

        count++;
        token = strtok(NULL, delim);
    }

    free(tmp);

    if (count == 0) {
        list = malloc(sizeof(char *));
        if (list == NULL) {
            return NULL;
        }
    } else {
        char **new_list = realloc(list, (count + 1) * sizeof(char *));
        if (new_list != NULL) {
            list = new_list;
        }
    }

    list[count] = NULL;

    return list;
}

void free_list(char **list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *input = "hello world this is a test";
    const char *delim = " ";
    char **list = string_to_list(input, delim);
    
    if (list != NULL) {
        for (size_t i = 0; list[i] != NULL; i++) {
            printf("%s\n", list[i]);
        }
        free_list(list);
    }
    
    return 0;
}
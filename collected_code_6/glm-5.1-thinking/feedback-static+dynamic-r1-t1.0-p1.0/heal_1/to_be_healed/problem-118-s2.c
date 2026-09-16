#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  */

char **string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    char *tmp = strdup(str);
    if (tmp == NULL) {
        return NULL;
    }

    char **list = NULL;
    size_t capacity = 0;
    size_t count = 0;
    char *saveptr = NULL;

    char *token = strtok_r(tmp, delim, &saveptr);
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

        list[count] = strdup(token);
        if (list[count] == NULL) {
            free(tmp);
            for (size_t i = 0; i < count; i++) {
                free(list[i]);
            }
            free(list);
            return NULL;
        }
        count++;
        token = strtok_r(NULL, delim, &saveptr);
    }

    free(tmp);

    char **new_list = realloc(list, (count + 1) * sizeof(char *));
    if (new_list == NULL) {
        for (size_t i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
        return NULL;
    }
    list = new_list;
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
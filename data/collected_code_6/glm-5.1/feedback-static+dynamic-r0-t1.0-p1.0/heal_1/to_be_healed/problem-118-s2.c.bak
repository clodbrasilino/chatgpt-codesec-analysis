#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got ["w","r","i","t","e"," ","a"," ","p","r","o","g","r","a","m"]
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got ["l","i","s","t","s"," ","t","u","p","l","e","s"," ","s","t","r","i","n","g","s"]
  *  test case 0 failed: expected ['python', 'programming'], got ["p","y","t","h","o","n"," ","p","r","o","g","r","a","m","m","i","n","g"]
  */

char **string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    char **list = malloc((len + 1) * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        list[i] = malloc(2 * sizeof(char));
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        list[i][0] = str[i];
        list[i][1] = '\0';
    }

    list[len] = NULL;
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
    const char *str = "hello";
    char **list = string_to_list(str);

    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; list[i] != NULL; i++) {
        printf("%s\n", list[i]);
    }

    free_list(list);

    return EXIT_SUCCESS;
}
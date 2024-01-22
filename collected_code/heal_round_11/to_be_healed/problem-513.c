#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char **list, size_t *size_list) {
    if (tuple != NULL && string != NULL && list != NULL && size_list > 0) {
        size_t len_tuple = strnlen(tuple, MAX_SIZE - 1);
        size_t len_string = strnlen(string, MAX_SIZE - len_tuple - 1);

        if((len_tuple + len_string + 1) <= *size_list) {
            /* Possible weaknesses found:
             *  leak of 'list' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            *list = malloc(len_tuple + len_string + 1); 
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(*list, tuple, len_tuple);
            (*list)[len_tuple] = '\0';
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
             */
            strncat(*list, string, len_string);
        } else {
            printf("Buffer not large enough to store concatenated string\n");
        }
    }
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-";
    size_t size_list = sizeof(tuple) + sizeof(string) + 1;
    char *list = malloc(size_list);

    tupleToList(tuple, string, &list, &size_list);

    if (list) {
        printf("%s\n", list);
        free(list);
    }

    return 0;
}

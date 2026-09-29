#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char **list, size_t *size_list) {
    if (tuple != NULL && string != NULL && list != NULL && size_list > 0) {
        size_t len_tuple = strnlen(tuple, MAX_SIZE - 1);
        size_t len_string = strnlen(string, MAX_SIZE - len_tuple - 1);
        if ((len_tuple + len_string + 1) <= *size_list) {
            /* Possible weaknesses found:
             *  leak of 'list' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            *list = malloc(len_tuple + len_string + 1);
            if (*list) {
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(*list, tuple, len_tuple);
                (*list)[len_tuple] = '\0';
                /* Possible weaknesses found:
                 *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
                 */
                strncat(*list, string, len_string);
            } else {
                printf("Failed to allocate memory\n");
            }
        } else {
            printf("Buffer not large enough to store concatenated string\n");
        }
    }
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t size_list = strlen(tuple) + strlen(string) + 1;
    char *list = malloc(size_list);

    if (list) {
        tupleToList(tuple, string, &list, &size_list);
        /* Possible weaknesses found:
         *  use of NULL 'list' where non-null expected [CWE-476] [-Wanalyzer-null-argument]
         */
        printf("%s\n", list);
        free(list);
        return 0;
    } else {
        printf("Failed to allocate memory\n");
        return -1;
    }
}

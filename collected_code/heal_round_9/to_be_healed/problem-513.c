#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, size_t size_list) {
  
    if (tuple != NULL && string != NULL && list != NULL && size_list > 0) {
        size_t len_tuple = strnlen(tuple, size_list - 1);
        size_t len_string = strnlen(string, size_list - len_tuple - 1);

        if((len_tuple + len_string + 1) <= size_list) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(list, tuple, len_tuple);
            list[len_tuple] = '\0';
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
             */
            strncat(list, string, len_string);
        } else {
            printf("Buffer not large enough to store concatenated string\n");
        }
    }    
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char list[MAX_SIZE] = "";

    tupleToList(tuple, string, list, sizeof(list));

    printf("%s\n", list);

    return 0;
}

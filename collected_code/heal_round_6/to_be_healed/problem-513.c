#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, size_t size_list) {
    if (tuple == NULL || string == NULL || list == NULL || size_list <= 0) {
        return;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(list, tuple, size_list-1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(list, string, size_list - strlen(tuple) - 1);
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-"; 
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char list[MAX_SIZE] = "";

    tupleToList(tuple, string, list, sizeof(list)/sizeof(char));

    printf("%s\n", list);

    return 0;
}
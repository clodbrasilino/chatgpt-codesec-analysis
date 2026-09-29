#include <stdio.h>
#include <string.h>

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    if (!str1 || !str2 || !result) {
        return;
    }

    size_t str1Len = strnlen(str1, resultSize);
    size_t str2Len = strnlen(str2, resultSize);

    if (str1Len >= resultSize) {
        str1Len = resultSize - 1;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(result, str1, str1Len);
    result[str1Len] = '\0';

    if (str1Len + str2Len >= resultSize) {
       str2Len = resultSize - str1Len - 1;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(result, str2, str2Len);
    result[str2Len + str1Len] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[100] = "Hello, ";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str2[100] = "world!";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[200] = "";

    concatenateStrings(str1, str2, result, sizeof(result));

    printf("%s\n", result);
    return 0;
}
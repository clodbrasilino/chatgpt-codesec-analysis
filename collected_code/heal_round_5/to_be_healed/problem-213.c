#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    if (!str1 || !str2 || !result || resultSize == 0) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t str1Len = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t str2Len = strlen(str2);

    if (str1Len + str2Len >= resultSize) {
        if (str1Len >= resultSize) {
            str1Len = str2Len = resultSize / 2;
        } else {
            str2Len = resultSize - str1Len - 1;
        }
    }

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(result, str1, str1Len);
    result[str1Len] = '\0';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(result + str1Len, str2, str2Len);
    result[str1Len + str2Len] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[MAX_SIZE] = "Hello, ";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str2[MAX_SIZE] = "world!";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[MAX_SIZE*2] = "";

    concatenateStrings(str1, str2, result, sizeof(result));

    printf("%s\n", result);
    return 0;
}
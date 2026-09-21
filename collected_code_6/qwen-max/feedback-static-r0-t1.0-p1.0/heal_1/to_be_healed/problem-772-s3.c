#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(char *str, int k) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (!result) return NULL;
    result[0] = '\0';
    
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     *  Variable 'j' is assigned a value that is never used. [unreadVariable]
     */
    int i = 0, j = 0;
    while (i < len) {
        j = i;
        while (j < len && str[j] != ' ') j++;
        int word_len = j - i;
        if (word_len != k) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, str + i);
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            if (j < len) strcat(result, " ");
        }
        i = j + 1;
    }
    
    free(str);
    return result;
}

int main() {
    char str[] = "this is a test string with some words of length four and five";
    int k = 4;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}
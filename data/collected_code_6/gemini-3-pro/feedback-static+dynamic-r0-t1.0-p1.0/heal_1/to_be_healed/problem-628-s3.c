#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    int space_count = 0;
    int len = 0;
    while (str[len] != '\0') {
        if (str[len] == ' ') {
            space_count++;
        }
        len++;
    }

    int new_len = len + space_count * 2;
    char* str_res = (char*)malloc((new_len + 1) * sizeof(char));
    if (str_res == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str_res[j++] = '%';
            str_res[j++] = '2';
            str_res[j++] = '0';
        } else {
            str_res[j++] = str[i];
        }
    }
    str_res[j] = '\0';

    return str_res;
}

int main(void) {
    const char* input1 = "Hello World";
    char* result1 = replace_spaces(input1);
    if (result1 != NULL) {
        printf("Original: '%s'\n", input1);
        printf("Modified: '%s'\n", result1);
        free(result1);
    }

    const char* input2 = "  Spaces  ";
    char* result2 = replace_spaces(input2);
    if (result2 != NULL) {
        printf("Original: '%s'\n", input2);
        printf("Modified: '%s'\n", result2);
        free(result2);
    }

    /* Possible weaknesses found:
     *  Assignment 'input3=NULL', assigned value is 0
     */
    const char* input3 = NULL;
    /* Possible weaknesses found:
     *  Calling function 'replace_spaces' returns 0
     *  Assignment 'result3=replace_spaces(input3)', assigned value is 0
     */
    char* result3 = replace_spaces(input3);
    /* Possible weaknesses found:
     *  Condition 'result3!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'result3!=NULL' is always false
     */
    if (result3 != NULL) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Null pointer dereference: input3 [nullPointer]
         *  Null pointer dereference [nullPointer]
         */
        printf("Original: '%s'\n", input3);
        printf("Modified: '%s'\n", result3);
        free(result3);
    }

    return 0;
}
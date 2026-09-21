#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convert_date_format(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 11);
    if (len != 10 || input[4] != '-' || input[7] != '-') {
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (input[i] < '0' || input[i] > '9') {
            return NULL;
        }
    }

    char* output = (char*)malloc(11);
    if (output == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    memcpy_s(output, 11, input + 8, 2);
    output[2] = '-';
    memcpy_s(output + 3, 11 - 3, input + 5, 2);
    output[5] = '-';
    memcpy_s(output + 6, 11 - 6, input, 4);
    output[10] = '\0';

    return output;
}

int main() {
    const char* date1 = "2023-10-25";
    char* converted1 = convert_date_format(date1);
    if (converted1 != NULL) {
        printf("%s\n", converted1);
        free(converted1);
    }

    const char* date2 = "2023/10/25";
    char* converted2 = convert_date_format(date2);
    if (converted2 != NULL) {
        printf("%s\n", converted2);
        free(converted2);
    }

    /* Possible weaknesses found:
     *  Calling function 'convert_date_format' returns 0
     *  Assignment 'converted3=convert_date_format(NULL)', assigned value is 0
     */
    char* converted3 = convert_date_format(NULL);
    /* Possible weaknesses found:
     *  Condition 'converted3!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'converted3!=NULL' is always false
     */
    if (converted3 != NULL) {
        printf("%s\n", converted3);
        free(converted3);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_' && i + 1 < len && islower((unsigned char)snake_str[i + 1])) {
            camel_str[j++] = toupper((unsigned char)snake_str[i + 1]);
            i++;
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char *input1 = "convert_this_snake_case_string";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("Input: %s\nOutput: %s\n", input1, output1);
        free(output1);
    }

    const char *input2 = "alreadycamelcase";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("Input: %s\nOutput: %s\n", input2, output2);
        free(output2);
    }

    const char *input3 = NULL;
    /* Possible weaknesses found:
     *  Assignment 'output3=snake_to_camel(input3)', assigned value is 0
     *  Calling function 'snake_to_camel' returns 0
     */
    char *output3 = snake_to_camel(input3);
    /* Possible weaknesses found:
     *  Condition 'output3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'output3==NULL' is always true
     */
    if (output3 == NULL) {
        printf("NULL input handled safely.\n");
    }
    free(output3);

    return 0;
}
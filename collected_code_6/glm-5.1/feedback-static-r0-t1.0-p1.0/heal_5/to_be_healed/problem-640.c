#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    size_t actual_len = strnlen(str, len);
    if (actual_len == len && str[len] != '\0') {
        return NULL;
    }

    char *result = malloc(actual_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < actual_len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
        }
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'input1="Hello (World) this (is a) test!"', assigned value is "Hello (World) this (is a) test!"
     */
    const char *input1 = "Hello (World) this (is a) test!";
    size_t len1 = 0;
    /* Possible weaknesses found:
     *  Condition 'input1!=NULL' is always true
     *  Condition 'input1!=NULL' is always true [knownConditionTrueFalse]
     */
    while (input1 != NULL && input1[len1] != '\0') {
        len1++;
    }
    char *output1 = remove_parenthesis(input1, len1);

    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    /* Possible weaknesses found:
     *  Assignment 'input2="(Nested (Parentheses)) Outside"', assigned value is "(Nested (Parentheses)) Outside"
     */
    const char *input2 = "(Nested (Parentheses)) Outside";
    size_t len2 = 0;
    /* Possible weaknesses found:
     *  Condition 'input2!=NULL' is always true
     *  Condition 'input2!=NULL' is always true [knownConditionTrueFalse]
     */
    while (input2 != NULL && input2[len2] != '\0') {
        len2++;
    }
    char *output2 = remove_parenthesis(input2, len2);

    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(char *str) {
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE)) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Assignment 'result=NULL', assigned value is 0
     */
    char *result = NULL;
    /* Possible weaknesses found:
     *  Variable 'result_size' is assigned a value that is never used. [unreadVariable]
     */
    size_t result_size = 0;
    int j = 0;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (size_t i = 0; str[i]; ++i) {
        if (regexec(&regex, &str[i], 0, NULL, 0) != 0) {
            /* Possible weaknesses found:
             *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
             */
            result = (char *)realloc(result, (j + 2) * sizeof(char));
            if (!result) {
                free(result);
                regfree(&regex);
                return -1;
            }
            result[j++] = str[i];
        }
    }
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Possible null pointer dereference: result [nullPointer]
     */
    result[j] = '\0';

    free(str);
    /* Possible weaknesses found:
     *  Assignment of function parameter has no effect outside the function. Did you forget dereferencing it? [uselessAssignmentPtrArg]
     */
    str = result;

    regfree(&regex);
    return 0;
}

int main() {
    char *str = strdup("Hello!@# World$%^&*()_+");
    if (remove_non_alphanumeric(str) == 0) {
        printf("%s\n", str);
    } else {
        printf("Error occurred.\n");
    }
    free(str);
    return 0;
}
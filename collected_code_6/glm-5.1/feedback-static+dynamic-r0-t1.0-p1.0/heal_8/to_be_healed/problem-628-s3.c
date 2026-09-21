#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'I%20am%20a%20Programmer', got <no output>
  *  test case 2 failed: expected 'I%20love%20Coding', got <no output>
  *  test case 0 failed: expected 'My%20Name%20is%20Dawood', got <no output>
  */

char* replace_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t space_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    size_t new_len = len + space_count * 2;
    char *new_str = malloc(new_len + 1);

    if (new_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            new_str[j++] = '%';
            new_str[j++] = '2';
            new_str[j++] = '0';
        } else {
            new_str[j++] = str[i];
        }
    }

    new_str[j] = '\0';
    return new_str;
}

int main(int argc, char *argv[]) {
    const char *original = "My Name is Dawood";
    char *replaced = replace_spaces(original);

    if (replaced != NULL) {
        printf("%s\n", replaced);
        free(replaced);
    }

    const char *test1 = "I am a Programmer";
    char *replaced1 = replace_spaces(test1);
    if (replaced1 != NULL) {
        printf("%s\n", replaced1);
        free(replaced1);
    }

    const char *test2 = "I love Coding";
    char *replaced2 = replace_spaces(test2);
    if (replaced2 != NULL) {
        printf("%s\n", replaced2);
        free(replaced2);
    }

    /* Possible weaknesses found:
     *  Calling function 'replace_spaces' returns 0
     *  Assignment 'null_result=replace_spaces(NULL)', assigned value is 0
     */
    char *null_result = replace_spaces(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_result==NULL' is always true
     *  Condition 'null_result==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_result == NULL) {
        printf("NULL input handled.\n");
    } else {
        free(null_result);
    }

    return 0;
}
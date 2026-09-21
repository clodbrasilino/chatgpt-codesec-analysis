#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int count_01 = 0;
    int count_10 = 0;
    size_t i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }

        if (str1[i] == '0' && str2[i] == '1') {
            count_01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count_10++;
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (count_01 != count_10) {
        return -1;
    }

    return count_01;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        printf("Not Possible\n");
        free(buffer);
        return 0;
    }

    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as pointer to const [constVariablePointer]
     */
    char *str1 = strtok(buffer, " \t\n\r");
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as pointer to const [constVariablePointer]
     */
    char *str2 = strtok(NULL, " \t\n\r");

    if (str1 != NULL && str2 != NULL) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    free(buffer);
    return 0;
}
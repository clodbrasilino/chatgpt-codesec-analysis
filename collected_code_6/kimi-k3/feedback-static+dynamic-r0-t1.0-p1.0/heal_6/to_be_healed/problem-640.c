#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got ��
  *  test case 1 failed: expected 'string', got  ��
  *  test case 2 failed: expected 'alpha', got `��
  */

char *remove_parenthesis_area(const char *str)
{
    size_t len;
    char *result;
    size_t i;
    size_t j;
    int depth;
    int has_content;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;
    depth = 0;
    has_content = 0;

    while (str[i] != '\0') {
        if (str[i] == '(') {
            depth++;
            has_content = 1;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j] = str[i];
                j++;
            }
        } else if (depth == 0) {
            result[j] = str[i];
            j++;
            has_content = 1;
        }
        i++;
    }

    if (has_content == 0 && len > 0) {
        strcpy(result, str);
    } else {
        result[j] = '\0';
    }

    return result;
}

int main(void)
{
    const char *test_str = "Hello (World) Test (Example) Done";
    char *result;

    result = remove_parenthesis_area(test_str);

    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    return 0;
}
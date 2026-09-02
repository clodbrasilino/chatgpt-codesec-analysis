#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got �Q�
  *  test case 0 failed: expected 'python', got  Q�
  *  test case 1 failed: expected 'string', got `Q�
  */

char* remove_parenthesis(const char *s) {
    int len = strlen(s);
    char *result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;
    
    int r_index = 0;
    int p_count = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            p_count++;
        } else if (s[i] == ')') {
            if (p_count > 0) {
                p_count--;
            }
        } else if (p_count == 0) {
            result[r_index++] = s[i];
        }
    }

    result[r_index] = '\0';
    return result;
}

int main() {
    const char input[] = "Hello (World, this is a (test)) string.";
    char *output = remove_parenthesis(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}
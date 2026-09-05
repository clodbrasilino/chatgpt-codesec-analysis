#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

char *remove_parenthesis(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else {
            /* Possible weaknesses found:
             *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
             *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            if (depth == 0 && !isspace((unsigned char)str[i])) {
                result[j++] = str[i];
            }
        }
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        return shrunk;
    }

    return result;
}

int main(void) {
    const char *input0 = "python (is) great";
    char *output0 = remove_parenthesis(input0);
    if (output0) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "a (string) test";
    char *output1 = remove_parenthesis(input1);
    if (output1) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "alpha (beta) gamma";
    char *output2 = remove_parenthesis(input2);
    if (output2) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input = "Hello (World) C (Programming) Language";
    char *output = remove_parenthesis(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}
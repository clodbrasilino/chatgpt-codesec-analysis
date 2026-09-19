#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isdigit'
  */

char* remove_digits(const char *input) {
    int len = strlen(input);
    char *output = (char *)malloc((len + 1) * sizeof(char));
    if (output == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'isdigit'
         *  call to undeclared library function 'isdigit' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if (!isdigit(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

void free_strings(char **strings, int n) {
    for (int i = 0; i < n; i++) {
        if (strings[i] != NULL) {
            free(strings[i]);
        }
    }
    free(strings);
}

int main() {
    char *strings[] = {"abc123", "456def789", "ghi0jkl", "mno"};
    int n = sizeof(strings) / sizeof(strings[0]);

    char **new_strings = (char **)malloc(n * sizeof(char *));
    if (new_strings == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        new_strings[i] = remove_digits(strings[i]);
        if (new_strings[i] == NULL) {
            free_strings(new_strings, i);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s\n", new_strings[i]);
    }

    free_strings(new_strings, n);
    return 0;
}
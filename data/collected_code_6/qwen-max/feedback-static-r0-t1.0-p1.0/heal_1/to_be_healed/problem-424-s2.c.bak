#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void extract_rear(char *output[], char *input[], int len) {
    for (int i = 0; i < len; ++i) {
        if (input[i] != NULL && input[i][0] != '\0') {
            int str_len = strlen(input[i]);
            /* Possible weaknesses found:
             *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
             *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
             */
            output[i] = (char *)malloc(sizeof(char) * 2);
            if (output[i] == NULL) {
                continue;
            }
            output[i][0] = input[i][str_len - 1];
            output[i][1] = '\0';
        } else {
            output[i] = (char *)malloc(sizeof(char));
            if (output[i] == NULL) {
                continue;
            }
            output[i][0] = '\0';
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "", NULL};
    int len = sizeof(strings) / sizeof(strings[0]);
    char *results[len];

    extract_rear(results, strings, len);

    for (int i = 0; i < len; ++i) {
        if (results[i] != NULL) {
            printf("%s\n", results[i]);
            /* Possible weaknesses found:
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  include '<stdlib.h>' or provide a declaration of 'free'
             */
            free(results[i]);
        }
    }

    return 0;
}
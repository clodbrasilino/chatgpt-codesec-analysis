#include <stdio.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int find_min_char(const char *str) {
    int counts[256] = {0};
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    int min_count = INT_MAX;
    char min_char = '\0';
    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0 && counts[i] < min_count) {
            min_count = counts[i];
            min_char = (char)i;
        }
    }

    return min_char;
}

char *minimize_string_length(char *str, char ch) {
    int len = strlen(str);
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *result = (char *)malloc(len + 1);
    int k = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != ch) {
            result[k++] = str[i];
        }
    }
    result[k] = '\0';

    return result;
}

int main() {
    char str[] = "aabccbb";
    char min_char = find_min_char(str);
    char *result = minimize_string_length(str, min_char);
    printf("Original: %s\n", str);
    printf("Minimized: %s\n", result);

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(result);
    return 0;
}
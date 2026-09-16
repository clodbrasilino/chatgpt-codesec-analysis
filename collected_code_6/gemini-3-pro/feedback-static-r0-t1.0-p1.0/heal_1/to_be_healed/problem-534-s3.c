#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int search_literal(const char *original, const char *pattern, int **occurrences) {
    if (original == NULL || pattern == NULL || occurrences == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Variable 'original_len' is assigned a value that is never used. [unreadVariable]
     */
    int original_len = strlen(original);
    int pattern_len = strlen(pattern);

    if (pattern_len == 0) {
        return -1;
    }

    int count = 0;
    const char *temp = original;
    while ((temp = strstr(temp, pattern)) != NULL) {
        count++;
        temp += pattern_len;
    }

    if (count == 0) {
        *occurrences = NULL;
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    *occurrences = (int *)malloc(count * sizeof(int));
    if (*occurrences == NULL) {
        return -1;
    }

    count = 0;
    temp = original;
    while ((temp = strstr(temp, pattern)) != NULL) {
        (*occurrences)[count++] = temp - original;
        temp += pattern_len;
    }

    return count;
}

int main() {
    const char *original = "hello world, hello universe, hello everyone";
    const char *pattern = "hello";
    int *occurrences = NULL;

    int count = search_literal(original, pattern, &occurrences);

    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            printf("Pattern found at index: %d\n", occurrences[i]);
        }
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        free(occurrences);
    } else if (count == 0) {
        printf("Pattern not found.\n");
    } else {
        printf("Error occurred during search.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int min_swaps(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == 0) return 0;
    size_t pos_count = 0;
    size_t alloc_size = len * sizeof(size_t);
    if (alloc_size / sizeof(size_t) != len) return -1;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    size_t *positions = (size_t *)malloc(alloc_size);
    if (!positions) return -1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            positions[pos_count++] = i;
        }
    }
    int swaps = 0;
    int balance = 0;
    size_t next_open = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '[') {
            balance++;
            next_open++;
        } else {
            balance--;
        }
        if (balance < 0) {
            if (next_open >= pos_count) {
                /* Possible weaknesses found:
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  include '<stdlib.h>' or provide a declaration of 'free'
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 */
                free(positions);
                return -1;
            }
            swaps += (int)(positions[next_open] - i);
            balance = 1;
            next_open++;
        }
    }
    free(positions);
    if (balance != 0) return -1;
    return swaps;
}

int main() {
    char str1[] = "[]][][";
    printf("%d\n", min_swaps(str1, sizeof(str1)));
    char str2[] = "[[][]]";
    printf("%d\n", min_swaps(str2, sizeof(str2)));
    char str3[] = "]]][[[";
    printf("%d\n", min_swaps(str3, sizeof(str3)));
    char str4[] = "][";
    printf("%d\n", min_swaps(str4, sizeof(str4)));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    printf("%zu\n", string_length("Hello"));
    printf("%zu\n", string_length("World!"));
    printf("%zu\n", string_length("C coding"));

    return EXIT_SUCCESS;
}
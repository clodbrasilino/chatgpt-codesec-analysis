#include <stdio.h>
#include <stdlib.h>

size_t find_total_ascii(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t total = 0;
    size_t i = 0;
    
    while (str[i] != '\0') {
        total += (size_t)str[i];
        i++;
    }
    
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    size_t sum = find_total_ascii(argv[1]);
    printf("%zu\n", sum);
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_std_occurrence(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int count = 0;
    size_t len = strlen(str);
    if (len < 3) {
        return 0;
    }
    for (size_t i = 0; i <= len - 3; i++) {
        if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int count = find_std_occurrence(argv[1]);
    printf("%d\n", count);
    return EXIT_SUCCESS;
}
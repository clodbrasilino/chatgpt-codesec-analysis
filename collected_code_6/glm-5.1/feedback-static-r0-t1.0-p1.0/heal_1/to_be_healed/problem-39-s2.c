#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int can_rearrange(const char *str) {
    if (str == NULL) {
        return 0;
    }

    unsigned long len = strlen(str);
    if (len <= 1) {
        return 1;
    }

    int count[256] = {0};
    int max_count = 0;

    for (unsigned long i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
        if (count[c] > max_count) {
            max_count = count[c];
        }
    }

    if (max_count > (int)((len + 1) / 2)) {
        return 0;
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = can_rearrange(argv[1]);
    
    if (result) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}
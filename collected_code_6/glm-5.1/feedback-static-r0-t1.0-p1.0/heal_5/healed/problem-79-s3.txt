#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t len = strlen(word);
    return len % 2 != 0;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }
    if (is_odd_length(argv[1])) {
        printf("odd\n");
    } else {
        printf("even\n");
    }
    return 0;
}
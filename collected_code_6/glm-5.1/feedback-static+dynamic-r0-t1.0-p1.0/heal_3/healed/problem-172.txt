#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_std_occurrence(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = strnlen(str, max_len);
    if (len < 3) {
        return 0;
    }
    int count = 0;
    for (size_t i = 0; i <= len - 3; i++) {
        if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            count++;
        }
    }
    return count;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t argv_len = 0;
    while (argv[1][argv_len] != '\0' && argv_len < 4096) {
        argv_len++;
    }
    int count = find_std_occurrence(argv[1], argv_len);
    printf("%d\n", count);
    return EXIT_SUCCESS;
}
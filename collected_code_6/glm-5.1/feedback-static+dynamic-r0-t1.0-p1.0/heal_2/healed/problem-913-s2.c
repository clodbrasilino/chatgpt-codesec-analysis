#include <stdio.h>
#include <ctype.h>

int check_number_at_end(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    const char *end = str;
    while (*end != '\0') {
        end++;
    }

    const char *ptr = end - 1;
    while (ptr >= str && isdigit((unsigned char)*ptr)) {
        ptr--;
    }

    return (end - ptr - 1 > 0) ? 1 : 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = check_number_at_end(argv[1]);
    printf("%d\n", result);

    return 0;
}
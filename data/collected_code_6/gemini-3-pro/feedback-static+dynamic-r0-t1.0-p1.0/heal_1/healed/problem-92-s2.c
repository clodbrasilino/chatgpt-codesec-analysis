#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_undulating(const char *num_str);

bool is_undulating(const char *num_str) {
    if (num_str == NULL) {
        return false;
    }

    size_t len = 0;
    while (num_str[len] != '\0') {
        if (num_str[len] < '0' || num_str[len] > '9') {
            return false;
        }
        len++;
    }

    if (len < 3) {
        return false;
    }

    if (num_str[0] == num_str[1]) {
        return false;
    }

    for (size_t i = 2; i < len; i++) {
        if (num_str[i] != num_str[i - 2]) {
            return false;
        }
    }

    return true;
}

int main(int argc, const char *const argv[]) {
    if (argc != 2) {
        return 1;
    }

    if (is_undulating(argv[1])) {
        printf("Undulating\n");
    } else {
        printf("Not undulating\n");
    }

    return 0;
}
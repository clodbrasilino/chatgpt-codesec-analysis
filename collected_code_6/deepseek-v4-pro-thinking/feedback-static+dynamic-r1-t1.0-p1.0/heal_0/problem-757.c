#include <stdio.h>
#include <string.h>

static int is_reverse_pair(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a != len_b) {
        return 0;
    }

    if (len_a == 0) {
        return 1;
    }

    for (size_t i = 0; i < len_a; ++i) {
        if (a[i] != b[len_a - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(char **strings, int n) {
    if (strings == NULL || n <= 0) {
        return 0;
    }

    int count = 0;

    for (int i = 0; i < n - 1; ++i) {
        if (strings[i] == NULL) {
            continue;
        }

        for (int j = i + 1; j < n; ++j) {
            if (strings[j] == NULL) {
                continue;
            }

            if (is_reverse_pair(strings[i], strings[j])) {
                ++count;
            }
        }
    }

    return count;
}

int main(void) {
    char *words[] = { "abc", "cba", "hello", "olleh", "test", "tset" };
    int n = (int)(sizeof(words) / sizeof(words[0]));

    printf("%d\n", count_reverse_pairs(words, n));

    return 0;
}
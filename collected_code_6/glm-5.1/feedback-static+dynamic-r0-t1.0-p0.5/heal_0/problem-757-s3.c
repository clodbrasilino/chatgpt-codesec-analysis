#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_reverse(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    if (len_a != len_b) {
        return 0;
    }
    for (size_t i = 0; i < len_a; i++) {
        if (a[i] != b[len_a - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int count_reverse_pairs(char **strings, int count) {
    int pair_count = 0;
    if (strings == NULL || count <= 0) {
        return 0;
    }
    int *used = calloc(count, sizeof(int));
    if (used == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (used[i]) {
            continue;
        }
        for (int j = i + 1; j < count; j++) {
            if (used[j]) {
                continue;
            }
            if (strings[i] != NULL && strings[j] != NULL && is_reverse(strings[i], strings[j])) {
                pair_count++;
                used[i] = 1;
                used[j] = 1;
                break;
            }
        }
    }
    free(used);
    return pair_count;
}

int main() {
    char *list[] = {"abc", "cba", "hello", "olleh", "world", "test", "tset"};
    int count = sizeof(list) / sizeof(list[0]);
    int result = count_reverse_pairs(list, count);
    printf("%d\n", result);
    return 0;
}
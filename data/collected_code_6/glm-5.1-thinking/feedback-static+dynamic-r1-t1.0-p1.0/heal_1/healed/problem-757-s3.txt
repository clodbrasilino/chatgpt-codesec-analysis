#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

bool is_reverse(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }
    size_t len1 = 0;
    while (len1 < MAX_STR_LEN && s1[len1] != '\0') {
        len1++;
    }
    if (len1 == MAX_STR_LEN) {
        return false;
    }
    size_t len2 = 0;
    while (len2 < MAX_STR_LEN && s2[len2] != '\0') {
        len2++;
    }
    if (len2 == MAX_STR_LEN) {
        return false;
    }
    if (len1 != len2) {
        return false;
    }
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return false;
        }
    }
    return true;
}

int count_reverse_pairs(char **strs, int n) {
    if (strs == NULL || n < 2) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (strs[i] == NULL) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (strs[j] == NULL) {
                continue;
            }
            if (is_reverse(strs[i], strs[j])) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    char *list1[] = {"abc", "cba", "hello", "olleh", "world"};
    int n1 = sizeof(list1) / sizeof(list1[0]);
    printf("%d\n", count_reverse_pairs(list1, n1));

    char *list2[] = {"abc", "def", "ghi"};
    int n2 = sizeof(list2) / sizeof(list2[0]);
    printf("%d\n", count_reverse_pairs(list2, n2));

    char *list3[] = {"ab", "ba", "ab", "ba"};
    int n3 = sizeof(list3) / sizeof(list3[0]);
    printf("%d\n", count_reverse_pairs(list3, n3));

    return 0;
}
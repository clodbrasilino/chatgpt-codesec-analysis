#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define BUF_SIZE (MAX_LEN + 3)

int minSwaps(const char *s1, const char *s2) {
    if (!s1 || !s2) return -1;

    size_t len = strnlen(s1, MAX_LEN + 1);
    if (len == 0 || len > MAX_LEN) return -1;

    if (strnlen(s2, MAX_LEN + 1) != len) return -1;

    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int pos1 = 0, pos2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') pos1++;
            else pos2++;
        }
    }

    if (pos1 % 2 == 0 && pos2 % 2 == 0) {
        return pos1 / 2 + pos2 / 2;
    } else if (pos1 % 2 == 1 && pos2 % 2 == 1) {
        return pos1 / 2 + pos2 / 2 + 2;
    }

    return -1;
}

int read_string(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    size_t len = strnlen(buf, size);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return 1;
}

int validate_binary(const char *s) {
    if (!s || *s == '\0') return 0;
    size_t len = strnlen(s, MAX_LEN + 1);
    if (len == 0 || len > MAX_LEN) return 0;
    for (size_t i = 0; i < len; i++) {
        if (s[i] != '0' && s[i] != '1') return 0;
    }
    return 1;
}

int main(void) {
    char s1[BUF_SIZE] = {0};
    char s2[BUF_SIZE] = {0};

    printf("Enter first binary string: ");
    if (!read_string(s1, BUF_SIZE)) {
        printf("-1\n");
        return 0;
    }

    printf("Enter second binary string: ");
    if (!read_string(s2, BUF_SIZE)) {
        printf("-1\n");
        return 0;
    }

    if (!validate_binary(s1) || !validate_binary(s2)) {
        printf("-1\n");
        return 0;
    }

    size_t len1 = strnlen(s1, BUF_SIZE);
    size_t len2 = strnlen(s2, BUF_SIZE);

    if (len1 != len2 || len1 == 0 || len1 > MAX_LEN) {
        printf("-1\n");
        return 0;
    }

    int result = minSwaps(s1, s2);
    printf("%d\n", result);

    return 0;
}
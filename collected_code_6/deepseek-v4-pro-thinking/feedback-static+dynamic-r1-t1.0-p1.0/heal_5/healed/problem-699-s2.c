#include <stdio.h>

long long minSwaps(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        printf("Not Possible\n");
        return -1;
    }
    size_t i = 0;
    size_t ones_s = 0, ones_t = 0;
    size_t len_s = 0, len_t = 0;
    while (s[i] != '\0') {
        if (s[i] != '0' && s[i] != '1') {
            printf("Not Possible\n");
            return -1;
        }
        if (s[i] == '1') {
            ones_s++;
        }
        i++;
    }
    len_s = i;
    i = 0;
    while (t[i] != '\0') {
        if (t[i] != '0' && t[i] != '1') {
            printf("Not Possible\n");
            return -1;
        }
        if (t[i] == '1') {
            ones_t++;
        }
        i++;
    }
    len_t = i;
    if (len_s != len_t) {
        printf("Not Possible\n");
        return -1;
    }
    if (ones_s != ones_t) {
        printf("Not Possible\n");
        return -1;
    }
    long long swaps = 0;
    for (i = 0; i < len_s; i++) {
        if (s[i] == '1' && t[i] == '0') {
            swaps++;
        }
    }
    return swaps;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }
    long long result = minSwaps(argv[1], argv[2]);
    if (result >= 0) {
        printf("%lld\n", result);
    }
    return 0;
}
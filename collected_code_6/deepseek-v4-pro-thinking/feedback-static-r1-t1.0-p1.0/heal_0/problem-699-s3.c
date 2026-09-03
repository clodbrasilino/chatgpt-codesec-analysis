#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    int ones1 = 0;
    int ones2 = 0;
    int mismatches = 0;

    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }

        if (s1[i] == '1') {
            ++ones1;
        }
        if (s2[i] == '1') {
            ++ones2;
        }
        if (s1[i] != s2[i]) {
            ++mismatches;
        }
    }

    if (ones1 != ones2) {
        return -1;
    }

    return mismatches / 2;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }

    printf("%d\n", minSwaps(argv[1], argv[2]));
    return 0;
}
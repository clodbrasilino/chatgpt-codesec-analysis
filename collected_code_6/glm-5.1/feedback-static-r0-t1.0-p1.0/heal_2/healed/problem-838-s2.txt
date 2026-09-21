#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *s1, const char *s2, size_t max_len) {
    size_t len1 = strnlen(s1, max_len);
    size_t len2 = strnlen(s2, max_len);
    if (len1 != len2 || (len1 == max_len && s1[max_len - 1] != '\0') || (len2 == max_len && s2[max_len - 1] != '\0')) {
        return -1;
    }
    int xy = 0;
    int yx = 0;
    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            xy++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            yx++;
        }
    }
    if ((xy + yx) % 2 != 0) {
        return -1;
    }
    return (xy / 2) + (yx / 2) + (xy % 2) + (yx % 2);
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }
    int result = minSwaps(argv[1], argv[2], 4096);
    if (result == -1) {
        printf("Impossible\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
        return -1;
    }
    int xy = 0;
    int yx = 0;
    for (int i = 0; i < len1; i++) {
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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }
    char *s1 = argv[1];
    char *s2 = argv[2];
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Impossible\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
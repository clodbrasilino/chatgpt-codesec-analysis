#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buff1[1000005];
char buff2[1000005];
char buff3[1000005];

int main(void) {
    int c = scanf("%1000000s %1000000s %1000000s", buff1, buff2, buff3);
    char *s1 = NULL;
    char *s2 = NULL;

    if (c == 3) {
        s1 = buff2;
        s2 = buff3;
    } else if (c == 2) {
        s1 = buff1;
        s2 = buff2;
    } else {
        printf("Not Possible\n");
        return 0;
    }

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        printf("Not Possible\n");
        return 0;
    }

    int m01 = 0;
    int m10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                m01++;
            } else if (s1[i] == '1') {
                m10++;
            } else {
                printf("Not Possible\n");
                return 0;
            }
        }
    }

    if (m01 != m10) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", m01);
    }

    return 0;
}
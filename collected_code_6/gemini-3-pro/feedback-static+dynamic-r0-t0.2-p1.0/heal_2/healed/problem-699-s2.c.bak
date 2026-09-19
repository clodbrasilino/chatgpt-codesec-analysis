#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
    char str1[200005];
    char str2[200005];

    if (scanf("%200000s %200000s", str1, str2) != 2) {
        return 0;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        printf("Not Possible\n");
        return 0;
    }

    int *pos1 = malloc(len1 * sizeof(int));
    int *pos2 = malloc(len2 * sizeof(int));
    if (!pos1 || !pos2) {
        free(pos1);
        free(pos2);
        return 1;
    }

    int c1 = 0;
    int c2 = 0;

    for (int i = 0; i < len1; i++) {
        if (str1[i] == '1') pos1[c1++] = i;
        if (str2[i] == '1') pos2[c2++] = i;
    }

    if (c1 != c2) {
        printf("Not Possible\n");
    } else {
        long long ans = 0;
        for (int i = 0; i < c1; i++) {
            int diff = pos1[i] - pos2[i];
            ans += diff > 0 ? diff : -diff;
        }
        printf("%lld\n", ans);
    }

    free(pos1);
    free(pos2);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(const int *a, const int *b, const int *c, int na, int nb, int nc) {
    int count = 0;
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb && k < nc) {
        if (a[i] == b[j] && b[j] == c[k]) {
            int va = a[i], vb = b[j], vc = c[k];
            int ca = 0, cb = 0, cc = 0;

            while (i < na && a[i] == va) {
                ca++;
                i++;
            }
            while (j < nb && b[j] == vb) {
                cb++;
                j++;
            }
            while (k < nc && c[k] == vc) {
                cc++;
                k++;
            }

            count += ca * cb * cc;
        } else if (a[i] <= b[j] && a[i] <= c[k]) {
            i++;
        } else if (b[j] <= a[i] && b[j] <= c[k]) {
            j++;
        } else {
            k++;
        }
    }

    return count;
}

int main() {
    int a[] = {1, 2, 2, 3, 4};
    int b[] = {2, 2, 3, 5, 6};
    int c[] = {2, 2, 2, 3, 7};

    int na = sizeof(a) / sizeof(a[0]);
    int nb = sizeof(b) / sizeof(b[0]);
    int nc = sizeof(c) / sizeof(c[0]);

    int result = count_same_pairs(a, b, c, na, nb, nc);
    printf("%d\n", result);

    return 0;
}
#include <stdio.h>
#include <string.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *str, int l, int r) {
    if (str == NULL) {
        return;
    }
    
    if (l == r) {
        printf("%s\n", str);
    } else {
        for (int i = l; i <= r; i++) {
            swap((str + l), (str + i));
            permute(str, l + 1, r);
            swap((str + l), (str + i));
        }
    }
}

int main(void) {
    char str[] = "ABC";
    size_t n = 0;
    
    while (n < sizeof(str) && str[n] != '\0') {
        n++;
    }
    
    if (n > 0) {
        permute(str, 0, (int)(n - 1));
    }
    
    return 0;
}
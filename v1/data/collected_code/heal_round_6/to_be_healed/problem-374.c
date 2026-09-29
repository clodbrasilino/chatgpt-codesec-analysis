#include<stdio.h>
#include<string.h>

void swap(char* x, char* y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char* str, int l, int r) {
    int i;
    if (l == r) {
        printf("%s\n", str);
    } else {
        for (i = l; i <= r && str[i]; i++) {
            swap(&str[l], &str[i]);
            permute(str, l + 1, r);
            swap(&str[l], &str[i]);
        }
    }
}

int main() {
    char str[] = "AAB";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(str);
    
    if(n > 0) {
        permute(str, 0, n - 1);
    }
    return 0;
}
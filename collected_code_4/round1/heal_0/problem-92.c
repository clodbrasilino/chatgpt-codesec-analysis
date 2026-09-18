#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool check_undulating(int n) {
    char s[15];
    sprintf(s, "%d", n);
    int len = strlen(s);

    if(len<3) return false;

    for(int i = 2; i < len; i += 2) {
        if(s[i] != s[0]) return false;
    }

    for(int i = 3; i < len; i += 2) {
        if(s[i] != s[1]) return false;
    }

    return s[0] != s[1];
}

int main() {
    int n;
    scanf("%d", &n);
    if(check_undulating(n)) {
        printf("Number is undulating\n");
    } else {
        printf("Number is not undulating\n");
    }
    return 0;
}
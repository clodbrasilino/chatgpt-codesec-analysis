#include <stdio.h>

int match_a_three_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    while (*str) {
        if (str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == 'b') {
            return 1;
        }
        str++;
    }

    return 0;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "xabbby";
    const char *test3 = "abb";
    const char *test4 = "a bbb";
    const char *test5 = NULL;

    int res1 = match_a_three_b(test1);
    int res2 = match_a_three_b(test2);
    int res3 = match_a_three_b(test3);
    int res4 = match_a_three_b(test4);
    int res5 = match_a_three_b(test5);

    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);
    printf("%d\n", res4);
    printf("%d\n", res5);

    return 0;
}
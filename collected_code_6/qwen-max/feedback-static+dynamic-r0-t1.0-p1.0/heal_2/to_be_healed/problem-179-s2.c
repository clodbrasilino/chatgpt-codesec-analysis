#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int* generate_initial_terms(int n, int *len) {
    char s[20];
    sprintf(s, "%d", n);
    *len = strlen(s);
    int* terms = (int*)malloc(*len * sizeof(int));
    for (int i = 0; i < *len; i++) {
        terms[i] = s[i] - '0';
    }
    return terms;
}

bool is_keith_number(int n) {
    int len;
    int* terms = generate_initial_terms(n, &len);
    if (n < 10) {
        free(terms);
        return false;
    }

    while (1) {
        int sum = 0;
        for (int i = 0; i < len; i++) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (sum > INT_MAX - terms[i]) {
                free(terms);
                return false;
            }
            sum += terms[i];
        }
        if (sum > n) {
            free(terms);
            return false;
        } else if (sum == n) {
            free(terms);
            return true;
        }
        for (int i = 0; i < len - 1; ++i) {
            terms[i] = terms[i + 1];
        }
        terms[len - 1] = sum;
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (is_keith_number(num)) {
        printf("%d is a Keith Number.\n", num);
    } else {
        printf("%d is not a Keith Number.\n", num);
    }
    return 0;
}
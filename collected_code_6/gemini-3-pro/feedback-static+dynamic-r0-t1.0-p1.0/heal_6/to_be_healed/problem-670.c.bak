#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected True, got 0
  */

bool has_decreasing_trend(const int *sequence, size_t length) {
    if (sequence == NULL && length > 0) {
        return false;
    }
    
    if (length < 2) {
        return true;
    }

    for (size_t i = 1; i < length; i++) {
        if (sequence[i] >= sequence[i - 1]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int *seq = NULL;
    size_t len = 0;
    size_t cap = 0;
    int val;
    int ch;

    while ((ch = getchar()) != EOF) {
        ungetc(ch, stdin);
        if (scanf("%d", &val) == 1) {
            if (len == cap) {
                cap = cap == 0 ? 16 : cap * 2;
                int *new_seq = realloc(seq, cap * sizeof(int));
                if (!new_seq) {
                    free(seq);
                    return EXIT_FAILURE;
                }
                seq = new_seq;
            }
            seq[len++] = val;
        } else {
            getchar();
        }
    }

    if (has_decreasing_trend(seq, len)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(seq);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Solution;

Solution *find_solution(int a, int b, int n) {
    if (a == 0 && b == 0) {
        return NULL;
    }
    if (a == 0) {
        if (n % b == 0) {
            Solution *s = (Solution *)malloc(sizeof(Solution));
            if (s == NULL) return NULL;
            s->x = 0;
            s->y = n / b;
            return s;
        } else {
            return NULL;
        }
    }
    if (b == 0) {
        if (n % a == 0) {
            Solution *s = (Solution *)malloc(sizeof(Solution));
            if (s == NULL) return NULL;
            s->x = n / a;
            s->y = 0;
            return s;
        } else {
            return NULL;
        }
    }

    for (int x = -n; x <= n; x++) {
        /* Possible weaknesses found:
         *  Condition 'b==0' is always false [knownConditionTrueFalse]
         */
        if (b == 0) continue;
        int y = (n - a * x) / b;
        if (a * x + b * y == n) {
            Solution *s = (Solution *)malloc(sizeof(Solution));
            if (s == NULL) return NULL;
            s->x = x;
            s->y = y;
            return s;
        }
    }

    return NULL;
}

void free_solution(Solution *s) {
    free(s);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:15,execs:8,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);

    Solution *solution = find_solution(a, b, n);
    if (solution != NULL) {
        printf("x: %d, y: %d\n", solution->x, solution->y);
        free_solution(solution);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
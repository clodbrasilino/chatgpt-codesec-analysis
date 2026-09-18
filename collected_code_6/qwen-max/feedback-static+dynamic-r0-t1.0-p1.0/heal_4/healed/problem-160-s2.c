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
            Solution *s = malloc(sizeof(Solution));
            if (s != NULL) {
                s->x = 0;
                s->y = n / b;
                return s;
            }
        }
        return NULL;
    }
    if (b == 0) {
        if (n % a == 0) {
            Solution *s = malloc(sizeof(Solution));
            if (s != NULL) {
                s->x = n / a;
                s->y = 0;
                return s;
            }
        }
        return NULL;
    }

    for (int x = -n; x <= n; x++) {
        int y = (n - a * x);
        if (y % b == 0) {
            Solution *s = malloc(sizeof(Solution));
            if (s != NULL) {
                s->x = x;
                s->y = y / b;
                if (a * s->x + b * s->y == n) {
                    return s;
                }
                free(s);
            }
        }
    }

    return NULL;
}

void free_solution(Solution *s) {
    free(s);
}

int main() {
    int a, b, n;
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    Solution *solution = find_solution(a, b, n);
    if (solution != NULL) {
        printf("x: %d, y: %d\n", solution->x, solution->y);
        free_solution(solution);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
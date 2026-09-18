#include <stdio.h>
#include <math.h>

struct quadratic {
    double a;
    double b;
    double c;
};

int find_solutions(struct quadratic equation) {
    double d = (equation.b * equation.b) - (4 * equation.a * equation.c);
    
    if(d < 0)
        return 0;
    else if(d == 0)
        return 1;
    else
        return 2;
}

int main() {
    struct quadratic equation;
    equation.a = 1;
    equation.b = -3;
    equation.c = 2;
    int solutions = find_solutions(equation);
    printf("Number of solutions: %d\n", solutions);
    return 0;
}
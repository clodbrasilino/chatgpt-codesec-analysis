#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double amplitude;
    double frequency;
    double phase;
    double offset;
} Sinusoid;

typedef struct {
    Sinusoid *components;
    size_t count;
} PeriodicFunction;

PeriodicFunction create_function(size_t count) {
    PeriodicFunction func;
    func.components = (Sinusoid *)malloc(count * sizeof(Sinusoid));
    if (func.components == NULL) {
        func.count = 0;
        return func;
    }
    func.count = count;
    for (size_t i = 0; i < count; i++) {
        func.components[i].amplitude = 0.0;
        func.components[i].frequency = 0.0;
        func.components[i].phase = 0.0;
        func.components[i].offset = 0.0;
    }
    return func;
}

void destroy_function(PeriodicFunction *func) {
    if (func != NULL && func->components != NULL) {
        free(func->components);
        func->components = NULL;
        func->count = 0;
    }
}

double evaluate_function(const PeriodicFunction *func, double t) {
    if (func == NULL || func->components == NULL || func->count == 0) {
        return 0.0;
    }
    double result = 0.0;
    for (size_t i = 0; i < func->count; i++) {
        result += func->components[i].amplitude * sin(2.0 * PI * func->components[i].frequency * t + func->components[i].phase) + func->components[i].offset;
    }
    return result;
}

double find_maximum(const PeriodicFunction *func, double lower_bound, double upper_bound, size_t samples) {
    if (func == NULL || func->components == NULL || func->count == 0 || samples == 0 || upper_bound <= lower_bound) {
        return 0.0;
    }
    double max_value = evaluate_function(func, lower_bound);
    double step = (upper_bound - lower_bound) / (double)samples;
    for (size_t i = 1; i <= samples; i++) {
        double t = lower_bound + i * step;
        double value = evaluate_function(func, t);
        if (value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}

int main(void) {
    PeriodicFunction func = create_function(3);
    if (func.components == NULL) {
        return 1;
    }

    func.components[0].amplitude = 1.0;
    func.components[0].frequency = 1.0;
    func.components[0].phase = 0.0;
    func.components[0].offset = 0.0;

    func.components[1].amplitude = 0.5;
    func.components[1].frequency = 2.0;
    func.components[1].phase = PI / 4.0;
    func.components[1].offset = 0.2;

    func.components[2].amplitude = 0.3;
    func.components[2].frequency = 3.0;
    func.components[2].phase = PI / 2.0;
    func.components[2].offset = -0.1;

    double max_val = find_maximum(&func, 0.0, 2.0 * PI, 10000);
    printf("%.6f\n", max_val);

    destroy_function(&func);
    return 0;
}
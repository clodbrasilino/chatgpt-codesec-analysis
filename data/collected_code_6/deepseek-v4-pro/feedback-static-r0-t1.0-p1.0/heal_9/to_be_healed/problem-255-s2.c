#include <stdio.h>
#include <stdlib.h>

void generate_combinations(char **colours, int colour_count, int choose_count, char **current, int current_size, int start) {
    if (current_size == choose_count) {
        for (int i = 0; i < choose_count; i++) {
            printf("%s", current[i]);
            if (i < choose_count - 1) printf(" ");
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= colour_count - choose_count + current_size; i++) {
        current[current_size] = colours[i];
        generate_combinations(colours, colour_count, choose_count, current, current_size + 1, i + 1);
    }
}

int main(void) {
    char *colours[] = {"Red", "Green", "Blue"};
    /* Possible weaknesses found:
     *  Assignment 'choose_count=2', assigned value is 2
     */
    int choose_count = 2;
    /* Possible weaknesses found:
     *  Assignment 'colour_count=(int)(sizeof(colours)/sizeof(colours[0]))', assigned value is 3
     */
    int colour_count = (int)(sizeof(colours) / sizeof(colours[0]));

    /* Possible weaknesses found:
     *  Condition 'choose_count<=0' is always false [knownConditionTrueFalse]
     *  Condition 'colour_count<=0' is always false [knownConditionTrueFalse]
     *  Condition 'choose_count<=0' is always false
     *  Condition 'colour_count<=0' is always false
     *  Condition 'choose_count>colour_count' is always false [knownConditionTrueFalse]
     *  Condition 'choose_count>colour_count' is always false
     */
    if (choose_count <= 0 || colour_count <= 0 || choose_count > colour_count) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }

    char **current = malloc((size_t)choose_count * sizeof(char *));
    if (current == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    generate_combinations(colours, colour_count, choose_count, current, 0, 0);

    free(current);
    return EXIT_SUCCESS;
}
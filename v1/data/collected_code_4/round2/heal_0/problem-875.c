#include<stdio.h>
#include<limits.h>

int find_difference(int first_number, int second_number){
        int result =  first_number - second_number;
        return result > 0 ? result : -result;
}

int find_min_difference(int tuples[][2], size_t length) {
        if(length == 0) {
            return INT_MAX;
        }
        
        int min_difference = find_difference(tuples[0][0], tuples[0][1]);
        
        for(size_t i = 1; i < length; ++i) {
            int difference = find_difference(tuples[i][0], tuples[i][1]);
            if (difference < min_difference) {
                min_difference = difference;
            }
        }
        
        return min_difference;
}

int main() {
        int tuples[][2] = {{3, 7}, {2, 5}, {8, 4}, {6, 9}, {5, 1}};
        size_t length = sizeof(tuples) / sizeof(tuples[0]);

        int min_difference = find_min_difference(tuples, length);

        printf("The smallest difference is: %d\n", min_difference);
        
        return 0;
}
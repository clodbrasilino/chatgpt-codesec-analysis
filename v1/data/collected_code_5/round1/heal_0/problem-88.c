#include <stdio.h>
#include <stdlib.h>

struct itemFrequency {
    int item;
    int count;
};

void getFrequency(int* arr, int n){
    struct itemFrequency* freq_arr = (struct itemFrequency*) malloc(n * sizeof(struct itemFrequency));

    for(int i=0; i<n; i++) {
        freq_arr[i].item = arr[i];
        freq_arr[i].count = 0;
    }

   for(int i=0; i<n; i++) {
        int curr_val = arr[i];

        for(int j=0; j<n; j++) {
            if(freq_arr[j].item == curr_val) {
                freq_arr[j].count += 1;
                break;
            }
        }
    }

    for(int k=0; k<n; k++)
    {
        if(freq_arr[k].count != 0)
        {
            printf("Frequency of %d: %d\n", freq_arr[k].item, freq_arr[k].count);
            int current_item = freq_arr[k].item;
            
            for(int m=k+1; m<n; m++)
            {
                if(freq_arr[m].item == current_item)
                {
                    freq_arr[m].count = 0;
                }
            }
        }
    }

    free(freq_arr);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 3, 4, 5, 2, 3, 4, 5, 2, 3, 2, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    getFrequency(arr, n);

    return 0;
}
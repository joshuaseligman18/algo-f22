#include <stdlib.h>
#include <time.h>
#include <string>

#include "sortsAndShuffles.h"
#include "util.h"

int selectionSort(StringArr* data) {
    // Start comparisons at 0
    int comparisons = 0;

    // Iterate through the second to last element because the last element will already be sorted as is
    for (int i = 0; i < data->length - 1; i++) {
        // The smallest index is going to start as the start of the subset of the list
        int smallestIndex = i;

        // Iterate through the rest of the list
        for (int j = i + 1; j < data->length; j++) {
            // Compare the current element to the current smallest element in the subset
            if (data->arr[smallestIndex].compare(data->arr[j]) > 0) {
                // If the current element comes first, make it the new smallest element
                smallestIndex = j;
            }
            // Increment comparisons
            comparisons++;
        }

        // Put the smallest index in its respective place
        std::string temp = data->arr[i];
        data->arr[i] = data->arr[smallestIndex];
        data->arr[smallestIndex] = temp;
    }

    // Return the number of comparisons
    return comparisons;
}

int insertionSort(StringArr* data) {
    int comparisons = 0;

    for (int i = 1; i < data->length; i++) {
        std::string cur = data->arr[i];

        int j = i - 1;
        while (j >= 0 && cur.compare(data->arr[j]) < 0) {
            comparisons++;
            data->arr[j + 1] = data->arr[j];
            j--;
        }
        comparisons++;
        data->arr[j + 1] = cur;
    }

    return comparisons;
}

void knuthShuffle(StringArr* data) {
    // Random numbers found at https://cplusplus.com/reference/cstdlib/rand/
    // Initialize the seed for random numbers to be different each time the program is run
    srand(time(NULL));

    for (int i = 0; i < data->length; i++) {
        // Get the random index where 0 <= swapIndex <= data->length - 1
        int swapIndex = rand() % data->length;

        // Swap the data at the respective indices
        std::string temp = data->arr[i];
        data->arr[i] = data->arr[swapIndex];
        data->arr[swapIndex] = temp;
    }
}
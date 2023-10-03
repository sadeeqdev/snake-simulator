#include <stdio.h>

int main()
{
    int numbers[] = {10, 20, 30, 40, 50, 89};     // Predefined array
    int n = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements in the array
    float sum = 0.0, average;

    // Calculate the sum of numbers
    for (int i = 0; i < n; i++)
    {
        sum += numbers[i];
    }

    // Calculate the average
    average = sum / n;

    printf("Average = %.2f\n", average);

    return 0;
}

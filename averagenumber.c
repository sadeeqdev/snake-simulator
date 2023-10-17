#include <stdio.h>

int main()
{
    int totalNumbers;
    double sum = 0.0; // Initialize the sum as a double to store floating-point values.

    // Prompt the user for the total number of numbers.
    printf("Enter the total of numbers:");
    scanf("%d", &totalNumbers);

    int num[totalNumbers]; // Declare an array to store the numbers.

    // Prompt the user to enter the numbers.
    printf("Enter numbers:\n");
    for (int i = 0; i < totalNumbers; i++)
    {
        scanf("%d", &num[i]);
        sum += num[i]; // Calculate the sum as numbers are entered.
    }

    double average = sum / totalNumbers; // Calculate the average using floating-point division.

    // Display the average with two decimal places.
    printf("The average of the provided numbers is %.2lf\n", totalNumbers, average);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char input[1000];
    printf("enter the string: \n");
    scanf("%s", input);

    int inputLength = strlen(input);
    int vowels = 0;
    int consonants = 0;

    for (int i = 0; i < inputLength; ++i)
    {
        char c = tolower(input[i]);
        if (input[i] == 'a' || input[i] == 'e' || input[i] == 'i' || input[i] == 'o' || input[i] == 'u')
        {
            vowels++;
        }
        else
        {
            consonants++;
        }
    }

    printf("Consonants are %d \n", consonants);
    printf("Vowels are %d \n", vowels);

    return 0;
}
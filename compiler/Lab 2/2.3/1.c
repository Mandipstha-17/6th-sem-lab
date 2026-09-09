#include <stdio.h>
#include <stdbool.h>

int main()
{
    char str[100];
    int i, count, choice;
    bool conti = true;

    while (conti)
    {
        i = 0;
        count = 0;

        printf("\nEnter an expression: ");
        scanf("%99s", str);

        while (str[i] != '\0')
        {
            switch (str[i])
            {
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '=':
                    count++;
                    break;

                default:
                    break;
            }

            i++;
        }

        printf("Number of operators = %d\n", count);

        printf("\nDo you want to continue?\n");
        printf("Enter 1 for Yes, 0 for Exit: ");
        scanf("%d", &choice);

        if (choice == 0)
            conti = false;
    }

    return 0;
}
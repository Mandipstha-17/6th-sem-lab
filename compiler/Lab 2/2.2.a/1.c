#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main()
{
    char str[20];
    int i, state, choice;
    bool conti = true;

    while (conti)
    {
        i = 0;
        state = 0;

        printf("\nEnter an identifier: ");
        scanf("%19s", str);

        while (str[i] != '\0')
        {
            switch (state)
            {
                case 0:
                    if (isalpha(str[i]) || str[i] == '_')
                        state = 1;
                    else
                        state = 2;
                    break;

                case 1:
                    if (isalnum(str[i]) || str[i] == '_')
                        state = 1;
                    else
                        state = 2;
                    break;

                case 2:
                    break;
            }

            i++;
        }

        if (state == 1)
            printf("The identifier is valid.\n");
        else
            printf("The identifier is invalid.\n");

        printf("\nDo you want to continue?\n");
        printf("Enter 1 for Yes, 0 for Exit: ");
        scanf("%d", &choice);

        if (choice == 0)
            conti = false;
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

int main()
{
    char str[20];
    int i, state, choice;
    bool conti = true;

    while (conti)
    {
        i = 0;
        state = 0;

        printf("\nEnter a string: ");
        scanf("%19s", str);

        while (str[i] != '\0')
        {
            switch (state)
            {
                case 0:
                    if (str[i] == 'b')
                        state = 1;
                    else
                        state = 4;
                    break;

                case 1:
                    if (str[i] == 'a')
                        state = 2;
                    else
                        state = 4;
                    break;

                case 2:
                    if (str[i] == 'a')
                        state = 3;
                    else
                        state = 4;
                    break;

                case 3:
                    if (str[i] == 'b')
                        state = 3;
                    else
                        state = 4;
                    break;

                case 4:
                    break;
            }

            i++;
        }

        if (state == 3)
            printf("The string is accepted.\n");
        else
            printf("The string is invalid.\n");

        printf("\nDo you want to continue? Enter 1 for Yes, 0 for Exit: ");
        scanf("%d", &choice);

        if (choice == 0)
            conti = false;
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char str[100];
    int i, state, choice;
    bool conti = true;

    while (conti)
    {
        i = 0;
        state = 0;

        printf("\nEnter a comment: ");
        fgets(str, sizeof(str), stdin);

        while (str[i] != '\0' && str[i] != '\n')
        {
            switch (state)
            {
                case 0:
                    if (str[i] == '/')
                        state = 1;
                    else
                        state = 4;
                    break;

                case 1:
                    if (str[i] == '/')
                        state = 2;
                    else if (str[i] == '*')
                        state = 3;
                    else
                        state = 4;
                    break;

                case 2:
                    /* Single-line comment */
                    break;

                case 3:
                    if (str[i] == '*')
                        state = 5;
                    break;

                case 5:
                    if (str[i] == '/')
                        state = 6;
                    else if (str[i] != '*')
                        state = 3;
                    break;

                case 4:
                    break;

                case 6:
                    break;
            }

            i++;
        }

        if (state == 2 || state == 6)
            printf("The comment is valid.\n");
        else
            printf("The comment is invalid.\n");

        printf("\nDo you want to continue?\n");
        printf("Enter 1 for Yes, 0 for Exit: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0)
            conti = false;
    }

    return 0;
}
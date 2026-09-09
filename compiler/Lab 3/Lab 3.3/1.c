
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char lhs[MAX];
char rhs[MAX][100];
char first[26][50];
int n;

/* Add character to FIRST set if not already present */
int add(char set[], char c)
{
    if (!strchr(set, c))
    {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
        return 1;
    }
    return 0;
}

/* Check whether character is a non-terminal */
int isNonTerminal(char c)
{
    return isupper(c);
}

/* Calculate FIRST sets */
void findFirst()
{
    int changed = 1;

    while (changed)
    {
        changed = 0;

        for (int i = 0; i < n; i++)
        {
            int ai = lhs[i] - 'A';

            /*
             * Each alternative is separated by /
             * Example: A=a/$
             */
            char temp[100];
            strcpy(temp, rhs[i]);

            char *alternative = strtok(temp, "/");

            while (alternative != NULL)
            {
                int nullable = 1;

                for (int j = 0; alternative[j] != '\0'; j++)
                {
                    char c = alternative[j];

                    /* Ignore spaces */
                    if (isspace(c))
                        continue;

                    /* Epsilon */
                    if (c == '$')
                    {
                        changed |= add(first[ai], '$');
                        nullable = 1;
                        break;
                    }

                    /* Terminal */
                    if (!isNonTerminal(c))
                    {
                        changed |= add(first[ai], c);
                        nullable = 0;
                        break;
                    }

                    /* Non-terminal */
                    int bi = c - 'A';

                    /* Add FIRST of non-terminal except epsilon */
                    for (int k = 0; first[bi][k] != '\0'; k++)
                    {
                        if (first[bi][k] != '$')
                            changed |= add(first[ai], first[bi][k]);
                    }

                    /*
                     * If this non-terminal cannot produce epsilon,
                     * stop processing this alternative.
                     */
                    if (!strchr(first[bi], '$'))
                    {
                        nullable = 0;
                        break;
                    }
                }

                /*
                 * If every symbol in the alternative can produce
                 * epsilon, add epsilon.
                 */
                if (nullable)
                    changed |= add(first[ai], '$');

                alternative = strtok(NULL, "/");
            }
        }
    }
}

int main()
{
    int i;
    char input[100];
    char choice, c;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter production %d: ", i + 1);
        scanf("%s", input);

        /* Store LHS */
        lhs[i] = input[0];

        /* Find '=' */
        char *token = strchr(input, '=');

        if (token == NULL)
        {
            printf("Invalid production!\n");
            return 1;
        }

        /* Store RHS */
        strcpy(rhs[i], token + 1);
    }

    /* Calculate FIRST */
    findFirst();

    /* Ask user which FIRST to find */
    do
    {
        printf("\nFind FIRST of: ");
        scanf(" %c", &c);

        printf("FIRST(%c) = { ", c);

        if (isNonTerminal(c))
        {
            int index = c - 'A';

            for (i = 0; first[index][i] != '\0'; i++)
            {
                printf("%c ", first[index][i]);
            }
        }
        else
        {
            /* FIRST of a terminal is itself */
            printf("%c", c);
        }

        printf("}\n");

        printf("Press 'y' to continue: ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}


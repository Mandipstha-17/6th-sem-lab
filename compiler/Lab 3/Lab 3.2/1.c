#include <stdio.h>
#include <string.h>
#include <ctype.h>
int n, p, I = 0, j = 0;
char a[10][10], Result[10];
char subResult[20];
void follow(char *Result, char c);
void first(char *Result, char c);
void addToResultSet(char[], char);
int main(){
    int choice;
    char c, ch;
    printf("Enter the no. of productions: ");
    scanf("%d", &n);
    printf("Enter %d productions\nProduction with multiple terms should be given as separate productions:\n", n);
    for (I = 0; I < n; I++)  // Use I here, not i
        scanf("%s", a[I]);
    do{
        printf("Find FOLLOW of '");
        scanf(" %c", &c);
        follow(Result, c);
        printf("FOLLOW(%c) = { ", c);
        for (I = 0; Result[I] != '\0'; I++)
            printf(" %c ", Result[I]);
        printf(" }\n");
        printf("Do you want to continue (Press 1 to continue....)? ");
        scanf("%d", &choice);
    } while (choice == 1);
    return 0;
}
void follow(char *Result, char c){
    int k;
    subResult[0] = '\0';
    Result[0] = '\0';
    if (a[0][0] == c)
        addToResultSet(Result, '$');
    for (I = 0; I < n; I++){
        for (j = 1; j < strlen(a[I]); j++){
            if (a[I][j] == c){
                if (a[I][j + 1] != '\0')
                    first(subResult, a[I][j + 1]);
                if (a[I][j + 1] == '\0' && c != a[I][0])
                    follow(subResult, a[I][0]);
                for (k = 0; subResult[k] != '\0'; k++)
                    addToResultSet(Result, subResult[k]);
            }
        }
    }
}
void first(char *R, char c){
    int k, m;
    if (!isupper(c) && c != '#')
        addToResultSet(R, c);
    for (k = 0; k < n; k++){
        if (a[k][0] == c){
            if (a[k][2] == '#' && c != a[k][0])
                follow(R, a[k][0]);
            else if (!(isupper(a[k][2])) && a[k][2] != '#')
                addToResultSet(R, a[k][2]);
            else
                first(R, a[k][2]);
        }
    }
}
void addToResultSet(char Result[], char val){
    int k;
    for (k = 0; Result[k] != '\0'; k++){
        if (Result[k] == val)
            return;
    }
    Result[k] = val;
    Result[k + 1] = '\0';
}

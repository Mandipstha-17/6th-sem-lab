#include <stdio.h>
#include <string.h>
char op[2], arg1[5], arg2[5], result[5];
int main() {
    FILE *fp1, *fp2;
    fp1 = fopen("input.txt", "r");
    if (fp1 == NULL) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    fp2 = fopen("output.txt", "w");
    if (fp2 == NULL) {
        printf("Error: Could not open output.txt\n");
        fclose(fp1);
        return 1;
    }
    while (fscanf(fp1, "%s%s%s%s", op, arg1, arg2, result) == 4) {
        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "\n MOV R0,%s", arg1);
            fprintf(fp2, "\n ADD R0,%s", arg2);
            fprintf(fp2, "\n MOV %s,R0", result);
        }
        if (strcmp(op, "*") == 0) {
            fprintf(fp2, "\n MOV R0,%s", arg1);
            fprintf(fp2, "\n MUL R0,%s", arg2);
            fprintf(fp2, "\n MOV %s, R0", result);
        }
        if (strcmp(op, "-") == 0) {
            fprintf(fp2, "\n MOV R0,%s", arg1);
            fprintf(fp2, "\n SUB R0,%s", arg2);
            fprintf(fp2, "\n MOV %s,R0", result);
        }
        if (strcmp(op, "/") == 0) {
            fprintf(fp2, "\n MOV R0,%s", arg1);
            fprintf(fp2, "\n DIV R0,%s", arg2);
            fprintf(fp2, "\n MOV %s,R0", result);
        }
        if (strcmp(op, "=") == 0) {
            fprintf(fp2, "\n MOV R0,%s", arg1);
            fprintf(fp2, "\n MOV %s,R0", result);
        }
    }
    fflush(fp2);
    fclose(fp1);
    fclose(fp2);
    printf("Processing complete. Check output.txt\n");
    return 0;
}


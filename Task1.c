#include <stdio.h>
#include <string.h>
#include "linklistHash.h"


static int cmdInputted(char* tokens[], int count, char* fullInput) {
    if (strcmp(tokens[0], "history") == 0) {
        if (count == 1) {
            printHistory();
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("this is NOT a valid FML command.\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "validate") == 0) {
        if (count == 1) {
            validateHistory();
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("this is NOT a valid FML command.\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "quit") == 0) {
        if (count == 1) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("this is NOT a valid FML command.\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "upload") == 0) {
        if (count == 3) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("syntax error: upload <local filename> <remote filename>\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "download") == 0) {
        if (count == 3) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("syntax error: download <local filename> <remote filename>\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "delete") == 0) {
        if (count == 3) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("syntax error: delete <local|remote> <filepath>\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "change") == 0) {
        if (count == 3) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("syntax error: change <local|remote> <filepath>\n");
            return 0;
        }
    }

    if (strcmp(tokens[0], "show") == 0) {
        if (count == 3) {
            printf("this is a valid FML command.\n");
            addHistory(fullInput);
            return 1;
        }
        else {
            printf("syntax error: show <local|remote> <path|files|folders>\n");
            return 0;
        }
    }

    printf("this is NOT a valid FML command.\n");
    return 0;
}

int main(void) {
    char input[maxInp];
    char inputCopy[maxInp];
    char* tokens[10];

    while (1) {
        printf("FML> ");

        if (scanf(" %[^\n]", input) != 1) {
            break;
        }

        // clear leftover newline from stdin
        getchar();

        if (strlen(input) == 0) {
            continue;
        }

        strncpy(inputCopy, input, maxInp - 1);
        inputCopy[maxInp - 1] = '\0';

        int count = 0;
        char* tok = strtok(input, " ");
        while (tok != NULL && count < 10) {
            tokens[count++] = tok;
            tok = strtok(NULL, " ");
        }

        if (count == 0) {
            continue;
        }

        if (cmdInputted(tokens, count, inputCopy)) {
            if (strcmp(tokens[0], "quit") == 0) {
                break;
            }
        }
    }

    printf("bye!!\n");
    return 0;
}
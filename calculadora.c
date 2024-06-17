#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "calculadora.h"

void inciar_Pilha(Pilha *p) {
    p->topo = -1;
}

void iniciar_Pilha_String(PilhaDeStrings *p) {
    p->topo = -1;
}

//============================================================================

int pilha_Vazia(Pilha *p) {
    return p->topo == -1;
}

int pilha_String_Vazia(PilhaDeStrings *p) {
    return p->topo == -1;
}

//============================================================================

int pilha_Cheia(Pilha *p) {
    return p->topo == MAXPILHA - 1;
}

int pilha_String_Cheia(PilhaDeStrings *p) {
    return p->topo == MAXPILHA - 1;
}

//============================================================================

void empilhar(Pilha *p, double valor) {
    if (!pilha_Cheia(p)) {
        p->dados[++(p->topo)] = valor;
    } else {
        printf("A pilha está cheia!\n");
    }
}

void empilharString(PilhaDeStrings *p, char *valor) {
    if (!pilha_String_Cheia(p)) {
        strcpy(p->dados[++(p->topo)], valor);
    } else {
        printf("A pilha está cheia!\n");
    }
}

//============================================================================

double desempilhar(Pilha *p) {
    if (!pilha_Vazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        printf("A pilha está vazia!\n");
        return 0.0;
    }
}

char* desempilharString(PilhaDeStrings *p) {
    if (!pilha_String_Vazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        printf("A pilha está vazia!\n");
        return NULL;
    }
}

//============================================================================

double RPN(const char *expr) {
    Pilha pilha;

    inciar_Pilha(&pilha);

    char exprCopia[MAXEXPRESSAO];

    strcpy(exprCopia, expr);

    char *token = strtok(exprCopia, " ");
    
    while (token != NULL) {

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, atof(token));
        }

        else if (strlen(token) == 1 && strchr("+-*/^", token[0]) != NULL) {

            double b = desempilhar(&pilha);

            double a = desempilhar(&pilha);

            double resultado = 0.0;
            
            switch (token[0]) {

                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': resultado = a / b; break;
                case '^': resultado = pow(a, b); break;
                default: break;

            }
            empilhar(&pilha, resultado);
        }

        else if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {

            double a = desempilhar(&pilha);
            double resultado = 0.0;

            if (strcmp(token, "raiz") == 0) resultado = sqrt(a);

            else if (strcmp(token, "sen") == 0) resultado = sin(a * 3.14 / 180);

            else if (strcmp(token, "cos") == 0) resultado = cos(a * 3.14 / 180);

            else if (strcmp(token, "tg") == 0) resultado = tan(a * 3.14 / 180);

            else if (strcmp(token, "log") == 0) resultado = log10(a);

            empilhar(&pilha, resultado);
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

//============================================================================

char* converter_Prefixa(const char *expr) {

    PilhaDeStrings pilha;

    iniciar_Pilha_String(&pilha);

    char exprCopia[MAXEXPRESSAO];

    strcpy(exprCopia, expr);

    char *token = strtok(exprCopia, " ");

    while (token != NULL) {

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilharString(&pilha, strdup(token));
        }
        else if (strlen(token) == 1 && strchr("+-*/^", token[0]) != NULL) {
            char *b = desempilharString(&pilha);

            char *a = desempilharString(&pilha);

            char resultado[MAXEXPRESSAO];

            snprintf(resultado, sizeof(resultado), "%s %s %s", token, a, b);

            empilharString(&pilha, strdup(resultado));

            free(a);
            free(b);
        }
        token = strtok(NULL, " ");
    }

    char *prefixa = strdup(desempilharString(&pilha));
    return prefixa;
}

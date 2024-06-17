#ifndef CALCULADORA_H
#define CALCULADORA_H

#define MAXPILHA 100
#define MAXEXPRESSAO 100

//=============================================================================

typedef struct {
    double dados[MAXPILHA]; // Expressão pós-fixa
    int topo;
} Pilha;

typedef struct {
    char dados[MAXPILHA][MAXEXPRESSAO]; // Expressão infixa
    int topo;
} PilhaDeStrings;

//=============================================================================

void inciar_Pilha(Pilha *p);

void iniciar_Pilha_String(PilhaDeStrings *p);

int pilha_Vazia(Pilha *p);

int pilha_String_Vazia(PilhaDeStrings *p);

int pilha_Cheia(Pilha *p);

int pilha_String_Cheia(PilhaDeStrings *p);

void empilhar(Pilha *p, double valor);

void empilharString(PilhaDeStrings *p, char *valor);

double desempilhar(Pilha *p);

char* desempilharString(PilhaDeStrings *p);

//=============================================================================

char* converter_Prefixa(const char *expr); // Retorna a forma inFixa de Str (posFixa)

double RPN(const char *expr); // Calcula o valor de Str (na forma posFixa).


#endif

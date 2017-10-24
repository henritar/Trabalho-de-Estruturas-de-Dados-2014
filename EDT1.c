//
//  EDT1.c
//  Estrutura de Dados - Trabalho 1
//  Avaliação de Expressões Aritméticas (forma posfixa)
//
//  Professor: Dr. Eduardo Adilio Pelinson Alchieri.
//
//  Created by Henrique Torres on 03/09/14.
//  Matricula: 11/0013085.
//  UnB - Universidade de Brasília: ICC - Instituto de Ciências Exatas.
//  CiC - Departamento de Ciência da Computação.
//  Copyright (c) 2014 Henrique Torres. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//converte de char para int;
int conv(char a){
    int x;
    
    x=a-'0';
    return x;
}

//declara a pilha;
typedef struct pilha{
    char dado;
    int dado2;
    struct pilha* prox;
}Pilha;


//declara o header;
typedef struct header{
    Pilha* inicio;
    int tamanho;
}Header;

//cria a pilha;
void criapilha (Header *p){
    p->inicio = NULL;
    p->tamanho = 0;
}

//verifica se a pilha está vazia;
int vazia(Header * p){
    if(p->inicio == NULL){
        return 1;
    }
    return 0;
}

//verifica se a fila está vazia;
int vazia_f(Header* p){
    if(p->inicio == NULL){
        return 1;
    }
    return 0;
}

//empilha no topo;
int empilha(char a, int b, Header* p){
    Pilha* topo = (Pilha *)malloc(sizeof(Pilha));
    topo->dado = a;
    topo->dado2 = b;
    topo->prox = p->inicio;
    
    p->inicio = topo;
    p->tamanho++;
    return 0;
}

//cria fila;
int criafila(Header* p){
    p->inicio = NULL;
    p->tamanho = 1;
    return 0;
}

//enfileira;
int enfileira(char a, int b, Header* p){
    Pilha* ini = (Pilha *)malloc(sizeof(Pilha));
    ini->dado = a;
    ini->dado2 = b;
    ini->prox = NULL;
    int i = 1;
    Pilha *aux = p->inicio;
    while(i < p->tamanho){
        aux = aux->prox;
        i++;
    }
    if(p->inicio != NULL){
    aux->prox = ini;
    p->tamanho++;
    }else{
        p->inicio = ini;
    }
    return 0;
}

//desenfileira char;
char desenfileira_c (Header* p){
    if(vazia_f(p)){
        return 0;
    }
    char aux = p->inicio->dado;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    return aux;
}

//desenfileira int;
int desenfileira_i (Header* p){
    if(vazia_f(p)){
        return 0;
    }
    int aux = p->inicio->dado2;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    if(p->tamanho == 0){
        p->inicio = NULL;
    }
    return aux;
}


//desempilha char topo;
char desempilha (Header* p){
    if(vazia(p)){
        return 0;
    }
    char aux = p->inicio->dado;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
        if(p->tamanho == 0){
            p->inicio = NULL;
        }
    return aux;
}

//desempilha int topo;
int desempilha_i (Header* p){
    if(vazia(p)){
        return 0;
    }
    int aux = p->inicio->dado2;
    Pilha* elemento = p->inicio;
    p->inicio = p->inicio->prox;
    p->tamanho--;
    free(elemento);
    if(p->tamanho == 0){
        p->inicio = NULL;
    }
    return aux;
}

//libera pilha;
int libera_p (Header* p){
    if(vazia(p)){
        free(p);
        return 0;
    }
    while(p->tamanho > 0){
        Pilha* aux = p->inicio;
        p->inicio = p->inicio->prox;
        free(aux);
        p->tamanho--;
    }
    free(p);
    
    return 0;
}

//libera fila;
int libera_f(Header* p){
    if(vazia_f(p)){
        free(p);
        return 0;
    }
    while(p->tamanho > 1){
        Pilha* aux = p->inicio;
        p->inicio = p->inicio->prox;
        free(aux);
        p->tamanho--;
    }
    free(p);
    
    return 0;
}

/* FIM DAS DECLARAÇÕES */

//PASSO 3.1// Entrada e saída de dados//

int main(){
    char entrada[100];
    int i = 0;
    
    //Lê uma equação dada por meio do console;
    scanf("%c", &entrada[i]);
    while(entrada[i] != '\n'){
        i++;
        scanf("%c", &entrada[i]);
    }
    
    //(PRINTAR A EQUAÇÃO DADA PARA VISUALIZAÇÃO)//
    int j = 0;
    printf("A equacao de entrada eh: ");
    while(j != i){
        printf("%c", entrada[j]);
        j++;
    }
    printf("\n");
    
    
    //**VETOR CRIADO**//
    
    //PASSO 3.2// Validação da expressão//
    
    Header* head = (Header *)(malloc(sizeof(Header)));
    
    criapilha(head);
    
    
    for(int k = 0; k < i; k++){
        //empilha os '('
        if(entrada[k] == '('){
            empilha(entrada[k], 0, head);
        }
        //verifica se há '('
        else if(entrada[k] == ')'){
            //caso não exista '(' empilhado, termina a função main;
            if(head->inicio == NULL || head->inicio->dado != '('){
                printf("A expressao eh invalida. Abortando missao! Ha ')' excedentes!\n");
                return 0;
            }
            //caso exista '(' empilhado, desempilha-o;
            else{
                desempilha(head);
            }
        }
    }
    //verifica se sobraram '('. Caso exista, termina a função main;
    if(vazia(head) == 0){
        libera_p(head);
        printf("A expressao eh invalida. Abortando missao! Ha '(' excedentes!\n");
        return 1;
    }
free(head);


//PASSO 3.3// Transformação da forma infixa para posfixa//

Header* header = (Header *)(malloc(sizeof(Header)));
    
criapilha(head);
    
Header* fila = (Header *)malloc(sizeof(Header));

criafila(fila);
    
    int s = 0, numf = 0;
    
    for(int k = 0; k < i; k++){
        
        //empilha o "(";
        if (entrada[k] == '('){
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        
        //verifica a prioridade dos operadores "+" e "-" e os empilha;
        else if(entrada[k] == '+'|| entrada[k] == '-'){
            if(header->inicio != NULL){
                if(header->inicio->dado == '+' || header->inicio->dado == '-' || header->inicio->dado == '*' || header->inicio->dado == '/'){
                    while(header->tamanho > 0){
                    enfileira(desempilha(header), 0, fila);
                    }
                    }
                }
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        //verifica a prioridade dos operadores "*" e "/" e os empilha;
        else if(entrada[k] == '*' || entrada[k] == '/'){
            if(header->inicio != NULL){
            if(header->inicio->dado == '*'|| header->inicio->dado == '/'){
                enfileira(desempilha(header), 0, fila);
                }
            }
            empilha(entrada[k], 0, header);
            numf = 0;
        }
        
        //ao encontrar um ")", desempilha o topo até encontrar um "(" para, então, desempilha-lo;
        else if(entrada[k] == ')'){
                while(header->inicio->dado != '('){
                    enfileira(desempilha(header), 0, fila);
                }
                desempilha(header);
            numf = 0;
        }
        
        //ao encontrar um operando, transforma-o para o tipo "int" e o copia para a expressão de saída;
        else{
            while(entrada[k] == '1'|| entrada[k] == '2'|| entrada[k] == '3'|| entrada[k] == '4'|| entrada[k] == '5'|| entrada[k] == '6' || entrada[k] == '7'|| entrada[k] == '8'|| entrada[k] == '9'|| entrada[k] == '0'){
                s++;
                k++;
            }
            while(s > 0){
            numf+=(conv(entrada[k-s]))*pow(10,s-1);
                s--;
            }
            k--;
            enfileira(0, numf, fila);
        }
        
    }
    while(header->inicio != NULL){
         enfileira(desempilha(header), 0, fila);
    }
    
    //(PRINTAR A EQUAÇÃO NA FORMA POSFIXA PARA VISUALIZAÇÃO)//
    int y = 0;
    Pilha *aux = fila->inicio;
    printf("A equacao de entrada, na sua forma posfixa, eh: ");
    while(y < fila->tamanho){
        if(aux->dado == 0){
            printf("%d", aux->dado2);
        }else{
            printf("%c", aux->dado);
        }
        aux = aux->prox;
        y++;
    }
    printf("\n");
    
    free(header);
    
//PASSO 3.4//Avaliação da expressão//
    
    Header* calc = (Header *)malloc(sizeof(Header));
    criapilha(calc);
    int x, z;
    
    //desenfileira os termos empilhando os operandos. Caso encontrar um operador, realizar as devidas operações;
    while(fila->tamanho > 0){
        
        //empilha os operandos;
        if(fila->inicio->dado == 0){
            empilha(0, desenfileira_i(fila), calc);
        }else{
            
            //desempilha os operandos para realizar sua soma;
            if(fila->inicio->dado == '+'){
                x = desempilha_i(calc);
                z = desempilha_i(calc);
                z = z + x;
                empilha(0, z, calc);
                desenfileira_c(fila);
            }
            
            //desempilha os operandos para realizar sua substração;
            else if(fila->inicio->dado == '-'){
                x = desempilha_i(calc);
                z = desempilha_i(calc);
                z = z - x;
                empilha(0, z, calc);
                desenfileira_c(fila);
            }
            
            //desempilha os operandos para realizar sua multiplicação;
            else if(fila->inicio->dado == '*'){
                x = desempilha_i(calc);
                z = desempilha_i(calc);
                z = z * x;
                empilha(0, z, calc);
                desenfileira_c(fila);
            }
            
            //desempilha os operandos para realizar sua divisão;
            else if(fila->inicio->dado == '/'){
                x = desempilha_i(calc);
                z = desempilha_i(calc);
                z = z / x;
                empilha(0, z, calc);
                desenfileira_c(fila);
            }
        }
    }
    printf("O resultado da operacao dada eh: %d\n", desempilha_i(calc));
    
    return 0;
}


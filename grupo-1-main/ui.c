/**
 * Author: Vitor custódio
 * Date: 09Nov2020
 * Description: Implementação projeto final Algoritmos em C usando estruturas
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


/*##### USER INTERFACE ########*/
/**
 * Escreve no ecrã o menu e retorna a opção escolhida
 * @return int a opção selecionada
 * Esta função faz a avaliação se a opção está correta
 * mas limpa o ecrã antes de retornar
 **/
int menu() {
    char aux[MAX_INPUT];
    memset(aux, '\0', MAX_INPUT);
    printf("##########################################\n"
            "###############   MENU   #################\n"
            "(1) Menu Clientes\n"
            "(2) Menu Contas\n"
            "(3) Menu Movimentos\n"
            "(4) Informação do Banco\n"
            "-------------------\n"
            "(9) Sair da aplicação\n"
            "##########################################\n"
            "Insira a sua opção -> ");
    fgets(aux, MAX_INPUT, stdin);
    //cleanScreen();
    return atoi(aux);
}

/**
 * Escreve no ecrã o menu e retorna a opção escolhida
 * @return int a opção selecionada
 * Esta função nao faz a avaliação se a opção está correta
 * mas limpa o ecrã antes de retornar
 **/
int menuClientes() {
    char aux[MAX_INPUT];
    memset(aux, '\0', MAX_INPUT);
    printf("##########################################\n"
            "##########   MENU CLIENTES   #############\n"
            "(1) Inserir Cliente\n"
            "(2) Listar Clientes\n"
            "(3) Mostrar Cliente\n"
            "(4) Apagar Cliente\n"
            "(5) Procurar Clientes\n"
            "-------------------\n"
            "(9) Menu Principal\n"
            "##########################################\n"
            "Insira a sua opção -> ");
    fgets(aux, MAX_INPUT, stdin);
    //cleanScreen();
    return atoi(aux);
}

int menuContas() {
    char aux[MAX_INPUT];
    memset(aux, '\0', MAX_INPUT);
    printf("##########################################\n"
            "##########    MENU CONTAS    #############\n"
            "(1) Criar Conta\n"
            "(2) Listar Contas Cliente\n"
            "(3) Mostrar Conta Cliente\n"
            "(4) Fechar Conta\n"
            "-------------------\n"
            "(9) Menu Principal\n"
            "##########################################\n"
            "Insira a sua opção -> ");
    fgets(aux, MAX_INPUT, stdin);
    //cleanScreen();
    return atoi(aux);
}

int menuMovimentos() {
    char aux[MAX_INPUT];
    memset(aux, '\0', MAX_INPUT);
    printf("##########################################\n"
            "##########    MENU MOVIMENTOS   #############\n"
            "(1) Depositar Dinheiro\n"
            "(2) Levantar Dinheiro\n"
            "(3) Efetuar Transferência\n"
            "-------------------\n"
            "(9) Menu Principal\n"
            "##########################################\n"
            "Insira a sua opção -> ");
    fgets(aux, MAX_INPUT, stdin);
    //cleanScreen();
    return atoi(aux);
}

/**
 * Pedir uma string ao user (msg) e grava n (max_char)
 * caracteres inseridos pelo user na string de destino (dest)
 * @param dest String de destino
 * @param msg String de prompt ao utilizador
 * @param max_char Número máximo de caracteres a ler
 **/
void pedirString(char *dest, char *msg, int max_char) {
    char aux[MAX_INPUT];
    memset(aux,'\0',MAX_INPUT);
    printf("%s->", msg);
    fgets(aux, MAX_INPUT, stdin);
    strncpy(dest,aux,strlen(aux)-1);
}

/**
 * Pedir um inteiro ao utilizador
 * @param msg String de prompt ao utilizador
 **/
int pedirInteiro(char *msg) {
    char aux[MAX_INPUT];
    memset(aux, '\0', MAX_INPUT);
    printf("%s->", msg);
    fgets(aux, MAX_INPUT, stdin);
    return atoi(aux);
}

/**
 * Pede e devolve um valor de ponto flutuante (Double) ao utilizador
 * @param msg String de prompt ao utilizador
 * @return double inserido pelo utilizador
 **/
double pedirDouble(char *msg) {
    char aux[MAX_INPUT];
    double valor;
    memset(aux, '\0', MAX_INPUT);
    printf("%s->", msg);
    fgets(aux, MAX_INPUT, stdin);
    sscanf(aux, "%lf", &valor);
    return valor;
}

/**
 * Limpa o ecrã
 * Função system da biblioteca stdlib.h
 **/
void cleanScreen() {
    /* Limpa o ecra*/
    system("clear");
}

/**
* Author: Vitor custódio
* Date: 09Nov2020
* Description: Implementa funções de interação com o utilizador
* Projeto final de avaliação de módulo UFCD 0782
**/

/**
 * PROIBIDO ALTERAR ESTA BIBLIOTECA
 **/

#ifndef UI_H
#define UI_H
#define MAX_INPUT 1000 //Máximo input do utilizador
#define INVALID_OPTION printf("Opção Inválida!!!!\n")

/*##### USER INTERFACE ########*/
/**
 * Escreve no ecrã o menu e retorna a opção escolhida
 * @return int a opção selecionada
 **/
int menu();

/**
 * Escreve no ecrã o menu de Clientes e retorna a opção escolhida
 * @return int a opção selecionada
 **/
int menuClientes();

/**
 * Escreve no ecrã o menu de Contas e retorna a opção escolhida
 * @return int a opção selecionada
 **/
int menuContas();

/**
 * Escreve no ecrã o menu de Contas e retorna a opção escolhida
 * @return int a opção selecionada
 **/
int menuMovimentos();

/**
 * Pedir uma string ao user (msg) e grava n (max_char)
 * caracteres inseridos pelo user na string de destino (dest)
 * @param dest String de destino
 * @param msg String de prompt ao utilizador
 * @param max_char Número máximo de caracteres a ler
 **/
void pedirString(char *dest, char *msg, int max_char);

/**
 * Pedir e devolver um inteiro ao utilizador
 * @param msg String de prompt ao utilizador
 * @return inteiro inserido pelo utilizador
 **/
int pedirInteiro(char *msg);

/**
 * Pede e devolve um valor de ponto flutuante (Double) ao utilizador
 * @param msg String de prompt ao utilizador
 * @return double inserido pelo utilizador
 **/
double pedirDouble(char *msg);
/**
 * Limpa o ecrã
 * Função system da biblioteca stdlib.h
 **/
void cleanScreen();

#endif

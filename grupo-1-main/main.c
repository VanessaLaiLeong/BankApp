/**
 * Author: Gustavo Meireles, José Pombo, Tomás Costa, Vanessa Lai Leong
 * Date: 18-07-23
 * Description: Main code where functions are called
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include bibliotecas internas
#include "ui.h"
#include "sgb.h"

/**
 * Process os pedidos no menu Clientes
 * @param banco
 **/
void
processaMenuClientes (Banco *b)
{
  int opt;
  char nome[MAX_NAME], nif[NIF_SIZE];
  while (1)
  {
    opt = menuClientes ();
    switch (opt)
    {
      case 1:
        pedirString (nome, ASK_NAME, MAX_NAME);
        pedirString (nif, ASK_NIF, NIF_SIZE);

        inserirCliente (nome, nif, b);
        break;
      case 2:
        listarCliente (b, b->numero_clientes);
        break;
      case 3:
        mostrarCliente (b);
        break;
      case 4:
        apagarCliente (b);
        break;
      case 5:
        procurarClientes (b);
        break;
      case 9:
        return;		//Sai da função, logo do menu Clientes
      default:
        INVALID_OPTION;
    }
  }
}

/**
 * Process os pedidos no menu Contas
 * @param banco
 **/
void
processaMenuContas (Banco *b)
{
  int opt;

  while (1)
  {
    opt = menuContas ();
    switch (opt)
    {
      case 1:
        criarConta (b);
        break;
      case 2:
        listarContasCliente (b);
        break;
      case 3:
        mostrarContaCliente (b);
        break;
      case 4:
        fecharConta (b);
        break;
      case 9:
        return;		//Sai da função, logo do menu Contas
      default:
        INVALID_OPTION;
    }
  }
}

/**
 * Process os pedidos no meu Clientes
 * @param banco
 **/
void
processaMenuMovimentos (Banco *b)
{
  int opt;
  while (1)
  {
    opt = menuMovimentos ();
    switch (opt)
    {
      case 1:
        depositarDinheiro (b);
        break;
      case 2:
        levantarDinheiro (b);
        break;
      case 3:
        transferirDinheiro (b);
        break;
      case 9:
        return;  //Sai da função, logo do menu Movimentos
      default:
        INVALID_OPTION;
    }
  }
}

int
main (int argc, char const *argv[])
{
  Banco *b;
  int opt;
  b = iniciarBanco ("TPSICAS1022-BANK");
  while (1)
  {
    opt = menu ();
    switch (opt)
    {
      case 1:
        processaMenuClientes (b);
        break;
      case 2:
        processaMenuContas (b);
        break;
      case 3:
        processaMenuMovimentos (b);
        break;
      case 4:
        // printf("Info Banco\n");
        informacaoBanco (b);
        break;
      case 9:
        exit (EXIT_SUCCESS);	//Sai da aplicação
      default:
        INVALID_OPTION;
        break;
    }
  }

  return EXIT_SUCCESS;
}

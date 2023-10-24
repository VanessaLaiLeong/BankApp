/**
 * Author: Gustavo Meireles, José Pombo, Tomás Costa, Vanessa Lai Leong
 * Date: 18-07-23
 * Description: Declaração de funções relativas à gestão bancária
 * Projeto final de avaliação de módulo UFCD 0782
 **/

/**
 * Esta biblioteca deve ser complementada com o vosso código
 **/
#ifndef SGB_H
#define SGB_H
/**
 * ######  Mensagens da Biblioteca ######
 **/
// Mensagens de resposta a pedidos
#include <stdio.h>

#define SHOW_BANK_INFO(NOME, NUM_CLIENTES, NUM_CONTAS, SALDO_TOTAL) printf("####  %s  ####\nClientes: %d\nContas: %d\nValor em Cofre: %.2lf €\n", NOME, NUM_CLIENTES, NUM_CONTAS, SALDO_TOTAL)
#define INSERT_CLIENT_SUCESS(ID, NAME) printf("Cliente %d, %s, inserido com sucesso\n", ID, NAME)
#define LIST_USERS_HEADER(TOTAL_CLIENTS) printf("#######  %d Clientes no Banco  #######\n", TOTAL_CLIENTS)
#define LIST_USERS_ITEM(ID, NIF, NAME, NUM_ACCOUNTS, TOTAL_VALUE) printf("%d - %s - %s - Contas: %d - %.2lf€\n", ID, NIF, NAME, NUM_ACCOUNTS, TOTAL_VALUE)
#define CLIENT_INFO(ID, NAME, NIF, NUM_ACCOUNTS, TOTAL_VALUE) printf("###### INFO CLIENTE: %d ######\nNOME: %s\nNIF: %s\nNUM. CONTAS: %d\nPOSIÇÃO INTEGRADA: %.2lf €\n", ID, NAME, NIF, NUM_ACCOUNTS, TOTAL_VALUE)
#define CLIENT_INFO_ACCOUNTS(ID_CONTA, SALDO) printf("  # Conta Num: %s - Saldo: %.2lf €\n", ID_CONTA, SALDO)
#define CLIENT_INFO_MOVEMENTS(ID_MOV, TIPO, VALOR) printf("   -> Movimento %d - %s : %.2lf €\n", ID_MOV, TIPO, VALOR)
#define CLIENT_DELETE_OK(ID) printf("Cliente %d apagado com sucesso\n", ID)
#define CLIENTS_LOOKUP_FOOTER(NUM_CLIENTS_FOUND, TERMO) printf("# Foram encontrados %d clientes com o termo: %s\n", NUM_CLIENTS_FOUND, TERMO)
#define ACCOUNT_CREATION_SUCESS(ID_ACCOUNT, ID_CLIENT) printf("Conta %s criada com sucesso para o cliente %d\n", ID_ACCOUNT, ID_CLIENT)
#define LIST_ACCOUNTS_HEADER(ID_CLIENT, NAME, TOTAL_VALUE) printf("## Cliente %d : %s : %.2lf € ##\n", ID_CLIENT, NAME, TOTAL_VALUE)
#define ACCOUNT_CLOSE_OK(ID_ACCOUNT, ID_CLIENT) printf("Conta %s pertencente ao cliente %d fechada com sucesso", ID_ACCOUNT, ID_CLIENT)
#define DEPOSIT_OK(VALUE, ID_ACCOUNT) printf("Depósito de %.2lf € efetuado com sucesso na conta %s\n", VALUE, ID_ACCOUNT)
#define WITHDRAW_OK(VALUE, ID_ACCOUNT) printf("Levantamento de %.2lf € efetuado com sucesso da conta %s\n", VALUE, ID_ACCOUNT)
#define TRANSFER_OK(VALUE, ID_ORIGIN, ID_DESTINATION) printf("Transferência de %.2lf € efetuada com sucesso. %s -> %s", VALUE, ID_ORIGIN, ID_DESTINATION)

// Mensagens de Erro
#define INSERT_CLIENT_ERROR_ALREADY_EXISTS(NIF) printf("Erro! Cliente com %s já existe!\n", NIF)
#define INSERT_CLIENT_ERROR_BANK_OVERLOAD printf("Erro! Não há vagas para novos clientes\n")
#define NO_CLIENTS_ERROR printf("Erro! Não existem clientes no banco\n")
#define NO_SUCH_CLIENT_ERROR(ID) printf("Erro! O cliente com o ID %d não existe\n", ID)
#define NO_CLIENTS_FOUND_ERROR(TERMO) printf("Não Foram encontrados clientes através da Pesquisa: %s\n", TERMO)
#define NEW_ACCOUNT_ERROR_CLIENT_OVRELOADED(ID) printf("Erro! O cliente ID %d já não pode possuir mais contas\n", ID)
#define CLIENT_DONT_HAVE_ACCOUNTS(ID) printf("O cliente %d não possui contas\n", ID)
#define NO_SUCH_ACCOUNT_ERROR(ID_CLIENT, ID_ACCOUNT) printf("Erro! O cliente com o ID %d não possuí a conta %s\n", ID_CLIENT, ID_ACCOUNT)
#define WITHDRAWAL_ERROR_NO_FUNDS(ID_CLIENT, ID_ACCOUNT) printf("O cliente %d não possui saldo suficiente na conta %s para a operação solicitada", ID_CLIENT, ID_ACCOUNT)

// Macros com Strings para solicitar dados
#define ASK_NAME "Introduza o nome do Cliente"
#define ASK_NIF "Introduza o NIF do Cliente"
#define ASK_CLIENT_ID "Introduza o ID do cliente"
#define ASK_FIND_TERM "Introduza termo de pesquisa"
#define ASK_ACCOUNT_ID "Introduza o número da conta"
#define ASK_FOR_VALUE "Introduza o valor em €"

/**
 * ###### Modelo de Dados######
 **/
#define MAX_NAME 100
#define CODE_SIZE 4
#define MAX_N_MOVEMENTS 100
#define MAX_N_ACCOUNTS 3
#define MAX_N_CLIENTS 20
#define NIF_SIZE 10

// Tipos de movimentos:
#define MOV_DEPOSIT "DEPOSITO"
#define MOV_TRANSFER "TRANSFERENCIA"
#define MOV_CASHOUT "LEVANTAMENTO"


typedef struct cliente Cliente;
typedef struct conta Conta;
typedef struct movimento Movimento;

// Structures in use:

typedef struct conta {
    double saldo;
    char id[CODE_SIZE];  //identificacao da conta
    Movimento *movimentos[MAX_N_MOVEMENTS];  //movimentos totais da conta
    int numero_movimentos;
} Conta;

typedef struct cliente {
    int id;  //tera de ser gerado automaticamente em quando se criar Conta *paccountConta *paccountConta *paccountnovo cliente contar nr de cliente e soma1
    double posicaoIntegrada;  //saldo intergado de todas as contas
    char *nome;
    char nif[NIF_SIZE];
    Conta *contas[MAX_N_ACCOUNTS];  // maximo de 3 contas por cliente

} Cliente;

typedef struct banco {
    char *nome;
    double saldoTotal;
    int numero_clientes;
    int idCounter;
    Cliente *clientes[MAX_N_CLIENTS];
} Banco;

typedef struct movimento {
    int id;
    char *type;       // 1 -> DEPÓSITO | 2 -> LEVANTAMENTO | 3 -> TRANSFERÊNCIA
    double value;     // valor negativo caso se retire dinheiro da conta e positivo se estamos a adicionar
    Cliente *client;  // Cliente que realiza a transação
    Cliente *clientDestino;
    Conta *conta;
    Conta *contaDestino;
} Movimento;

/**
 * ###### Funções Visíveis no exterior da biblioteca######
 **/

/**
 * Iniciar o banco. Esta função necessita de ser completada pelos alunos
 **/
Banco *iniciarBanco(char *nome);

void inserirCliente(char *nome, char *nif, Banco * b);

void listarCliente(Banco * b, int number_of_clients);

void criarConta(Banco * b);

void fecharConta(Banco * b);

void listarContasCliente(Banco * b);

void mostrarContaCliente(Banco * b);

void depositarDinheiro(Banco * ptrB);

void informacaoBanco(Banco * b);

Cliente *getClientesById(Banco * b, int id);

int getClienteAccountsNumber(Cliente * c);

int getClienteAccountPosition(Cliente * c, char idAccount[CODE_SIZE]);

void levantarDinheiro(Banco * pb);

Conta *getClientAcountById(Banco * b, int clienteId, char *contaId);

void transferirDinheiro(Banco * b);

void sortMovimentosById(Conta * c, int arrayLength);

int verificarExistenciaClientes(Banco * b);

Cliente *checkIdForClient(Banco *b);

void apagarCliente(Banco * b);

void mostrarCliente(Banco * b);

void procurarClientes(Banco * b);

#endif

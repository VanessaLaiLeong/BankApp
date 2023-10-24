/**
 * Author: Gustavo Meireles, José Pombo, Tomás Costa, Vanessa Lai Leong
 * Date: 18-07-23
 * Description: Function implementations for sgb.h
 **/
#include "sgb.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FIX ME - Completar o ficheiro*/

/**
 * Function: iniciarBanco
 * This function creates and initializes a new instance of the 'Banco' structure.
 * @param nome: A string representing the name of the bank.
 * @return: A pointer to the newly created 'Banco' structure.
 */
Banco *iniciarBanco(char *nome)
{
    // Allocate memory for the 'Banco' structure and assign it to 'b'
    Banco *b = malloc(sizeof(Banco));

    // Initialize the bank's total balance to 0.0
    b->saldoTotal = 0.0;

    // Initialize the 'idCounter' to 0, which will be used to assign unique IDs to clients
    b->idCounter = 0;

    // Allocate memory for the bank's name and copy the provided name to it
    b->nome = malloc(strlen(nome) + 1);
    strcpy(b->nome, nome);

    // Initialize the number of clients to 0
    b->numero_clientes = 0;

    // Initialize all positions of the 'clientes' array to NULL
    for (int i = 0; i < MAX_N_CLIENTS; i++) {
        b->clientes[i] = NULL;
    }

    // Return the pointer to the newly created 'Banco' structure
    return b;
}

/**
 * Function: informacaoBanco
 * This function prints the information about a bank, including its name, number of clients,
 * total number of accounts held by those clients, and the total money in the bank.
 * @param b: A pointer to the 'Banco' structure whose information is to be printed.
 */
void informacaoBanco(Banco *b)
{
    int numAccounts = 0;

    // Calculate total number of accounts across all clients
    for (int i = 0; i < b->numero_clientes; i++) {
        // Get the number of accounts held by the current client and add it to 'numAccounts'
        numAccounts += getClienteAccountsNumber(b->clientes[i]);
    }

    // Calculate the total money in the bank across all clients
    for (int i = 0; i < b->numero_clientes; i++) {
        // Add the 'posicaoIntegrada' (integrated position) of the current client
        // to the bank's total balance 'saldoTotal'
        b->saldoTotal += b->clientes[i]->posicaoIntegrada;
    }

    // Display the bank's information using the SHOW_BANK_INFO macro.
    SHOW_BANK_INFO(b->nome, b->numero_clientes, numAccounts, b->saldoTotal);
}

/*
 *  This function returns the number of accounts that a given
 *  client current has;
 * */
int getClienteAccountsNumber(Cliente *c)
{
    int counter = 0;
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] == NULL) {
            continue;
        } else {
            counter++;
        }
    }
    return counter;
}

/**
 * Funcao para verificar se ha clientes no banco
 * @param b Banco
*/
int verificarExistenciaClientes(Banco *b)
{
    if (b->numero_clientes == 0) {
        NO_CLIENTS_ERROR;
        return 0;
    } else {
        return 1;
    }
}

int checkForAccountsOfClient(Cliente *c) {
    if (getClienteAccountsNumber(c) == 0) {
        CLIENT_DONT_HAVE_ACCOUNTS(c->id);
        return 0;
    } else {
        return 1;
    }
}

/**
 * funcao que procura os clientes por id e retorna o cliente
 * @param b Banco
 * @param id Id do cliente
 */

Cliente *getClientesById(Banco *b, int id)
{
    for (int i = 0; i < MAX_N_CLIENTS; i++) {
        if (b->clientes[i] == NULL) {
            continue;
        }
        if (id == b->clientes[i]->id) {
            return b->clientes[i];
        }
    }
    return NULL;
}

// Asks for an id from the user and checks if there is a
// client with that id in the bank.
// If there is a client then returns pointer to that client.
// @return Cliente *client
Cliente *checkIdForClient(Banco *b) {
    Cliente *client;

    // Ask the user to enter the ID of the client they want to view
    int clienteId = pedirInteiro(ASK_CLIENT_ID);

    client = getClientesById(b, clienteId);

    // If no client is found with the given ID, display an error message
    if (client == NULL) {
        NO_SUCH_CLIENT_ERROR(clienteId);
        return NULL;
    }

    return client;
}

Conta *checkForAccount(Banco *b, Cliente *c) {
    Conta *conta;
    char numConta[CODE_SIZE];

    pedirString(numConta, ASK_ACCOUNT_ID, CODE_SIZE);

    // Procurar a conta pelo número
    conta = getClientAcountById(b, c->id, numConta);

    // Verificar se a conta foi encontrada
    if (conta == NULL) {
        NO_SUCH_ACCOUNT_ERROR(c->id, numConta);
        return NULL;
    }

    return conta;
}

/**
 * Funcao para inserir cliente
 * @param nome String do nome do cliente
 * @param nif String do nif do cliente
 * @param b Banco
 **/
void inserirCliente(char *nome, char *nif, Banco *b)
{
    if (b->numero_clientes >= 20) {
        INSERT_CLIENT_ERROR_BANK_OVERLOAD;
        return;
    }

    for (int i = 0; i < MAX_N_CLIENTS; i++) {
        if (b->clientes[i] != NULL
            && strcmp(b->clientes[i]->nif, nif) == 0) {
            INSERT_CLIENT_ERROR_ALREADY_EXISTS(nif);
            return;
        }

        if (b->clientes[i] == NULL) {
            b->clientes[i] = malloc(sizeof(Cliente));	// Allocate memory for b->clientes[i]

            // Dar id ao cliente:
            b->clientes[i]->id = b->idCounter + 1;

            // Dar o nome, nif e saldo ao cliente:

            // Dynamic memory madness:
            b->clientes[i]->nome =
                malloc(sizeof(char) * (strlen(nome) + 1));

            strncpy(b->clientes[i]->nome, nome, strlen(nome));
            b->clientes[i]->nome[strlen(nome)] = '\0';

            // No touch no touching no touchy please:
            strncpy(b->clientes[i]->nif, nif, NIF_SIZE);
            b->clientes[i]->posicaoIntegrada = 0.0;

            for (int j = 0; j < MAX_N_ACCOUNTS; j++) {
                b->clientes[i]->contas[j] = NULL;
            }

            b->idCounter++;
            b->numero_clientes++;

            memset(nome, '\0', MAX_NAME);

            INSERT_CLIENT_SUCESS(b->clientes[i]->id, b->clientes[i]->nome);
            return;
        }
    }
}

/**
 * Compares the names of two clients and returns the value to be used in qsort
 **/
int compare_by_nome(const void *a, const void *b)
{
    const Cliente *cliente_a = *(const Cliente **) a;
    const Cliente *cliente_b = *(const Cliente **) b;
    return strcmp(cliente_a->nome, cliente_b->nome);
}

/**
 * Uses qsort to sort the Clients and then prints them out with a for loop
 * @param *pBank
 * @param number_of_clients
 **/
void listarCliente(Banco *pBank, int number_of_clients)
{
    if (!verificarExistenciaClientes(pBank))
        return;

    int array_size = pBank->numero_clientes;

    qsort(pBank->clientes, array_size, sizeof(Cliente *), compare_by_nome);

    LIST_USERS_HEADER(number_of_clients);

    for (int i = 0; i < number_of_clients; i++) {
        int numberOfAccounts =
            getClienteAccountsNumber(pBank->clientes[i]);

        LIST_USERS_ITEM(pBank->clientes[i]->id, pBank->clientes[i]->nif,
                        pBank->clientes[i]->nome,
                        numberOfAccounts,
                        pBank->clientes[i]->posicaoIntegrada);
    }
}

/**
 * Funcao para criar conta
 * @param b Banco
 * **/
void criarConta(Banco *b)
{
    Cliente *c;
    char contaId[CODE_SIZE];	// Initialize contaId as an array
    int emptySlot = -1;  // Initialize variable to track empty slot

    if (!verificarExistenciaClientes(b))
        return;

    c = checkIdForClient(b);
    if (c == NULL)
        return;

    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] == NULL) {
            emptySlot = i;	// Track the first empty slot found
            break;
        }
    }

    if (emptySlot == -1) {
        NEW_ACCOUNT_ERROR_CLIENT_OVRELOADED(c->id);
        return;
    }

    pedirString(contaId, ASK_ACCOUNT_ID, CODE_SIZE);

    c->contas[emptySlot] = malloc(sizeof(Conta));

    strncpy(c->contas[emptySlot]->id, contaId, CODE_SIZE - 1);
    c->contas[emptySlot]->id[CODE_SIZE - 1] = '\0';	// Ensure null termination
    c->contas[emptySlot]->saldo = 0.0;
    c->contas[emptySlot]->numero_movimentos = 0;

    for (int i = 0; i < MAX_N_MOVEMENTS; i++)
        c->contas[emptySlot]->movimentos[i] = NULL;

    ACCOUNT_CREATION_SUCESS(contaId, c->id);
}

// Comparison to be used with qsort in future functions
int comparar_Ids_Contas(const void *a, const void *b)
{
    const Conta *conta_a = *(const Conta **) a;
    const Conta *conta_b = *(const Conta **) b;
    return strcmp(conta_a->id, conta_b->id);
}

// Sort function for movement id's using the same logic
// implemented above
void sortMovimentosById(Conta *c, int arrayLength)
{
    Movimento *swap;
    for (int i = 0; i < arrayLength - 1; i++) {
        for (int j = 0; j < arrayLength - i - 1; j++) {
            if (c->movimentos[j]->id < c->movimentos[j + 1]->id) {
                swap = c->movimentos[j];
                c->movimentos[j] = c->movimentos[j + 1];
                c->movimentos[j + 1] = swap;
            }
        }
    }
}

/**
 * Funcao para listar contas dos clientes
 * @param b Banco
 */
void listarContasCliente(Banco *b)
{
    Cliente *c;
    int contasCounter = 0;

    if (!verificarExistenciaClientes(b))
        return;

    c = checkIdForClient(b);
    if (c == NULL)
        return;

    contasCounter = getClienteAccountsNumber(c);

    if (!checkForAccountsOfClient(c))
        return;

    qsort(c->contas, contasCounter, sizeof(Conta *), comparar_Ids_Contas);
    LIST_ACCOUNTS_HEADER(c->id, c->nome, c->posicaoIntegrada);

    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] != NULL) {
            int n_movimentos = c->contas[i]->numero_movimentos;
            if (n_movimentos > 0) {
                sortMovimentosById(c->contas[i], n_movimentos);
            }
            CLIENT_INFO_ACCOUNTS(c->contas[i]->id, c->contas[i]->saldo);

            for (int j = 0; j < n_movimentos; j++) {
                Movimento *mov = c->contas[i]->movimentos[j];

                if (mov != NULL) {
                    CLIENT_INFO_MOVEMENTS(mov->id, mov->type, mov->value);
                }
            }
        }
    }
}

// Mostrar Conta Cliente
void mostrarContaCliente(Banco *b)
{
    Conta *conta;
    Cliente *cliente;

    // Verificar se existem clientes no banco
    if (!verificarExistenciaClientes(b))
        return;

    cliente = checkIdForClient(b);
    if (cliente == NULL)
        return;

    if (!checkForAccountsOfClient(cliente))
        return;

    conta = checkForAccount(b, cliente);
    if (conta == NULL)
        return;

    // Listar informações da conta
    LIST_ACCOUNTS_HEADER(cliente->id, cliente->nome,
                         cliente->posicaoIntegrada);
    CLIENT_INFO_ACCOUNTS(conta->id, conta->saldo);

    for (int j = 0; j < conta->numero_movimentos; j++) {
        Movimento *mov = conta->movimentos[j];

        if (mov != NULL) {
            CLIENT_INFO_MOVEMENTS(mov->id, mov->type, mov->value);
        }
    }
}

// Fechar Conta
void fecharConta(Banco *b)
{
    Conta *conta;
    Cliente *cliente;
    char numConta[CODE_SIZE];

    if (!verificarExistenciaClientes(b))
        return;

    cliente = checkIdForClient(b);
    if (cliente == NULL)
        return;

    // Verificar se o cliente possui contas
    if (!checkForAccountsOfClient(cliente))
        return;

    conta = checkForAccount(b, cliente);
    if (conta == NULL)
        return;

    strcpy(numConta, conta->id);
    // Fechar a conta (supondo que o dinheiro foi levantado)
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (cliente->contas[i] != NULL
            && strcmp(cliente->contas[i]->id, numConta) == 0) {
            free(cliente->contas[i]);
            cliente->contas[i] = NULL;
            break;
        }
    }

    ACCOUNT_CLOSE_OK(numConta, cliente->id);
}

/*
 *  Return the position of the account in the accounts array;
 *  If the account doesn't exist:
 *  @return 0;
 * */
int getClienteAccountPosition(Cliente *c, char idAccount[CODE_SIZE])
{
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (strncmp(idAccount, c->contas[i]->id, CODE_SIZE) == 0)
            return i;
    }
    return 0;
}

/*
 *  Create instance of a movement struct;
 *  @param Cliente pointer;
 *  @param Conta of origin;
 *  @param Conta of destiny;
 *  @param type of movement;
 *  @param value of movement;
 * */
void criarMovimento(Cliente *clienteOrigem, Cliente *clienteDestino,
                    Conta *contaOrigem, Conta *contaDestino, char *type,
                    double value)
{
    // Criar movimento da conta origem
    for (int i = 0; i < MAX_N_MOVEMENTS; i++) {
        if (contaOrigem->movimentos[i] == NULL) {

            contaOrigem->movimentos[i] =
                malloc(sizeof(Movimento));

            contaOrigem->numero_movimentos += 1;
            contaOrigem->movimentos[i]->id =
                contaOrigem->numero_movimentos;

            contaOrigem->movimentos[i]->type = malloc(sizeof(type));

            strncpy(contaOrigem->movimentos[i]->type, type, strlen(type) + 1);

            contaOrigem->movimentos[i]->client = clienteOrigem;
            contaOrigem->movimentos[i]->conta = contaOrigem;
            contaOrigem->movimentos[i]->clientDestino = clienteDestino;
            contaOrigem->movimentos[i]->contaDestino = contaDestino;
            contaOrigem->movimentos[i]->value = value;

            // Makes the value negative in case of a transfer
            if (strcmp(type, MOV_TRANSFER) == 0)
                contaOrigem->movimentos[i]->value = -value;

            // avoids seg fault when not doing transfers
            if (contaDestino == NULL && clienteDestino == NULL)
                return;

            break;
        }
    }

    for (int i = 0; i < MAX_N_MOVEMENTS; i++) {
        if (contaDestino->movimentos[i] == NULL) {

            contaDestino->movimentos[i] =
                malloc(sizeof(Movimento));

            contaDestino->numero_movimentos += 1; contaDestino->movimentos[i]->id =
                                                      contaDestino->numero_movimentos;

            contaDestino->movimentos[i]->type =
                malloc(sizeof(type));

            strncpy(contaDestino->movimentos[i]->type,
                    type, strlen(type) + 1);

            contaDestino->movimentos[i]->client = clienteOrigem;
            contaDestino->movimentos[i]->conta = contaOrigem;
            contaDestino->movimentos[i]->clientDestino = clienteDestino;
            contaDestino->movimentos[i]->contaDestino = contaDestino;
            contaDestino->movimentos[i]->value = value;

            break;
        }
    }
}

/**
 * Allows a client to deposit money into their bank account.
 * It prompts the user to provide their client ID, account number, and the
 * amount they wish to deposit. The function then performs various checks to
 * ensure that the deposit can be made. If the client or account is not found,
 * or if there are any issues with the deposit, appropriate error messages
 * are shown. Otherwise, the deposit is executed, and a new transaction (movement)
 * is created to reflect the deposit in the bank's records.
 * @param ptr_b: Pointer to the Banco (bank) structure that holds client and account information.
 */
void depositarDinheiro(Banco *ptr_b)
{
    Cliente *client;
    char idConta[CODE_SIZE];

    if (!verificarExistenciaClientes(ptr_b))
        return;

    client = checkIdForClient(ptr_b);
    if (client == NULL)
        return;

    // Clear the idConta array to make sure it is initialized correctly
    memset(idConta, '\0', CODE_SIZE);

    // Check if the client has any accounts; if not, show an error message and return
    if (!checkForAccountsOfClient(client))
        return;
    // Prompt the user to enter the account number in which they want to make the deposit
    pedirString(idConta, ASK_ACCOUNT_ID, CODE_SIZE);

    // Search for the account with the given account number associated with the client
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (client->contas[i] == NULL)
            continue;

        if (strncmp(idConta, client->contas[i]->id, 3) == 0) {
            // If the account is found, retrieve the account position within the client's array
            int contaPosition = getClienteAccountPosition(client, idConta);

            // Prompt the user to enter the amount they want to deposit
            double valorDeposito = pedirDouble(ASK_FOR_VALUE);

            // Update the integrated position of the client and the balance of the account
            client->posicaoIntegrada += valorDeposito;
            client->contas[contaPosition]->saldo += valorDeposito;

            // Create a new movement (transaction) to reflect the deposit in the bank's records
            criarMovimento(client, NULL, client->contas[contaPosition], NULL, MOV_DEPOSIT, valorDeposito);

            // Show a success message for the deposit and return
            DEPOSIT_OK(valorDeposito, client->contas[contaPosition]->id);
            return;
        } else
            continue;
    }

    NO_SUCH_ACCOUNT_ERROR(client->id, idConta);
    return;
}

/**
 * Allows a client to withdraw money from their bank account.
 * It prompts the user to provide their client ID, account number, and the
 * amount they wish to withdraw. The function then performs various checks to
 * ensure that the withdrawal can be made. If the client or account is not found,
 * or if there are insufficient funds for the withdrawal, appropriate error messages
 * are shown. Otherwise, the withdrawal is executed, and a new transaction (movement)
 * is created to reflect the withdrawal in the bank's records.
 * @param pb: Pointer to the Banco (bank) structure that holds client and account information.
 */
void levantarDinheiro(Banco *pb)
{
    double valor_a_levantar;
    char numeroConta[CODE_SIZE];
    Cliente *cliente;
    Conta *conta;

    if (!verificarExistenciaClientes(pb))
        return;

    cliente = checkIdForClient(pb);
    if (cliente == NULL)
        return;

    // If the client has no accounts, show an error message and return
    if (!checkForAccountsOfClient(cliente))
        return;

    conta = checkForAccount(pb, cliente);
    if (conta == NULL)
        return;
    strcpy(numeroConta, conta->id);

    // Prompt the user to enter the amount they want to withdraw
    valor_a_levantar = pedirDouble(ASK_FOR_VALUE);

    // Check if the account has sufficient funds for the withdrawal; if not, show an error message and return
    if (conta->saldo < valor_a_levantar) {
        WITHDRAWAL_ERROR_NO_FUNDS(cliente->id, numeroConta);
        return;
    }

    // Perform the withdrawal: deduct the amount from the client's integrated position and the account's balance
    cliente->posicaoIntegrada -= valor_a_levantar;
    conta->saldo -= valor_a_levantar;

    // Create a new movement (transaction) to reflect the withdrawal in the bank's records
    criarMovimento(cliente, NULL, conta, NULL, MOV_CASHOUT, -valor_a_levantar);

    WITHDRAW_OK(valor_a_levantar, numeroConta);
    return;
}

/**
 * funcao para procurar Id da conta do cliente
 * @param b Banco
 * @param clienteId id do cliente em questao
 * @param contaId id da conta
 */
Conta *getClientAcountById(Banco *b, int clienteId, char *contaId)
{
    Cliente *c = getClientesById(b, clienteId);

    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] == NULL) {
            continue;
        }
        if (strcmp(contaId, c->contas[i]->id) == 0) {
            return c->contas[i];
        }
    }
    return NULL;
}

/**
 * Funcao para transferir dinheiro
 * Primeiro é pedido os ids dos clientes de origem e de destino
 * Depois da verificação da existência destes clients,
 * é verificado se ambos possuem contas no banco.
 * Depois pedimos ao utilizador a informação do valor a ser transferido
 * e o id da conta de destino e com esta informação, utilizamos a função
 * "criarMovimento" para instanciar um movimento para cada conta
 *
 * @param b Banco
*/
void transferirDinheiro(Banco *b)
{
    Cliente *clienteOrigem;
    Cliente *clienteDestino;
    int clienteIdOrigem;
    int contasCounterOrigin = 0;
    char contaIdOrigem[CODE_SIZE];

    double valor;

    int clienteIdDestino;
    char contaIdDestino[CODE_SIZE];
    int contasCounterDestin = 0;

    // conta origem
    if (!verificarExistenciaClientes(b))
        return;

    clienteOrigem = checkIdForClient(b);
    if (clienteOrigem == NULL)
        return;
    clienteIdOrigem = clienteOrigem->id;

    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (clienteOrigem->contas[i] != NULL)
            contasCounterOrigin++;
    }

    if (contasCounterOrigin == 0) {
        CLIENT_DONT_HAVE_ACCOUNTS(clienteIdOrigem);
        return;
    }

    //pede conta ao cliente
    pedirString(contaIdOrigem, ASK_ACCOUNT_ID, MAX_INPUT);
    Conta *contaOrigem =
        getClientAcountById(b, clienteIdOrigem, contaIdOrigem);

    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (contaOrigem == NULL) {
            NO_SUCH_ACCOUNT_ERROR(clienteIdOrigem, contaIdOrigem);
            return;
        }
    }

    //pedir valor ao cliente origem
    valor = pedirDouble(ASK_FOR_VALUE);
    if (contaOrigem->saldo < valor) {
        WITHDRAWAL_ERROR_NO_FUNDS(clienteIdOrigem, contaIdOrigem);
        return;
    }

    // ========================================conta destino==============================================
    clienteDestino = checkIdForClient(b);
    if (clienteDestino ==NULL)
        return;
    clienteIdDestino = clienteDestino->id;

    // contador de contas
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (clienteDestino->contas[i] != NULL) {
            contasCounterDestin++;
        }
    }
    // cliente nao tem contas
    if (contasCounterDestin == 0) {
        CLIENT_DONT_HAVE_ACCOUNTS(clienteIdDestino);
        return;
    }
    //pede conta ao cliente
    pedirString(contaIdDestino, ASK_ACCOUNT_ID, MAX_INPUT);
    Conta *contaDestino =
        getClientAcountById(b, clienteIdDestino, contaIdDestino);
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (contaDestino == NULL) {
            NO_SUCH_ACCOUNT_ERROR(clienteIdDestino, contaIdDestino);
            return;
        }
    }
    //verificacao de saldo na conta de origem
    if (contaOrigem->saldo < valor) {
        WITHDRAWAL_ERROR_NO_FUNDS(clienteIdOrigem, contaIdOrigem);
    }

    criarMovimento(clienteOrigem, clienteDestino, contaOrigem,
                   contaDestino, MOV_TRANSFER, valor);

    contaOrigem->saldo -= valor;
    contaDestino->saldo += valor;
    clienteOrigem->posicaoIntegrada -= valor;
    clienteDestino->posicaoIntegrada += valor;
    TRANSFER_OK(valor, contaIdOrigem, contaIdDestino);
}

/**
 * Lists all the accounts of a specific client, along with the
 * movements associated with each account. It first checks if the
 * provided client pointer is NULL; if so, the function returns immediately.
 * The function then iterates through the client's accounts to count the number
 * of valid accounts. If there are no valid accounts, the function returns.
 * Otherwise, it sorts the client's accounts based on their IDs. For each account,
 * it lists the account's ID and current balance. If the account has movements,
 * they are sorted based on their IDs and then listed one by one with their IDs,
 * type (credit/debit), and transaction value.
 * @param c: Pointer to the Cliente (client) structure containing account information.
 * @param clientId: ID of the client whose accounts and movements will be listed.
 */
void listarContas(Cliente *c)
{
    int contasCounter = 0;  // Counter for the number of valid accounts

    if (c == NULL)
        return;

    // Iterate through the client's accounts to count the number of valid accounts
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] != NULL)
            contasCounter++;
    }

    // If there are no valid accounts for the client, return from the function
    if (contasCounter == 0)
        return;

    // Sort the client's accounts based on their IDs
    qsort(c->contas, contasCounter, sizeof(Conta *), comparar_Ids_Contas);

    // Iterate through the sorted client's accounts to list account details and movements
    for (int i = 0; i < MAX_N_ACCOUNTS; i++) {
        if (c->contas[i] != NULL) {
            int n_movimentos = c->contas[i]->numero_movimentos;

            // If the account has movements, sort them based on their IDs
            if (n_movimentos > 0)
                sortMovimentosById(c->contas[i], n_movimentos);

            // Display account information (ID and current balance)
            CLIENT_INFO_ACCOUNTS(c->contas[i]->id, c->contas[i]->saldo);

            // Display movements for the current account, if any
            for (int j = 0; j < n_movimentos; j++) {
                Movimento *mov = c->contas[i]->movimentos[j];

                if (mov != NULL)
                    CLIENT_INFO_MOVEMENTS(mov->id, mov->type, mov->value);
            }
        }
    }
}

/**
 * Displays detailed information about a specific client in the bank.
 * It prompts the user to enter the ID of the client to show information for.
 * If the client is found, it displays the client's details, including their accounts,
 * and if no client is found with the given ID or there are no clients in the bank,
 * appropriate error messages are shown.
 * @param b: Pointer to the Banco (bank) structure containing client information.
 */
void mostrarCliente(Banco *b)
{
    int number_of_contas;
    Cliente *client;

    if (!verificarExistenciaClientes(b))    
        return;

    client = checkIdForClient(b);
    if (client == NULL)
        return;

    number_of_contas = getClienteAccountsNumber(client);

    CLIENT_INFO(client->id, client->nome, client->nif, number_of_contas, client->posicaoIntegrada);

    listarContas(client);

    // If the client has no accounts, return from the function
    if (number_of_contas == 0)
        return;
}

/*
 * Shifts the client array on value to the left
 * To be used inside apagarCliente()
 * */
void rotateClientArrayLeft(int numClients, Cliente *array[], int deletePosition)
{
    for (int i = deletePosition; i < MAX_N_CLIENTS - 1; i++) {
        array[i] = array[i + 1];
    }
    array[numClients] = NULL;
}

/**
 * Funcao para apagar o cliente
 * @param b Banco
 * @param num_clientes numero de clientes no banco
 */
void apagarCliente(Banco *b)
{
    Cliente *client;
    int clienteId, currentPosition = 0;

    if (!verificarExistenciaClientes(b))
        return;

    client = checkIdForClient(b);
    if (client == NULL)
        return;

    clienteId = client->id;  // For some reason this stops working without this assignment

    for (int i = 0; i < MAX_N_CLIENTS + 1; i++) {
        if (b->clientes[i] != NULL && b->clientes[i]->id == clienteId) {
            free(b->clientes[i]);
            b->clientes[i] = NULL;
            currentPosition = i;
            CLIENT_DELETE_OK(clienteId);
            b->numero_clientes -= 1;
            rotateClientArrayLeft(b->numero_clientes, b->clientes,
                                  currentPosition);
            break;
        }
    }
}

/**
 * Searches for clients whose names contain a given substring (searchTerm).
 * It then displays the details of the found clients, including their accounts information,
 * sorted by their names in ascending order.
 * @param b: Pointer to the Banco (bank) structure containing client information.
 */
void procurarClientes(Banco *b)
{
    Cliente *foundClient;                          // Pointer to the currently examined client
    char searchTerm[MAX_INPUT];                    // The substring to search for in client names
    Cliente *foundClientsArray[MAX_N_CLIENTS];     // Array to store pointers to found clients
    int numberOfClients = b->numero_clientes;      // Total number of clients in the bank
    int clientsFound = 0;                          // Number of clients found matching the search term
    int numberOfAccounts;                          // Number of accounts for each found client

    // Check if there are no clients in the bank
    if (!verificarExistenciaClientes(b))
        return;

    // Initialize searchTerm and foundClientsArray with null characters
    memset(searchTerm, '\0', MAX_INPUT);
    memset(foundClientsArray, '\0', sizeof(Cliente *) * MAX_N_CLIENTS);

    // Prompt the user to enter the search term (substring)
    pedirString(searchTerm, ASK_FIND_TERM, MAX_INPUT);

    // Loop through all clients to find those whose names contain the search term
    for (int i = 0; i < numberOfClients; i++) {
        foundClient = b->clientes[i];
        
        // Check if the search term (substring) is present in the client's name using strstr function
        if (strstr(foundClient->nome, searchTerm) != NULL) {
            numberOfAccounts = getClienteAccountsNumber(b->clientes[i]);
            foundClientsArray[clientsFound] = foundClient;
            clientsFound++;
        }
    }

    if (clientsFound == 0) {
        NO_CLIENTS_FOUND_ERROR(searchTerm);
        return;
    }

    qsort(foundClientsArray, clientsFound, sizeof(Cliente *), compare_by_nome);

    for (int i = 0; i < clientsFound; i++) {
        foundClient = foundClientsArray[i];
        LIST_USERS_ITEM(foundClient->id, foundClient->nif, foundClient->nome,
                        numberOfAccounts, foundClient->posicaoIntegrada);
    }

    CLIENTS_LOOKUP_FOOTER(clientsFound, searchTerm);
}

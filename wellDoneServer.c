/**
 * @file main.c
 * @author Wellington Wagner F. Sarmento (wwagner@virtual.ufc.br)
 * @brief 
 * @version 0.1
 * @date 2021-09-10
 * 
 * @copyright Copyleft 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* porta do servido */

#define PORT 2424 

/* Tamanho do Buffer */

#define BUFFER_LENGTH 4096

int main(void) {

        /**
     * @brief Programa para teste de socket. Ele imp,emta um protocolo simples de comunicação: 
     * HLO: Cliente verifica disponibilidade do servidor. Se servidornão responder em 20 ms, cliente espera 10 ms e envia novo HLO. Se não responder, cliente encerra tentativas de comunicação. 
     * ACK: Servidor reponde que está livre para receber mensagens.
     * POST: Cliente envia mensagem para servidor. POST <Mensagem>
     * GET: Cliente trás mensagens do servidor. GET
     * BYE: Cliente finaliza comunicação com servidor ou servidor finaliza comunicação com cliente.
     * 
     * 
     * 
     */

    /* Estruturas usadas no para implmentação do servidor */
    struct sockaddr_in server;

    /* Descritor de arquivo do Servidor*/
    int serverfd;

    char buffer[BUFFER_LENGTH];



    


    return 0;
}


/**
 * @file wellDoneServer.c
 * @author Wellington Wagner F. Sarmento (wwagner@virtual.ufc.br)
 * @brief Programa para teste de socket. Ele imp,emta um protocolo simples de comunicação: 
    * WUP: Servidor manda mensagem de boas vindas para o cliente que esta se conectando
    * HLO: Cliente verifica disponibilidade do servidor. Se servidornão responder em 20 ms, cliente espera 10 ms e envia novo HLO. Se não responder, cliente encerra tentativas de comunicação. 
    * ACK: Servidor reponde que está livre para receber mensagens
    * POST: Cliente envia mensagem para servidor. POST <Mensagem>
    * GET: Cliente trás mensagens do servidor. GET
    * BYE: Cliente finaliza comunicação com servidor ou servidor finaliza comunicação com cliente.
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
#define PORT 4242

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096


int main(int argc, char *argv[]) {


    /* Estruturas usadas no para implmentação do servidor */
    struct sockaddr_in server,client;

    /* Descritor de arquivo do Servidor */
    int serverfd,clientfd;

    /* Buffer do socket */
    char buffer[BUFFER_LENGTH];

    fprintf(stdout,"Iniciando o servidor\n");

    /* Cria um Socket IPv4 */

    serverfd=socket(AF_INET,SOCK_STREAM,0);
    if(serverfd == -1){
        perror("Socket nao pode ser criado:");
        return EXIT_FAILURE;
    }

    fprintf(stdout,"Servidor socket criado com fd: %d\n",serverfd);

    /* Definicao das propriedades do servidor socket */
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    memset(server.sin_zero,0x0,8);

    /* Manipulador de erro para o caso da porta ja estar em uso */
    int yes=1;
    if(setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
        perror("Erro de Opcoes do Socket: ");
        return EXIT_FAILURE;
    }

    /* Relaciona (bind) o socket a porta TCP */
    if(bind(serverfd,(struct sockaddr*)&server,sizeof(server)) == -1){
        perror("Erro de relacionando socket a uma porta TCP: ");
        return EXIT_FAILURE;
    }

    /* Inicia a espera por concexoes de clientes */
    if(listen(serverfd,1) == -1){
        perror("Erro escutando porta do socket: ");
        return EXIT_FAILURE;
    }

    fprintf(stdout,"Escutando na porta %d\n",PORT);

    /* Coloca o programa para dormir ate que um cliente estabeleca conexao TCP/IP */
    socklen_t client_len = sizeof(client);
    if((clientfd=accept(serverfd,(struct sockaddr *) &client, &client_len)) == -1){
        perror("Erro no Accept do socket: ");
        return EXIT_FAILURE;
    }

    /*  Copia no buffer a mensagem de boas-vindas do servidor */
    strcpy(buffer,"Servidor manda ola! \n");

    /* Envia a mensagem para o cliente */
    if(send(clientfd,buffer,strlen(buffer),0)){
        fprintf(stdout,"Cliente conectado. \n Esperando mensagens do cliente.\n");
    }

    /* Mantem comunicacao ate que o cliente envia uma mensagem BYE */
    do{
        /* Zera buffer */
        memset(buffer,0x0,BUFFER_LENGTH);

        /* Recebe mensagem do cliente */
        int message_len;
        if((message_len = recv(clientfd,buffer,BUFFER_LENGTH,0)) > 0){
            buffer[message_len-1] = '\0';
            printf("Cliente enviou a mensagem: %s\n",buffer);
        }

        /* Se for enviada a mensagem BYE a conexao e desfeita */
        if(strcmp(buffer,"bye") == 0){
            send(clientfd,"bye",3,0);
        } else {
            send(clientfd,"Mensagem recebida!\n",4,0);
        }

    } while (strcmp(buffer,"BYE"));

    /* Fecha conexao com cliente */
    close(clientfd);

    /* Fecha socket local */
    close(serverfd);
    printf("Conexao fechada!\n\n");
    

    return EXIT_SUCCESS;

}


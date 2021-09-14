/**
 * @file wellDoneClientß.c
 * @author Wellington Wagner F. Sarmento
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
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



/* Definicao da Porta TCP */
#define PORT 4242


/* Tamanho do buffer do socket */
#define LEN 4096


/* Endereco do servidor */
#define SERVER_ADDR "127.0.0.1"


int main(int argc, char *argv[]) {

    /* Socket Server */
    struct sockaddr_in server;

    /* Descritor do arquivo do socket local do cliente */
    int sockfd;

    int len = sizeof(server);
    int slen;

    /* Buffer de recepcao de mensagens */
    char buffer_in[LEN];

    /* Buffer de envio de mensagens */
    char buffer_out[LEN];

    fprintf(stdout,"Iniciando cliente.\n");

    /* Criando socket para o cliente */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("Erro na criacao do socket do cliente:");
        return EXIT_FAILURE;
    }
    fprintf(stdout,"Cliente criado com o descritor de arquivo do socket fd: %d\n",sockfd);

    /* Propriedades de conexao do socket */
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero,0x0,8);

    /* Tenta conectar com o servidor */
    if((connect(sockfd,(struct sockaddr*) &server,len)) == -1){
        perror("Não foi possível conectar com nenhum servidor no endereço fornecido!");
        return EXIT_FAILURE;
    }

    /* Recebe a mensagem de apresentacao do servidor */

    if((slen = recv(sockfd,buffer_in,LEN,0)) > 0){
        buffer_in[slen + 1] = '\0';
        fprintf(stdout,"Servidor enviou a mensagem: %s\n",buffer_in);
    }

    /* Comunicaca-se com o servidor ate que receba uma mensagem BYE de saida da conexao */
    while(true){

        /* Zera os buffers */
        bzero(buffer_in,LEN);
        bzero(buffer_out,LEN);

        fprintf(stdout,"Envie uma mensagem para o servidor: ");
        fgets(buffer_out,len,stdin);

        /* Envia mensagem para o servidor atraves do socket */
        send(sockfd,buffer_out,strlen(buffer_out),0);

        /* Recebe as rmensagens vindas do servidor */
        slen = recv(sockfd,buffer_in,LEN,0);

        /* Se receber a mensagem BYE fara desconexao */
        if(strcmp(buffer_in,"bye") == 0){
            break;
        }
    }

    /* Fecha a conexao com o servidor */
    close(sockfd);
    fprintf(stdout,"\n Conexao com servidor fechada!\n\n");

    return EXIT_SUCCESS;

}
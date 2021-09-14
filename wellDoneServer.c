/**
 * @file      wellDoneServer.c
 * @authors   Wellington Wagner F. Sarmento
 * @copyright Copyleft 2021
 *
 * @brief Servidor Web Simples para fins didaticos
 */
/*******************************************************************************
* Includes
*******************************************************************************/

#include <stdio.h>

#include <stdlib.h> //Biblioteca responsavel por funcoes de manipulacao de memoria.
#include <unistd.h> //Biblioteca de conexao com o Unix ou POSIX system.  A funcao close() esta nela. EXIT_SUCESS e EXIT_Failure estao nela.
#include <string.h> //Biblioteca de manipulacao de strings. A funcao strcmp() e memset() esta nela.
#include <sys/errno.h> //Utilizado na exibicao do erro enviado por funcoes como o setsockopt().

#include <sys/socket.h> //Onde estao definidas todas as funcoes de socket.
#include <netinet/in.h> //Onde esta definida a estrutura sockaddr_in.


/*******************************************************************************
* Defines
*******************************************************************************/

/* porta do servido */
#define PORT 3000

/* Tamanho do Buffer */
#define BUFFER_LENGTH 4096


/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/

/*******************************************************************************
* Functions
*******************************************************************************/


/**
 * @brief Criando um servidor web para fins didaticos usando linguagem C. As partes do servidor são:
 * readRequest(): funcao pra tratar as mensagens de request do cliente
 * writeResponse(): funcao para enviar as mensagens de Response para o Cliente
 * main(): contem o laco de operacao do servidor e cria um processo (depois deve ser convertido em threads) para cada conexao.
 * readHtmlFile(): le um arquiv1o presente em um diretorio e coloca em uma area de memoria para ser enviadeo para o cliente.
 * readImgFile(): le um arquivo de imagem, pdf, etc em um diretorio e coloca em uma area de memoria para ser enviadeo para o cliente.
 * logIt(): cria um log das operacoes de entrada e saida do servidor, bem como de erros.
 * 
 * As principais funcionalidades do servidor serao colocadas no arquivo httpd.c. No arquivo httpd.h serão colocadas as prototipacao de  
 * funcoes e definicao de constantes e estruturas de dados a serem usadas. No arquivo main.c sera colocado o loop do servidor, criado o socket e os processos ou threads.
 * 
 * @return int 
 */


int main(void) {


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

    /**
     * \todo "Melhoria na identificacao de IP Address e disponibilidade de porta antes de criar um Socket." 
     * Ver o uso do getaddrinfo() para retornar o endereco livre e testar se a porta esta ocupada antes de criar o socket.
     * Ver material: https://man7.org/linux/man-pages/man3/getaddrinfo.3.html
     * 
     */

    /* Definicao das propriedades do servidor socket */
    server.sin_family=AF_INET; 
    server.sin_addr.s_addr = htonl(INADDR_ANY); //As funcoes de conversao Host to Network ou Network to Host permitem converter os formatos de bytes para o formato usado no computador, sendo opcionais em maquinas little-endian e obrigatorios em maquinas com big-endian. O "s" no final significa Short (16bits). Se for necessario um inteiro de 32bits, use as mesmas funcoes mas com "l" no final.
    server.sin_port=htons(PORT);
    bzero(server.sin_zero,8); //O sin_zero e para uso do SO

    //memset(server.sin_zero,0x0,8); //Coloca o caracter null "\0" no a primeira posicao da string dada por 

    /* Manipulador de erro para o caso da porta ja estar em uso */
    /** 
     * Uso de setsockopt() para criacao de um socket. Os parametros sao:
     * SOL_SOCKET: Define que o nivel onde sera pesquisado para o socket é o proprio nivel de Socket.
     * SO_REUSEADDR: Permitre o uso de localhost para bind(). Ele peder um valor inteiro de validacao, no caso, dado por yes
     * */
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
    strcpy(buffer,"Servidor manda ola! \n\0");

    /* Envia a mensagem para o cliente */
    if(send(clientfd,buffer,strlen(buffer),0)){
        fprintf(stdout,"Cliente conectado. \n Esperando mensagens do cliente.\n");
    }
/**
 * \todo "Loop principal do servidor"
 * 
 * Fazer o loop principal do servidor com mecanismos de timeout para recepcao de mensagens
 * 
 */
    /* Mantem comunicacao ate que o cliente envia uma mensagem BYE */
    for(;;){
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
            //close(clientfd);
            printf("Conexao fechada!\n\n");
        } else {
            send(clientfd,"Mensagem Recebida!\n",18,0);
        }

    }

    /* Fecha conexao com cliente */


    /* Fecha socket local */
    // close(serverfd);

    

    return EXIT_SUCCESS;

}


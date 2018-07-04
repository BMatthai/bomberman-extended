#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
int main(int argc, char *argv[])
{
       
    int sockfd, newsockfd, portno ,n;
    socklen_t clilen;
    char buffer[256] = "";
    int x =0;
    struct sockaddr_in serv_addr, cli_addr;
     
 
    if (argc < 2)
    {
    fprintf(stderr,"Erreur, Spécifiez le Port\n");
     exit(1);
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
    if (sockfd < 0)
        {
            perror("Erreur d'ouverture du socket");
            exit(1);
        }
     
 
    memset((char *) &serv_addr,0,sizeof(serv_addr));
    portno = atoi(argv[1]);
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
 
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) // attachement de la socket l numero port dial serveur
    {
            perror("Erreur d'association au port");
            exit(1);
    }
     
         
    listen(sockfd,5);//pour indiquer qu'il est disposé à accepter des connexions
 
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
 
    if (newsockfd < 0)
    {
            perror("Erreur d'acceptation");
            exit(1);
    }
 
 
     
 do{ 
    memset(buffer,0,256);
    n = read(newsockfd,buffer,255);
 
    if (n < 0) perror("Erreur de lecture du socket");
    printf("Voici le message que j'ai reçu : %s\n",buffer);
     
    n = write(newsockfd,"J'ai reçu votre message\n",24);
         
 
    if (n < 0)
    {
            perror("Erreur d'écriture dans le socket");
            exit(1);
    }
   
 
  }while(x==1);
return 0;
}

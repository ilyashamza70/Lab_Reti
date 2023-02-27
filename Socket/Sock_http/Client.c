#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg) {
 perror(msg);
 exit(0);
}

int main(int argc, char *argv[]){
 int sockfd, portno, n;
 struct sockaddr_in serv_addr;
 struct hostent *server;
 char buffer[256];
 if (argc < 1) {
	 fprintf(stderr,"usage %s URL\n", argv[0]);
 	exit(0);
 	}
 /* defaul HTTP port */
 portno = 80;
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) 
 	error("ERROR opening socket");
 /* resolve hostname (localhost) */
 server = gethostbyname("localhost");
 if (server == NULL) {
 	fprintf(stderr,"ERROR, no such host\n");
 	exit(0);
 	}
/* server address structure setup */
 bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr, 
 (char *)&serv_addr.sin_addr.s_addr,
 server->h_length);
 serv_addr.sin_port = htons(portno);
 /* connect */
 if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
 	error("ERROR connecting");
 bzero(buffer,256);
 /* send request */
 sprintf(buffer,"GET %s HTTP/1.1\r\nHost: localhost\r\n\r\n",
 argv[1]);
 n = write(sockfd,buffer,strlen(buffer));
 if (n < 0) 
 	error("ERROR writing to socket");
 /* read response (assume len < 255 bytes) */
 bzero(buffer,256);
 n = read(sockfd,buffer,255);
 if (n < 0) 
	 error("ERROR reading from socket");
 printf("%s\n",buffer);
 return 0;
}



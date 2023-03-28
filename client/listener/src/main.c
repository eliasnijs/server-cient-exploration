#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "base/base.h"
#include "base/base.c"

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERV_PORT 8008
/* #define SERV_IP   "38.242.136.102" */
#define SERV_IP   "127.0.0.1"

#define MAXLINE   2048

S32
main(S32 argc, char *argv[])
{
  S32                 sockfd, n; 
  socklen_t           servaddr_size;
  struct sockaddr_in  servaddr;
  char                buf[MAXLINE],
                      *msg = "@";

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
    perror("socket()"); 
    exit(1); 
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family      = AF_INET; 
  servaddr.sin_port        = htons(SERV_PORT); 
  inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);

  sendto(sockfd, msg, strlen(msg), 
         MSG_CONFIRM, (struct sockaddr *) &servaddr,  
         sizeof(servaddr));
 
  for (;;)
  {
    memset(buf, 0, sizeof(buf)); // NOTE(Eias): Clear buffer
    
    servaddr_size = sizeof(servaddr);
    n = recvfrom(sockfd, buf, MAXLINE,  
                 MSG_WAITALL, (struct sockaddr *) &servaddr, 
                 &servaddr_size); 
    
    if (n < 0) {
      perror("n < 0");
      exit(1);
    }
    
    buf[n] = 0;
    printf("%s\n", buf);
  }

  close(sockfd);
  return(0);
}


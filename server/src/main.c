#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "base/base.h"
#include "base/base.c"

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8008
#define MAXLINE 2048

struct Client 
{
  struct sockaddr_in  cliaddr;
  socklen_t           size; 
};

S32
main()
{
  S32 sockfd;
  socklen_t namelen, cliaddr_size;
  struct sockaddr_in server, cliaddr;
  char buf[MAXLINE],
       msg[] = "Hello from UDP Server!";

  // NOTE(Elias): Replace with linked list
  S32 cli_cnt;
  struct Client cliarr[32];

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket()");
    exit(1);
  }

  server.sin_family      = AF_INET;             /* Server is in Internet Domain */
  server.sin_addr.s_addr = htonl(INADDR_ANY);   /* Server's Internet Address   */
  server.sin_port        = htons(PORT);         /* Use any available port      */

  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    perror("bind()");
    exit(2);
  }

  namelen = sizeof(server);
  if (getsockname(sockfd, (struct sockaddr *) &server, &namelen) < 0)
  {
    perror("getsockname()");
    exit(3);
  }
  printf("Port assigned is %d\n", ntohs(server.sin_port));

  printf("Server launched...\n");

  for (;;)
  {
    memset(buf, 0, sizeof(buf)); // NOTE(Eias): Clear buffer
    
    cliaddr_size = sizeof(cliaddr);
    if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &cliaddr,
          &cliaddr_size) < 0)
    {
      perror("recvfrom()");
      exit(4);
    }
    
    if (strcmp(buf, "@") == 0)
    {
      printf("Added new listener: %s:%d \n",
             inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port)); 
      cliarr[cli_cnt].cliaddr = cliaddr; 
      cliarr[cli_cnt].size    = cliaddr_size;
      ++cli_cnt;
    }
    else
    {
      printf("Distributing new msg: %s\n", buf);
      for (S32 i = 0; i < cli_cnt; ++i)
      {
        sendto(sockfd, buf, strlen(buf),  
               MSG_CONFIRM, (struct sockaddr *) &cliarr[i].cliaddr, cliarr[i].size);
      }
    }
  }
  close(sockfd);
}


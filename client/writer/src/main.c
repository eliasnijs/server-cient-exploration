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

internal S32 
strarrl(char *src[], S32 srccnt)
{
  S32 i = 0, l = 0;
  while (i < srccnt)
  {
    l += strlen(src[i]);
    ++i;
  }
  return(l);
}

internal void
strconcat_spaced(char *src[], S32 srccnt, char *dest)
{
  S32 i = 0, offset = 0;
  while (i < srccnt) 
  {
    strcpy(&dest[offset], src[i]);
    offset += strlen(src[i]);
    dest[offset] = ' ';
    ++offset; ++i;
  }
  dest[offset-1] = 0;
}

S32
main(S32 argc, char *argv[])
{
  // NOTE(Elias): msg length + length for spaces in between
  S32  msgl = strarrl(&argv[1], argc-1); 
  char msg[msgl + argc - 1]; 
  memset(msg, 0, sizeof(msg));

  S32                 sockfd, n;
  socklen_t           servaddr_size;
  struct sockaddr_in  servaddr;

  if (argc < 2) 
  {
    printf("%d messages\n", argc-1);
    fprintf(stderr, "No msg was given!\n");
    exit(1); 
  }
  
  strconcat_spaced(&argv[1], argc-1, msg);

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
  { 
    perror("socket()"); 
    exit(1); 
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family      = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(SERV_PORT); 
  
  sendto(sockfd, msg, strlen(msg), 0, 
         (struct sockaddr *) &servaddr,  sizeof(servaddr));
  
  close(sockfd);
  return(0);
}

#include <nds.h>
#include <dswifi9.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

char data[16000];

int main(void) {
  int i;
  for( i = 0; i < 16000; i++ ) {
    data[i] = 'a';
  }
  
	consoleDemoInit();
	iprintf("Wifi init.\n");

	if(!Wifi_InitDefault(WFC_CONNECT)) {
		iprintf("Could not associate.\n");
	}
  else {
    printf( "Wifi init worked.\n" );
    
    struct hostent * host = gethostbyname( "google.com" );
    int port = 80;
    
    struct sockaddr_in sain;
    sain.sin_family = AF_INET;
    sain.sin_port = htons(port);
    sain.sin_addr.s_addr= *( (unsigned long *)(host->h_addr_list[0]) );

    int sockfd;
    sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    
    iprintf( "Connecting to %s port %d\n",
            inet_ntoa( sain.sin_addr ),
            port
           );
    if( connect( sockfd,(struct sockaddr *)&sain, sizeof(sain) ) == 0 ) {
      iprintf("Connection established. Send/recv..\n");
      char* req = "GET / HTTP/1.1\nHost:google.com\n\n";
      send(sockfd, req, strlen(req), 0 );
      char buffer[1024];
      recv (sockfd, buffer, 1024, 0);
      iprintf("Close and new connect\n");
      close( sockfd );
      sockfd = -1;

      // Okay, go
      struct hostent * host2 = gethostbyname( "google.de" );
      sockfd = socket( AF_INET, SOCK_STREAM, 0 );
      struct sockaddr_in sain2;
      sain2.sin_family = AF_INET;
      sain2.sin_port = htons(80);
      sain2.sin_addr.s_addr= *( (unsigned long *)(host2->h_addr_list[0]) );

      if( connect( sockfd,(struct sockaddr *)&sain2, sizeof(sain2) ) == 0 ) {
        iprintf( "Connected again.\n" );

        int bytesleft = 16000;
        int bytessent = 0;
        int n = 0;
        while( bytesleft > 0 ) {
          if ( (n = send(sockfd, data+bytessent, bytesleft, 0)) < 0 ) {
            iprintf( "Send failed!\n" );
            break;
          }
          iprintf( "Sent %d bytes\n", n );
          bytesleft -= n;
          bytessent += n;
        }
      }
      else {
        iprintf( "Failed to connect.\n" );
      }
    }
  }

	while(1) {
		swiWaitForVBlank();
	}

	return 0;
}
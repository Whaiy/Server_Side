#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(){
//  set server-address
    struct sockaddr_in ser_addr; ser_addr.sin_family=AF_INET; inet_aton("127.0.0.1", &ser_addr.sin_addr); ser_addr.sin_port=htons(2333);
// create client-socket-file-descriptor
    int cli_sf=socket(AF_INET, SOCK_STREAM, 0);
// connect to server
    int ser_sf=connect(cli_sf, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
// send msg to server
    printf("send: hey server !\n"); write(cli_sf, "hey server !", 12);
// read msg from server
    char rec_msg[1024]; read(cli_sf, rec_msg,1024);
    printf("recived: %s\n", rec_msg);

	close(ser_sf); close(cli_sf); return 0;
}

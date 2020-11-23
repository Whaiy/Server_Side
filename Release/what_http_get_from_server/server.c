#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){
    int ser_sf, cli_sf;
    struct sockaddr_in ser_addr,cli_addr; ser_addr.sin_family=AF_INET; ser_addr.sin_addr.s_addr=INADDR_ANY; ser_addr.sin_port=htons(2333);
    ser_sf=socket(AF_INET, SOCK_STREAM, 0);
    bind(ser_sf,(struct sockaddr *)&ser_addr, sizeof(ser_addr));
    listen(ser_sf,5);
    socklen_t cli_addr_len = sizeof(cli_addr);
    cli_sf=accept(ser_sf, (struct sockaddr *)&cli_addr, &cli_addr_len);
    
    char rec_msg[1024];
    read(cli_sf,rec_msg,1024); printf("recived:\n%s",rec_msg);
    printf("send: HTTP/1.1 200 OK\r\n\r\n<h1>HELLO WORLD!</h1>");
    write(cli_sf,"HTTP/1.1 200 OK\r\n\r\n<h1>HELLO WORLD!</h1>",1024);

    return 0;
}

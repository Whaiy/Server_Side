#include <stdio.h> // printf();
#include <unistd.h> // provide read(),write()
#include <arpa/inet.h> // provide inet_addr("x.y.z.h") into u_long type, socket.h ...

int main(void){
    int ser_sf, cli_sf;
// set server-address informations
    struct sockaddr_in ser_addr,cli_addr; ser_addr.sin_family=AF_INET; ser_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); ser_addr.sin_port=htons(2333); // ser_addr.sin_addr.s_addr=INADDR_ANY
// create server-socket-file-descriptor
    ser_sf=socket(AF_INET, SOCK_STREAM, 0);
// bind server address
    bind(ser_sf,(struct sockaddr *)&ser_addr, sizeof(ser_addr));
// listen -- wait connection in then run the code under this
    listen(ser_sf,5);
// create client-socket-file-descriptor 
    socklen_t cli_addr_len = sizeof(cli_addr); // long int
    cli_sf=accept(ser_sf, (struct sockaddr *)&cli_addr, &cli_addr_len);
// read & write the client-socket-file-descriptor to transmition msg
    // recive a msg from client
    char rec_msg[1024];
    read(cli_sf,rec_msg,1024); printf("recived: %s\n",rec_msg);
    // send a msg to client
    printf("send: u'v been connected to the server !");
    write(cli_sf,"u'v been connected to the server !",34);

    return 0;
}

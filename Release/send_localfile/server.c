#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>

int main(void){
    int ser_sf, cli_sf;
    struct sockaddr_in ser_addr,cli_addr; ser_addr.sin_family=AF_INET; ser_addr.sin_addr.s_addr=INADDR_ANY; ser_addr.sin_port=htons(2333);
    ser_sf=socket(AF_INET, SOCK_STREAM, 0);
    bind(ser_sf,(struct sockaddr *)&ser_addr, sizeof(ser_addr));
    listen(ser_sf,5);
    socklen_t cli_addr_len = sizeof(cli_addr);
    cli_sf=accept(ser_sf, (struct sockaddr *)&cli_addr, &cli_addr_len);
    
    char rec_msg[1024];memset(rec_msg,0,1023);
    read(cli_sf,rec_msg,1024); printf("recived:\n%s",rec_msg);
    // set header
    char header[]="HTTP/2 200 OK\r\ncontent-type:text/html;charset=utf-8\r\n\r\n"; 
    // set content
    struct stat FS;stat("./index.html",&FS);
    int header_n=strlen(header);
    int msg_len=FS.st_size+header_n-1;
    char content[FS.st_size+1];int fd=open("./index.html",O_RDONLY);read(fd,content,FS.st_size);close(fd);
    // set msg
    char msg[msg_len];sprintf(msg,"%s%s",header,content);
    // send msg
    write(cli_sf,msg,msg_len);

    return 0;
}

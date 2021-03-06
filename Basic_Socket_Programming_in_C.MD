# Write a Server with C Socket



[toc]



## Baisic Server & client

server.c

```c
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
```

client.c

```c
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
```

client.js  : xhr "GET" & "POS"

```js
// run server > open browser tap 127:0.0.1:2333 and check things heppened > restart server run this js code on browser-console and then look what's going on
var POST= (url,tx) => {
    let xhr = new XMLHttpRequest();
    xhr.open("POST",url);
    xhr.send(tx);
    xhr.onload=()=>console.log("recived: ", xhr.responseText);
}
POST("127.0.0.0:2333","Hi server!");
```

[watch this a.href see the anwser](data requested for the first time will be rendered by the browser) 



## Basic Web Server

```c
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
    write(cli_sf,"HTTP/1.1 200 OK\r\n\r\n<h1>HELLO WORLD!</h1>",34);

    return 0;
}
```

start server visit [127.0.0.1:2333](127.0.0.1:2333) as you see the server .c has becom a web server but not so bueatifull ! 



## Send a localfile to client

```c
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
```

As you see this is the socket & htttp basic work flow;  read & write & process string ...

...


#/bin/bash
gcc -Wall -O3 server.c -o server;
gcc -Wall -O3 client.c -o client;
./server;

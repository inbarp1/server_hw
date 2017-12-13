#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("./well known", 0644);
  char[256]priv;
  char[256]final; 
  read("./well known",priv, sizeof(priv));
  write(priv, priv, sizeof(priv));
  read("./well known", final,sizeof(final));
  if(strcmp(final, "success")==0){
    close(0);
  }
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server
  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char priv[]= "./private";
  char from_server[256];
  char message[] = "succees";
  mkfifo(priv, 0644);
  write("./well known", priv, sizeof(priv));
  read(priv,from_server,sizeof(from_server));
  if(strcmp(priv,from_server)== 0){
    write("./well known", message, sizeof(message));
    close(0);
  }
  
  return 0;
}

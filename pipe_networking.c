#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  /* setup*/
  int fd;
  const char * well_known = "./well_known";
  fd = mkfifo(well_known, 0644);
  /*fd = open(well_known, O_WRONLY);
    write(fd, well_known, strlen(well_known) + 1);*/
  char priv[256];
  char final[256];

  /* handshake */
  read(fd,priv, sizeof(priv));
  close(fd);
  const char *operation = "./operation";
  int fd_op = mkfifo(operation,0644);
  int fd_priv= open(priv, O_WRONLY);
  write(fd_priv, operation, strlen(operation)+1);

  /* operation */

  
  read(fd_op, final,sizeof(final));
  if(strcmp(final, "success")==0){
    printf("Succeeded\n");
    close(fd_op);
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
  const char * priv = "./private";
  int fd;
  const char * well_known = "./well_known";
  char from_server[256];
  char message[] = "succees";
  fd = mkfifo(priv, 0644);
  int fd_well = open(well_known, O_WRONLY);
  write(fd_well, priv, sizeof(priv));
  read(fd,from_server,sizeof(from_server));
  close(fd);
  int fd_op = open(from_server, O_WRONLY);
  write(fd_op, message, sizeof(message));
  return 0;
}

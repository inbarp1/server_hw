#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  char buffer[256];

  from_client = server_handshake( &to_client );
  while(read(from_client, buffer, sizeof(buffer))){
    printf("Message recieved: %s", buffer); 
    write(to_client, buffer, sizeof(buffer));
  }
}


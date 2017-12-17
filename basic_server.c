#include "pipe_networking.h"


void process(char * s){
  //Simple process that makes all the string uppercase
  // int x = 0;
  // while(x<strlen(s)){
  //   s[x++] -= 32;
  //}
  int x = 0;
  while(x<strlen(s)){
    if(s[x] == 32){
      s[x] = '_';
    }
    x++;
  }

}
int main() {

  int to_client;
  int from_client;
  char buffer[256];

  while(1){
    from_client = server_handshake( &to_client );
    while(read(from_client, buffer, sizeof(buffer))){
      printf("Message received: %s", buffer);
      process(buffer);
      printf("%s\n", buffer);
      write(to_client, buffer, sizeof(buffer));
    }
  }
}

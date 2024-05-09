#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("Ошибка при создании сокета!");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("Ошибка bind!");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0)
  {
    perror("Ошибка listen!");
    exit(EXIT_FAILURE);
  }

  cout << "Сервер прослушивает порт 8080" << endl;

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
  {
    perror("Ошибка accept!");
    exit(EXIT_FAILURE);
  }

  read(new_socket, buffer, 1024);
  cout << "Ответ: " << buffer << endl;

  close(new_socket);
  close(server_fd);
  return 0;
}

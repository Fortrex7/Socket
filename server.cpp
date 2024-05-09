#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

int main()
{
  const char *socket_path = "/tmp/my_socket";
  int server_fd, client_socket;
  struct sockaddr_un server_addr;

  server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_fd == -1)
  {
    perror("Ошибка при создании сокета!");
    return 1;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, socket_path, sizeof(server_addr.sun_path) - 1);
  unlink(socket_path);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
  {
    perror("Ошибка bind!");
    return 1;
  }

  if (listen(server_fd, 5) == -1)
  {
    perror("Ошибка listen!");
    return 1;
  }

  cout << "Сервер слушает " << socket_path << endl;

  while ((client_socket = accept(server_fd, NULL, NULL)) != -1)
  {
    char buffer[100];
    int num_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (num_read > 0)
    {
      buffer[num_read] = '\0';
      cout << "Ответ: " << buffer << endl;
    }
    close(client_socket);
  }

  close(server_fd);
  unlink(socket_path);
  return 0;
}

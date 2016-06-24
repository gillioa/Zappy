#include	<stdlib.h>
#include	"parse.h"
#include	"map.h"

int	main(int argc, char *argv[])
{
  t_zappy	server;
  int		ret;

  server.game = true;
  release_memory(&server, 0);
  if (init_server(&server))
    return (release_memory(NULL, 1));
  if (fill_opt(argc, argv, &server))
    return (release_memory(NULL, 2));
  if (!(server.map = init_map(server.map, server.width, server.height)))
    return (release_memory(NULL, 3));
  if (!create_socket_TCP(&server))
    return (release_memory(NULL, 4));
  if (init_signal(&server))
    return (release_memory(NULL, 5));
  set_connect_nbr(&server);
  display_info(&server);
  ret = schedule(&server);
  release_memory(NULL, 42);
  return (ret);
}

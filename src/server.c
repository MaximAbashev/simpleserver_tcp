#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SRV_PORT 4444

int main()
{
	int sock, new_sock;
	int from_len;
	char buf[19];
	struct sockaddr_in s_addr, clnt_addr;
/*
 * Initiate socket and fabricate socket options
 */
	sock = socket (AF_INET, SOCK_STREAM, 0);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
	s_addr.sin_port = htons (SRV_PORT);
	bind (sock, (struct sockaddr *)&s_addr, sizeof (s_addr));
	listen (sock, 1);
/*
 * Service loop
 */
	while (1)
	{
		from_len = sizeof (clnt_addr);
		new_sock = accept (sock, &clnt_addr, &from_len);
		write (new_sock, "Who are you?\n", 14);
		from_len = read (new_sock, buf, 19);
		write (1, buf, from_len);
		shutdown (new_sock, 0);
		close (new_sock);
	}
	return 1;
}

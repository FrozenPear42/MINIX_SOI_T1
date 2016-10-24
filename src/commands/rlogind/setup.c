/*
setup.c
*/

#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/netlib.h>
#include <net/gen/in.h>
#include <net/gen/inet.h>
#include <net/gen/tcp.h>
#include <net/gen/tcp_io.h>
#include <net/gen/netdb.h>
#include <net/gen/socket.h>
#include "in.rld.h"

static void getstr(char *buf, int cnt, char *errmsg);

void authenticate(void)
{
	int result;
	struct nwio_tcpconf tcpconf;
	struct hostent *hostent;

	/* Let's lookup the hostname for the connection. */
	result= ioctl (0, NWIOGTCPCONF, &tcpconf);
	if (result<0)
	{
		fprintf(stderr, "%s: ioctl(NWIOTCPCONF): %s\r\n", 
			prog_name, strerror(errno));
		exit(1);
	}
	hostent= gethostbyaddr((char *)&tcpconf.nwtc_remaddr,
		sizeof(tcpconf.nwtc_remaddr), AF_INET);
	if (!hostent)
	{
		printf("Host name for your adress (%s) unknown\r\n",
			inet_ntoa(tcpconf.nwtc_remaddr));
		exit(1);
	}
	strncpy(hostname, hostent->h_name, sizeof(hostname)-1);
	hostname[sizeof(hostname)-1]= '\0';
	authenticated = (do_rlogin() == 0);
}

int do_rlogin(void)
{
	char c;
	struct passwd *pwd;

	getstr(&c, 1, "protocol violation");
	getstr(rusername, sizeof(rusername), "remuser too long");
	getstr(lusername, sizeof(lusername), "locuser too long");
	strcpy(term, "TERM=");
	getstr(term+5, sizeof(term)-5, "Terminal type too long");

#if DEBUG
	fprintf(stderr, "got lu= %s, ru= %s, te= %s\r\n", lusername, rusername,
		term);
#endif
	pwd= getpwnam(lusername);
	if (pwd == NULL)
		return -1;
	return(ruserok(hostname, 0, rusername, lusername));
}

static void getstr(char *buf, int cnt, char *errmsg)
{
	char c;

	errno= 0;
	do
	{
		if (read(0, &c, 1) != 1)
			fatal(1, "read failed", errno);
		cnt--;
		if (cnt < 0)
			fatal(1, errmsg, 0);
		*buf++= c;
	} while(c != 0);
}

void tcp_urg(int fd, int on)
{
	struct nwio_tcpopt tcpopt;

	tcpopt.nwto_flags= on ? (NWTO_BSD_URG | NWTO_SND_URG) : NWTO_SND_NOTURG;
	if (ioctl(1, NWIOSTCPOPT, &tcpopt) == -1)
	{
		fprintf(stderr, "rlogind: NWIOSTCPOPT failed: %s\r\n",
			strerror(errno));
	}
}

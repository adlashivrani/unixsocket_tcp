#include "header.h"

int main()
{
	int cfd;
    char send_buf[SIZE];
    char recv_buf[SIZE];
    struct sockaddr_un sock;

    //Create local socket
   	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd == -1) {
    	printf("Error create socket\n");
      	exit(0);
    }
	printf("socket created successfully...\n");
    //Cleare struct
    memset(&sock, 0, sizeof(struct sockaddr));

   	//Initalization of struct
    sock.sun_family = AF_UNIX;
   	strncpy(sock.sun_path, SOCK_NAME, sizeof(sock.sun_path) - 1);

    if (connect(cfd, (struct sockaddr *) &sock, sizeof(struct sockaddr)) == -1) {
    	printf("Error connect\n");
        exit(0);
        }
	
	printf("\nSocket connected successfully...");
	
    while (1) {
   		printf("\nEnter msg: \n");
        fgets(send_buf, SIZE, stdin);
		write(cfd, send_buf, SIZE);
        read(cfd, recv_buf, SIZE);
       	printf("Server msg: %s\n", recv_buf);
    }

    if (close(cfd) == -1) {
    	printf("Error close \n");
    }

   	return 0;
}

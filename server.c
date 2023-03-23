#include "header.h"

int main()
{
	int sfd;
    int cfd;
    char send_buf[SIZE];
    char recv_buf[SIZE];
    struct sockaddr_un sock;

    //create local socket
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
   		printf("Error create socket\n");
        exit(0);
   	}
	
	printf("Socket created....\n");
    //Clear strcture
    memset(&sock, 0, sizeof(struct sockaddr_un));

    //Intialization socket
    sock.sun_family = AF_UNIX;
    strncpy(sock.sun_path, SOCK_NAME, sizeof(sock.sun_path) - 1);

    //Bind socket to socket name
    if (bind(sfd, (struct sockaddr *) &sock, sizeof(struct sockaddr)) == -1) {
    	printf("Error bind\n");
        exit(0);
    }
	printf("\nSocket binded....\n");
    /* Prepare for accepting connections.
        The backlog size is set to 10.
        So while one request is being processed other request can be waiting. */
    if (listen(sfd, 10) == -1) {
    	printf("Error listen\n");
        exit(0);
    }
	
	printf("\nListening to connection requests...\n");
    /* Wait for incoming connection. */
    cfd = accept(sfd, NULL, NULL);
    if (cfd == -1) {
    	printf("Error accept\n");
        exit(0);
    }

    while (1) {
    	read(cfd, recv_buf, SIZE);
        printf("Clinet msg: %s\n", recv_buf);
		printf("Enter the msg: ");
        fgets(send_buf, SIZE, stdin);
		write(cfd, send_buf, SIZE);
    }

   	//close socket
    if (close(cfd) == -1) {
    	printf("Error close\n");
    }
    if (close(sfd) == -1) {
    	printf("Error close\n");
    }

    return 0;
}

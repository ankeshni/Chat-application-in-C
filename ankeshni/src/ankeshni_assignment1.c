/**
 * @ankeshni_assignment1
 * @author  Ankesh N Bhoi <ankeshni@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */

#include <strings.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



#include "../include/global.h"
#include "../include/logger.h"



//#define SERVER_PORT 5432
#define MAX_LINE 256

//#define SERVER_PORT 4322
#define MAX_PENDING 5
#define MAX_LINE 256

#define BACKLOG 5            // how many pending connections queue will hold
#define STDIN 0
#define TRUE 1
#define CMD_SIZE 100
#define BUFFER_SIZE 256     

#define TRUE 1
#define MSG_SIZE 256
#define BUFFER_SIZE 256

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 i* @return 0 EXIT_SUCCESS
 */

////////////////Shell//////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////Client//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int login_sucess=1;
int connect_to_host(char *server_ip, int server_port)
{
    int fdsocket, len;
    struct sockaddr_in remote_server_addr;

    fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdsocket < 0)
       {
       	perror("Failed to create socket");
       	login_sucess=0;
       }
    bzero(&remote_server_addr, sizeof(remote_server_addr));
    remote_server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
    remote_server_addr.sin_port = htons(server_port);

    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
        {
        	perror("Connect failed");
        	login_sucess=0;
        }
    return fdsocket;
}



char* arg;
int argno;
char* argument[80];
char* cmd;
void tokenize(void)
{

//tokenize input
arg =malloc(100);
argno=0;
argument[80];
cmd=malloc(100);
fgets(cmd,80,stdin);
arg = strtok(cmd," ");
printf ("command read\n");
while(arg!=NULL)
 { argument[argno]=malloc(100);
   strcpy(argument[argno],arg);
   argno+=1;
   arg=strtok(NULL," ");
 }
 strtok(argument[argno-1],"\n"); //removes \n from last argument
 return argument;
}

int server;
int logged_in=0;
char* pc;
void client_shell()
{  while(!logged_in)
 {	
	tokenize();           
    printf ("command parsed\n");
    

    if (!(strcmp(argument[0], "AUTHOR") )||!(strcmp(argument[0], "AUTHOR\n") ))
    { 
	  
	  cse4589_print_and_log("[%s:SUCCESS]\n", argument[0]);
	  cse4589_print_and_log("I, ankeshni, have read and understood the course academic integrity policy.\n");
      cse4589_print_and_log("[%s:END]\n", argument[0]);    
    }

    else if(!(strcmp(argument[0], "IP") )||!(strcmp(argument[0], "IP\n") ))
    { 
      char *server_ip="8.8.8.8";
      int server_port=53;
      struct sockaddr_in remote_server_addr;
	  int ip=1;
      int s = socket(AF_INET, SOCK_DGRAM, 0);
      if(s < 0)
       {
       	perror("Failed to create socket");
       	ip=0;
       }
	    bzero(&remote_server_addr, sizeof(remote_server_addr));
	    remote_server_addr.sin_family = AF_INET;
	    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
	    remote_server_addr.sin_port = htons(server_port);
	  //bind(s, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr));
	  if(connect(s, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
        {
        	perror("Connect failed");
        	ip=0;
        }

        socklen_t foo = sizeof(remote_server_addr);
      if (getsockname(s, (struct sockaddr*)&remote_server_addr, &foo ) <0)
       {
     	 perror("getsockname() failed");
      	 ip=0;
       }
       char myIP[16];

       inet_ntop(AF_INET, &remote_server_addr.sin_addr, myIP, sizeof(myIP));
	   close(s);
     if(ip)
     {
	  cse4589_print_and_log("[%s:SUCCESS]\n", argument[0]);
      cse4589_print_and_log("IP:%s\n",myIP );//inet_ntoa(remote_server_addr.sin_addr));
      cse4589_print_and_log("[%s:END]\n", argument[0]);
     }
      else
       { cse4589_print_and_log("[%s:ERROR]\n", argument[0]);
          cse4589_print_and_log("[%s:END]\n", argument[0]);     
	   }
    }

    else if(!(strcmp(argument[0], "PORT") )||!(strcmp(argument[0], "PORT\n") ))
    {
	  
	  cse4589_print_and_log("[%s:SUCCESS]\n", argument[0]);
	  cse4589_print_and_log("PORT:%d\n", atoi(pc));
      cse4589_print_and_log("[%s:END]\n", argument[0]);

	  
    }

     else if(!(strcmp(argument[0], "LIST") )||!(strcmp(argument[0], "LIST\n") ))
    {
	  //implement
	  
    }

    else if(!(strcmp(argument[0], "LOGIN") )||!(strcmp(argument[0], "LOGIN\n") ))
    {
	  server = connect_to_host(argument[1], atoi(argument[2]));
	  if(login_sucess)
	  {
       	cse4589_print_and_log("[%s:SUCCESS]\n", argument[0]);
	  	logged_in=1;//no output
      	cse4589_print_and_log("[%s:END]\n", argument[0]);
      }
	  
	  else
	  { //login failed
       	cse4589_print_and_log("[%s:ERROR]\n", argument[0]);
      	cse4589_print_and_log("[%s:END]\n", argument[0]);
      }
	  
    } 

    else
    { //if there is any wrong command entered
	  cse4589_print_and_log("[%s:ERROR]\n", argument[0]);
      cse4589_print_and_log("[%s:END]\n", argument[0]);
	 
    }
 }
}




void client(char* port )
{
	pc=port;
client_shell();


	while(TRUE){
		printf("\n[PA1-Client@CSE489/589]$ ");
		fflush(stdout);

		char *msg = (char*) malloc(sizeof(char)*MSG_SIZE);
    	memset(msg, '\0', MSG_SIZE);
		if(fgets(msg, MSG_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to msg
			exit(-1);

		printf("I got: %s(size:%d chars)", msg, strlen(msg));

		printf("\nSENDing it to the remote server ... ");
		if(send(server, msg, strlen(msg), 0) == strlen(msg))
			printf("Done!\n");
		fflush(stdout);

		/* Initialize buffer to receieve response */
        char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
        memset(buffer, '\0', BUFFER_SIZE);

		if(recv(server, buffer, BUFFER_SIZE, 0) >= 0){
			printf("Server responded: %s", buffer);
			fflush(stdout);
		}
	}

}




////////////Server/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* sarg;
int sargno;
char* sargument[80];

void tok(char *scmd)
{
// char* arg;
// int argno;
// char* argument[80];
//char* cmd;
//tokenize input
sarg =malloc(100);
sargno=0;
sargument[80];
//cmd=malloc(100);
//fgets(cmd,80,stdin);
sarg = strtok(scmd," ");
printf ("command read\n");
while(sarg!=NULL)
 { sargument[sargno]=malloc(100);
   strcpy(sargument[sargno],sarg);
   sargno+=1;
   sarg=strtok(NULL," ");
 }
 strtok(sargument[sargno-1],"\n"); //removes \n from last argument
 return sargument;
}

char *ps;
void server_shell(char *cmd)
{
  tok(cmd);
  printf("parsed");

  if (!(strcmp(sargument[0], "AUTHOR") )||!(strcmp(sargument[0], "AUTHOR\n") ))
    { 
	  
	  cse4589_print_and_log("[%s:SUCCESS]\n", sargument[0]);
	  cse4589_print_and_log("I, ankeshni, have read and understood the course academic integrity policy.\n");
      cse4589_print_and_log("[%s:END]\n", sargument[0]);    
    }

    else if(!(strcmp(sargument[0], "IP") )||!(strcmp(sargument[0], "IP\n") ))
    { 
      char *server_ip="8.8.8.8";
      int server_port=53;
      struct sockaddr_in remote_server_addr;
	  int ip=1;
      int s = socket(AF_INET, SOCK_DGRAM, 0);
      if(s < 0)
       {
       	perror("Failed to create socket");
       	ip=0;
       }
	    bzero(&remote_server_addr, sizeof(remote_server_addr));
	    remote_server_addr.sin_family = AF_INET;
	    inet_pton(AF_INET, server_ip, &remote_server_addr.sin_addr);
	    remote_server_addr.sin_port = htons(server_port);
	  //bind(s, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr));
	  if(connect(s, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
        {
        	perror("Connect failed");
        	ip=0;
        }

        socklen_t foo = sizeof(remote_server_addr);
      if (getsockname(s, (struct sockaddr*)&remote_server_addr, &foo ) <0)
       {
     	 perror("getsockname() failed");
      	 ip=0;
       }
       char myIP[16];

       inet_ntop(AF_INET, &remote_server_addr.sin_addr, myIP, sizeof(myIP));
	   close(s);
     if(ip)
     {
	  cse4589_print_and_log("[%s:SUCCESS]\n", sargument[0]);
      cse4589_print_and_log("IP:%s\n",myIP );//inet_ntoa(remote_server_addr.sin_addr));
      cse4589_print_and_log("[%s:END]\n", sargument[0]);
     }
      else
       { cse4589_print_and_log("[%s:ERROR]\n", sargument[0]);
          cse4589_print_and_log("[%s:END]\n", sargument[0]);     
	   }
    }

    else if(!(strcmp(sargument[0], "PORT") )||!(strcmp(sargument[0], "PORT\n") ))
    {
	  
	  cse4589_print_and_log("[%s:SUCCESS]\n", sargument[0]);
	  cse4589_print_and_log("PORT:%d\n", atoi(ps));
      cse4589_print_and_log("[%s:END]\n", sargument[0]);

	  
    }

     else if(!(strcmp(sargument[0], "LIST") )||!(strcmp(sargument[0], "LIST\n") ))
    {
	  //implement
	  
    }
    

    else
    { //if there is any wrong command entered
	  cse4589_print_and_log("[%s:ERROR]\n", argument[0]);
      cse4589_print_and_log("[%s:END]\n", argument[0]);
	 
    }

	
}




void serv(char* prt )
{
	// if(argc != 2) {
	// 	printf("Usage:%s [port]\n", argv[0]);
	// 	exit(-1);
	// }
    ps=prt;
	int port, server_socket, head_socket, selret, sock_index, fdaccept=0, caddr_len;
	struct sockaddr_in server_addr, client_addr;
	fd_set master_list, watch_list;

	/* Socket */
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
		perror("Cannot create socket");

	/* Fill up sockaddr_in struct */
	port = atoi(prt);//atoi(argv[1]);
	bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    /* Bind */
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 )
    	perror("Bind failed");

    /* Listen */
    if(listen(server_socket, BACKLOG) < 0)
    	perror("Unable to listen on port");

    /* ---------------------------------------------------------------------------- */

    /* Zero select FD sets */
    FD_ZERO(&master_list);
    FD_ZERO(&watch_list);
    
    /* Register the listening socket */
    FD_SET(server_socket, &master_list);
    /* Register STDIN */
    FD_SET(STDIN, &master_list);

    head_socket = server_socket;

    while(TRUE){
        memcpy(&watch_list, &master_list, sizeof(master_list));

        //printf("\n[PA1-Server@CSE489/589]$ ");
		//fflush(stdout);

        /* select() system call. This will BLOCK */
        selret = select(head_socket + 1, &watch_list, NULL, NULL, NULL);
        if(selret < 0)
            perror("select failed.");

        /* Check if we have sockets/STDIN to process */
        if(selret > 0){
            /* Loop through socket descriptors to check which ones are ready */
            for(sock_index=0; sock_index<=head_socket; sock_index+=1){

                if(FD_ISSET(sock_index, &watch_list)){

                    /* Check if new command on STDIN */
                    if (sock_index == STDIN){
                    	char *cmd = (char*) malloc(sizeof(char)*CMD_SIZE);

                    	memset(cmd, '\0', CMD_SIZE);
						if(fgets(cmd, CMD_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to cmd
							exit(-1);

						printf("\nI got: %s\n", cmd);
						server_shell(cmd);
						//Process PA1 commands here ...

						free(cmd);
                    }
                    /* Check if new client is requesting connection */
                    else if(sock_index == server_socket){
                        caddr_len = sizeof(client_addr);
                        fdaccept = accept(server_socket, (struct sockaddr *)&client_addr, &caddr_len);
                        if(fdaccept < 0)
                            perror("Accept failed.");

						printf("\nRemote Host connected!\n");                        

                        /* Add to watched socket list */
                        FD_SET(fdaccept, &master_list);
                        if(fdaccept > head_socket) head_socket = fdaccept;
                    }
                    /* Read from existing clients */
                    else{
                        /* Initialize buffer to receieve response */
                        char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                        memset(buffer, '\0', BUFFER_SIZE);

                        if(recv(sock_index, buffer, BUFFER_SIZE, 0) <= 0){
                            close(sock_index);
                            printf("Remote Host terminated connection!\n");

                            /* Remove from watched list */
                            FD_CLR(sock_index, &master_list);
                        }
                        else {
                        	//Process incoming data from existing clients here ...

                        	printf("\nClient sent me: %s\n", buffer);
							printf("ECHOing it back to the remote host ... ");
							if(send(fdaccept, buffer, strlen(buffer), 0) == strlen(buffer))
								printf("Done!\n");
							fflush(stdout);
                        }

                        free(buffer);
                    }
                }
            }
        }
    }
}



//////main/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	/*Init. Logger*/
	cse4589_init_log(argv[2]);

	/*Clear LOGFILE*/
	fclose(fopen(LOGFILE, "w"));

	/*Start Here*/
        /*Creating Socket*/
          
        if(!(strcmp(argv[1], "c") ))
        { // printf("inside first if");
           
     	    
			client(argv[2]);
			
		}
////////////////////////////////////////////////////////////////////////////////////
			
         
     else if(!(strcmp(argv[1], "s") ))
        {
          serv(argv[2]);
    	}
	return 0;

} 


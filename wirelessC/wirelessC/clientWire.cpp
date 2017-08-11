// Client program example
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 
#define DEFAULT_PORT 2007
// TCP socket type
#define DEFAULT_PROTO SOCK_STREAM
 
void Usage(char *progname)
{
    fprintf(stderr,"Usage: %s -p [protocol] -n [server name/IP] -e [port_num] -l [iterations]\n", progname);
    fprintf(stderr,"Where:\n\tprotocol is one of TCP or UDP\n");
    fprintf(stderr,"\t- server is the IP address or name of server\n");
    fprintf(stderr,"\t- port_num is the port to listen on\n");
    fprintf(stderr,"\t- iterations is the number of loops to execute.\n");
    fprintf(stderr,"\t- (-l by itself makes client run in an infinite loop,\n");
    fprintf(stderr,"\t- Hit Ctrl-C to terminate it)\n");
    fprintf(stderr,"\t- The defaults are TCP , localhost and 2007\n");
    WSACleanup();
    exit(1);
}
///mine
char command[100];

void captureCommand();
void displayResult();
void capture_password();

int i;
//mime ends

char *sessionName=""; char sessionNames[20];
char passwrd[15];
void help();

char *replace(char *st, char *orig, char *repl);//metnood
char *separate(char *Whole, char *identifier);
int a;char *another_holder[1024];char *q; int tokens_counter;

char personal_contribution[400];
char *sliced_table[400];
int slicecount;
char *sliced_table_loan[400];
int loan_slicecount;

   int wrongCommandCount=0;

 char Buffer[1024];
    // default to localhost
    char *server_name= "localhost";
    unsigned short port = DEFAULT_PORT;
    int retval, loopflag = 1; //loop =0;
    int i, loopcount, maxloop=-1;
    unsigned int addr;
    int socket_type = DEFAULT_PROTO;
    struct sockaddr_in server;
    struct hostent *hp;
    WSADATA wsaData;
    SOCKET  conn_socket;
int main(int argc, char **argv)
{
    
 
    if (argc >1)
       {
        for(i=1; i<argc; i++)
        {
            if ((argv[i][0] == '-') || (argv[i][0] == '/'))
           {
                switch(tolower(argv[i][1]))
                 {
                    case 'p':
                        if (!stricmp(argv[i+1], "TCP"))
                            socket_type = SOCK_DGRAM;
                        else if (!stricmp(argv[i+1], "UDP"))
                            socket_type = SOCK_STREAM;
                        else
                            Usage(argv[0]);
                        i++;
                        break;
                    case 'n':
                        server_name = argv[++i];
                        break;
                    case 'e':
                        port = atoi(argv[++i]);
                        break;
                    case 'l':
                        loopflag =1;
                        if (argv[i+1]) {
                            if (argv[i+1][0] != '-')
                                maxloop = atoi(argv[i+1]);
                        }
                        else
                            maxloop = -1;
                        i++; 
                        break;
                    default:
                        Usage(argv[0]);
                        break;
                }
            }
            else
                Usage(argv[0]);
        }
    }
 
    if ((retval = WSAStartup(0x202, &wsaData)) != 0)
    {
       fprintf(stderr,"Client: WSAStartup() failed with error %d\n", retval);
        WSACleanup();
        return -1;
    }
    else
     //  printf("Client: WSAStartup() is OK.\n");
 
    if (port == 0)
    {
        Usage(argv[0]);
    }
    // Attempt to detect if we should call gethostbyname() or gethostbyaddr()
    if (isalpha(server_name[0]))
    {   // server address is a name
        hp = gethostbyname(server_name);
    }
    else
    { // Convert nnn.nnn address to a usable one
        addr = inet_addr(server_name);
        hp = gethostbyaddr((char *)&addr, 4, AF_INET);
    }
    if (hp == NULL )
    {
        fprintf(stderr,"Client: Cannot resolve address \"%s\": Error %d\n", server_name, WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    else
     //  printf("Client: gethostbyaddr() is OK.\n");
    // Copy the resolved information into the sockaddr_in structure
    memset(&server, 0, sizeof(server));
    memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(port);
 
    conn_socket = socket(AF_INET, socket_type, 0); /* Open a socket */
    if (conn_socket <0 )
    {
        fprintf(stderr,"Client: Error Opening socket: Error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    else
     //  printf("Client: socket() is OK.\n");
 
    // Notice that nothing in this code is specific to whether we
    // are using UDP or TCP.
    // We achieve this by using a simple trick.
    //    When connect() is called on a datagram socket, it does not
    //    actually establish the connection as a stream (TCP) socket
    //    would. Instead, TCP/IP establishes the remote half of the
    //    (LocalIPAddress, LocalPort, RemoteIP, RemotePort) mapping.
    //    This enables us to use send() and recv() on datagram sockets,
    //    instead of recvfrom() and sendto()
   // printf("Client: Client connecting to: %s.\n", hp->h_name);
   printf("Connnection has been established to server: %s.\n", hp->h_name);
    if (connect(conn_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        fprintf(stderr,"Client: connect() failed: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    else
		printf("\n\t****PLEASE LOGIN****\n");
      // printf("Client: connect() is OK.\n");
 if(sessionName=""){
		printf("\nenter password\n");
		capture_password();
		sessionName=Buffer;
		}
   

	printf("\n\n*********enter help for directions*************");
	printf("\n\n********************COMMAND LINE READY***************\n");

    // Test sending some string
    loopcount = 0;
	i =10;
while(1)
    {  
		
		//do{

		captureCommand();
		//printf("%s",command);
		if( strcmp( command, "quit" ) == 0 )
        {
            break ;
        }
		 if ( strcmp( command, "help" ) == 0 )
        {
           help();
        }

		
		  if (( strcmp( command, "help" ) != 0 )
			  &&strcmp( command, "quit" ) != 0
			  
			  ){

		 if(( strcmp( command, "my contribution" )==0)|| ( strcmp( command, "contribution check" )==0) || ( strcmp( command, "benefits check" )==0)||
		 ( strcmp( command, "loan status" )==0) || ( strcmp( command, "load repayment details" )==0) || 
		 (strstr(command,"idea")&&strstr(command,"\""))|| (strstr(command,"loan")&&strstr(command,"request"))||
		 (strstr(command,"loan")&&strstr(command,"repayment"))||
		 ((strstr(command,"contribution"))&&(!strstr(command,"check")))
		){


				  
         wsprintf(Buffer,command, loopcount);//"This is a test message from client #%d"
		

        retval = send(conn_socket, Buffer, sizeof(Buffer), 0);
		 
        if (retval == SOCKET_ERROR)
        {
            fprintf(stderr,"Client: send() failed: error %d.\n", WSAGetLastError());
            WSACleanup();
            return -1;
        }
        else
         // printf("Client: send() is OK.\n");
       // printf("Client: Sent data \"%s\"\n", Buffer);
 
              retval = recv(conn_socket, Buffer, sizeof(Buffer), 0);
        if (retval == SOCKET_ERROR)
       {
            fprintf(stderr,"Client: recv() failed: error %d.\n", WSAGetLastError());
            closesocket(conn_socket);
            WSACleanup();
            return -1;
        }
        else
           // printf("Client: recv() is OK.\n");
       
        // We are not likely to see this with UDP, since there is no
        // 'connection' established.
        if (retval == 0)
       {
            printf("Client: Server closed connection.\n");
            closesocket(conn_socket);
            WSACleanup();
            return -1;
        }
		else{
       // printf("Client: Received %d bytes, data \"%s\" from server.\n", retval, Buffer);
			if ( strcmp( command, "my contribution" ) == 0 )
			
			{
				replace(Buffer,"	","|");
				//slice personalContTable
		separate(Buffer,"$",sliced_table);
		printf("\n\    Amount\t\   Date\t\tRptNum\t  Status\t   comfirmDate\n");
		for(slicecount=0;slicecount<tokens_counter/2+1;slicecount++){
		printf("\n%d.  %s",slicecount+1,sliced_table[slicecount]);
		
		}
		printf("\n\n");
			}

			else if ( strcmp( command, "load repayment details" ) == 0 )
			
			{
				//replace(Buffer,"	","|");
				//slice personalloanTable
		separate(Buffer,"$",sliced_table_loan);
		printf("\n\    Amount\t\   Date\t\tRptNum\t  Status\t   comfirmDate\n");
		for(loan_slicecount=0;loan_slicecount<tokens_counter/2+1;loan_slicecount++){
		printf("\n%d.  %s",loan_slicecount+1,sliced_table_loan[loan_slicecount]);
		
		}
		printf("\n\n");
			}

			else if ( strcmp( command, "contribution check" ) == 0 )
			printf("\t--> Total contributions: %s\n", Buffer);
			else if ( strcmp( command, "benefits check" ) == 0 )
			printf("\t--> Total profits: %s\n",Buffer);
			/*
			if ( strcmp( Buffer, "idea awaiting acceptance" ) == 0 )
			printf("\t--> Hi %s, your idea is awaiting acceptance ....\n",sessionNames);
			else if ( strcmp( Buffer, "receipt awaiting verication" ) == 0 )
			printf("\t--> Your receipt number is awaiting verification....\n");
			else if ( strcmp( Buffer, "loan in text file" ) == 0 )
			printf("\t--> Your loan request is pending....\n");
			else if ( strcmp( Buffer, "request unknown" ) == 0 )
			printf("\t--> Unknown request !\n");*/
			else
		    printf("\t--> %s\n", Buffer);
				
			
		
		}
		
        if (!loopflag)
       {
            printf("Client: Terminating connection...\n");
            break;
        }
        else
       {
            if ((loopcount >= maxloop) && (maxloop >0))
            break;
        }

		 } //end command verification
		 else{printf("Unknown command! pliz enter help to view command format\n");}
		 }//end if command not help
		

		//}//end do loop
		//while ( strcmp( command, "QUIT" ) != 0 );
       //end for loop
	}  // end while loop


    closesocket(conn_socket);
    WSACleanup();
	
 getchar();
 
return 0;
	
}

void capture_password(){
gets(passwrd);
retval = send(conn_socket, passwrd, sizeof(passwrd), 0);
retval = recv(conn_socket, Buffer, sizeof(Buffer), 0);
printf("\nYou are logged as %s", Buffer);
sessionName=Buffer;
strcpy(sessionNames,sessionName);
}

void captureCommand(){


// the user will input the commands here
printf("\n<< ");
gets(command);
//printf("u entered %s",command);
}
void displayResult(){

}

void help(){
//Endagililo
  
   printf("\n***********************GUIDELINES**************************");
   printf("\nfollow the command order below for your service");
   printf("\n'exit' to safely close program and 'logout' to stop your session");
   printf("\n'my contribution' to load all your contribution details");
   printf("\n'contribution amount receipt_number' to contribute e.g. contribution 200000 105663");
   printf("\n'contribution check' to check all cotributions");
   printf("\n'benefits check' to check current profits");
   printf("\n'loan request amount Number_of_Month' to request alone e.g loan request 500,000 7" );
   printf("\n'loan status' to check your loan status if any ie. approved,pending or denied");
   printf("\n'load repayment details' to get all details of loan repay including amount per month");
   printf("\n'idea name_or_title investment_required \"short_description_up_to_500_words\"' to suggest an idea e.g.");
   printf("\n\tCattle 10,000,000 \"nowadays, cattle has promising returns as compaired to other.......\" ");
   //printf("\n'dismiss' to remove guidelines");
   //printf("\n'never show this' never to show u guidelines");
   //printf("\n**NOTE** the colon ie ':' should only be used to separate command parameters and not anywhere else.");
   printf("\n");
   
   //zikomawanno
}




char *replace(char *st, char *orig, char *repl){
static char Dbuffer[4096];
char *ch;
if(!(ch=strstr(st,orig))){return st;}
else{
strncpy(Dbuffer,st,ch-st);
Dbuffer[ch-st]=0;
sprintf(Dbuffer+(ch-st),"%s%s",repl,ch+strlen(orig));
return Dbuffer;
}
}



char *separate(char *Whole, char *identifier,char *new_storage[1024]){

		a = 0; tokens_counter=0;
    q = strtok (Whole, identifier);

    while (q != NULL)
    {
        new_storage[a++] = q; 
		q = strtok (NULL, identifier);
		tokens_counter ++;
		
    }
    for (a=0;a<tokens_counter;a++){
		
		//printf("\n%s",new_storage[a]);
		
	}
}

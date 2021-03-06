
/* Server program example for IPv4 */
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<dos.h>
#include<conio.h>

#include<mysql.h>  //database connector, in this case, xampp

 
#define DEFAULT_PORT 2007
// default TCP socket type
#define DEFAULT_PROTO SOCK_STREAM

 
void Usage(char *progname)
{
    fprintf(stderr,"Usage: %s -p [protocol] -e [port_num] -i [ip_address]\n", progname);
    fprintf(stderr,"Where:\n\t- protocol is one of TCP or UDP\n");
    fprintf(stderr,"\t- port_num is the port to listen on\n");
    fprintf(stderr,"\t- ip_address is the ip address (in dotted\n");
    fprintf(stderr,"\t  decimal notation) to bind to. But it is not useful here...\n");
    fprintf(stderr,"\t- Hit Ctrl-C to terminate server program...\n");
    fprintf(stderr,"\t- The defaults are TCP, 2007 and INADDR_ANY.\n");
    WSACleanup();
    exit(1);
}
 

char *contribution="";char contributionToStrore[60];
void add_to_contribution();
int indexer,intstrlen=0,intcount=0;
int Rindexer,Rintstrlen=0,Rintcount=0;
int digit_occurance,ach;

const char cont_submit[]="receipt confirmation is in process..";
char *cont_holder[50];

char *idea;
void add_to_ideas();
const char idea_submit[]="your idea is awaiting verification..";
char idea_sub_holder[]={""};
int py;

char *loan_request;
void add_to_loans();
const char loan_submit[]="your loan request has been filed";
const char loan_repay_submit[]="loan repayment is waiting receipt approval. Thanks in advance...";
char loan_status[15]="";
const char loan_pending[]="your loan request is pending waiting for administrator approval";
const char loan_approved[]="Your loan request was successfully approved";
const char loan_reject[]="your loan request has not been granted";
const char no_repay_loan[]="You do not have any loans!";
char  repay_loan_details[]="Pliz hold on..If we delay, u may check from the web";

const char U_request[]="request unknown";


//name from database is stored here. it will be use through out the session
char toClientMsge[25];
char *sliced_Name[400];
char _fullNames[26];

char personalContTable[500];
char personal_loan_Table[500];

//time
void filterTime();
char systemtime[64];


char *replace(char *st, char *orig, char *repl);//metnood
char *separate(char *Whole, char *identifier);
int a;char *another_holder[1024];char *q; int tokens_counter;



int main(int argc, char **argv)
{
//*****************************************************************************connection to database variables
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
 
    
   char *server = "localhost";
   char *user = "root";
   char *password = "";
   char *database = "sacco";
   
  
   char prepared_statement[]="SELECT * FROM members WHERE password ='";
   char *s_name_extractor;
   char *sessionName="";
   

  //for the total contribution
   
   int selfTotal;
   char sTotal[]="your contribution: ";
   char sTotalHolder[10];
  
   int total;
   char tTotal[]="Total contribution: ";
   char tTotalHolder[10];

   int loan_repayed;
   char tloan_repayed_Holder[10];

   int benefits;
   char tbenefits[50]="Current profits: ";
   char tbenefitsHolder[10];
   
  //loans
   
   //char total_cont_st[]="SELECT * FROM sacco_table";
   //char *s_name_extractor;
  
//*****************************************************************************end connection to database variables

    char Buffer[1024]="";
    char *ip_address= NULL;
    unsigned short port=DEFAULT_PORT;
    int retval;
    int fromlen;
    int i;
    int socket_type = DEFAULT_PROTO;
    struct sockaddr_in local, from;
    WSADATA wsaData;
    SOCKET listen_socket, msgsock;
 
    /* Parse arguments, if there are arguments supplied */
    if (argc > 1)
       {
        for(i=1; i<argc; i++)
              {
                     // switches or options...
            if ((argv[i][0] == '-') || (argv[i][0] == '/'))
                     {
                            // Change to lower...if any
                           switch(tolower(argv[i][1]))
                           {
                     // if -p or /p
                    case 'p':
                        if (!stricmp(argv[i+1], "TCP"))
                            socket_type = SOCK_STREAM;
                        else if (!stricmp(argv[i+1], "UDP"))
                            socket_type = SOCK_DGRAM;
                        else
                            Usage(argv[0]);
                        i++;
                        break;
                     // if -i or /i, for server it is not so useful...
                    case 'i':
                        ip_address = argv[++i];
                        break;
                    // if -e or /e
                    case 'e':
                        port = atoi(argv[++i]);
                        break;
                     // No match...
                    default:
                        Usage(argv[0]);
                        break;
                }
            }
            else
                Usage(argv[0]);
        }
    }
 
    // Request Winsock version 2.2
    if ((retval = WSAStartup(0x202, &wsaData)) != 0)
       {
        fprintf(stderr,"Server: WSAStartup() failed with error %d\n", retval);
        WSACleanup();
        return -1;
		
    }
    else
       printf("Server: WSAStartup() is OK.\n");
 
    if (port == 0)
       {
        Usage(argv[0]);
    }
 
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = (!ip_address) ? INADDR_ANY:inet_addr(ip_address);
 
    /* Port MUST be in Network Byte Order */
    local.sin_port = htons(port);
    // TCP socket
    listen_socket = socket(AF_INET, socket_type,0);
 
    if (listen_socket == INVALID_SOCKET){
        fprintf(stderr,"Server: socket() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    else
       printf("Server: socket() is OK.\n");
 
    // bind() associates a local address and port combination with the socket just created.
    // This is most useful when the application is a
    // server that has a well-known port that clients know about in advance.
    if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
       {
        fprintf(stderr,"Server: bind() failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    else
              printf("Server: bind() is OK.\n");
 
     // So far, everything we did was applicable to TCP as well as UDP.
     // However, there are certain steps that do not work when the server is
     // using UDP. We cannot listen() on a UDP socket.
    if (socket_type != SOCK_DGRAM)
       {
        if (listen(listen_socket,5) == SOCKET_ERROR)
              {
            fprintf(stderr,"Server: listen() failed with error %d\n", WSAGetLastError());
            WSACleanup();
            return -1;
        }
       else
              printf("Server: listen() is OK.\n");
    }
    printf("Server: %s: I'm listening and waiting connection\non port %d, protocol %s\n", argv[0], port, (socket_type == SOCK_STREAM)?"TCP":"UDP");
 //************************************************************************************************establish a connection to database 
	//try{
	conn = mysql_init(0);
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
     // return(0);
   }
	//}catch(InnerException  ex){printf("Error:%s",ex );}
   else printf("connection to xampp database success");
   
//************************************************************************************************end establish a connection to database
	
       while(1)
       {

		  
        fromlen =sizeof(from);
        // accept() doesn't make sense on UDP, since we do not listen()
        if (socket_type != SOCK_DGRAM)
              {
            msgsock = accept(listen_socket, (struct sockaddr*)&from, &fromlen);
            if (msgsock == INVALID_SOCKET)
           {
                fprintf(stderr,"Server: accept() error %d\n", WSAGetLastError());
                WSACleanup();
                return -1;
            }
           else
              printf("Server: accept() is OK.\n");
              printf("Server: accepted connection from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port)) ;
           
        }
        else
            msgsock = listen_socket;
 
        // In the case of SOCK_STREAM, the server can do recv() and send() on
        // the accepted socket and then close it.
        // However, for SOCK_DGRAM (UDP), the server will do recvfrom() and sendto()  in a loop.
       do{  if (socket_type != SOCK_DGRAM)
            retval = recv(msgsock, Buffer, sizeof(Buffer), 0);
 
       else
       {
            retval = recvfrom(msgsock,Buffer, sizeof(Buffer), 0, (struct sockaddr *)&from, &fromlen);
            printf("Server: Received datagram from %s\n", inet_ntoa(from.sin_addr));
        }
           
        if (retval == SOCKET_ERROR)
              {
            fprintf(stderr,"Server: recv() failed: error %d\n", WSAGetLastError());
            closesocket(msgsock);
            continue;
        }
       else
            printf("Server: recv() is OK.\n");
 
        if (retval == 0)
              {
            printf("Server: Client closed connection.\n");
            closesocket(msgsock);
            continue;
        }
        printf("Server: Received %d bytes, data \"%s\" from client\n", retval, Buffer);
		//write_to_file();
		
	//*****************************************************************************fetch requests to database
		

		if(sessionName==""){

   s_name_extractor=strncat(prepared_statement,Buffer,sizeof(Buffer));
   strcat(s_name_extractor,"'");
   printf("\nUsing: %s\n",s_name_extractor);
  // send SQL query 
 
   if (mysql_query(conn, s_name_extractor)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   res = mysql_use_result(conn);
   
   // output fields 1 to 4 of each row 
   while ((row = mysql_fetch_row(res)) != NULL){
	  // printf("%s \n", row[1]);
	   sessionName=row[1];
	   
	   strcat(toClientMsge,sessionName);
	
   }//end while
   
   mysql_free_result(res);
   //printf("personal: %d",selfTotal);
   //mysql_close(conn); 
   separate(toClientMsge," ",sliced_Name);
   strcat(_fullNames,sliced_Name[0]);strcat(_fullNames,"_");strcat(_fullNames,sliced_Name[1]);

   retval = send(msgsock, replace(_fullNames,"_"," "), sizeof(_fullNames), 0);

		}
		printf("\nfully slicedNames: %s\n",_fullNames);

//*****************************************************************************end fetch requests to database
strcpy(prepared_statement,"");
strcat(prepared_statement,"SELECT * FROM contributions WHERE status='confirmed'");
 //************************************************************************** Now select everything and store into variables
		
		{
		if (mysql_query(conn, prepared_statement)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   res = mysql_use_result(conn);
   
   // output fields 1 to 4 of each row 
   total=0;
  benefits=0;
   while ((row = mysql_fetch_row(res)) != NULL){
	  
	   total +=atoi(row[2]);
	  benefits +=((atoi(row[2]))*0.25);
	    
   }//end while
   //printf("total: %d",total);
   itoa(total,tTotalHolder,10);  //convert total to string
   strcat(tTotal,tTotalHolder);
   
   itoa(benefits,tbenefitsHolder,10);  //convert benefits to string
   strcat(tbenefits,tbenefitsHolder);

   mysql_free_result(res);
  // mysql_close(conn); 
//end fetch everything
		}
	
//******************************************************************************************************loans
        strcpy(prepared_statement,""); //empty the prepared statement
		printf("%s",_fullNames);
		strcat(prepared_statement,"SELECT * FROM loans WHERE name ='");
		strcat(prepared_statement,replace(_fullNames,"_"," "));
		strcat(prepared_statement,"'");
		printf("USING_LOANS: %s",prepared_statement);
{
		if (mysql_query(conn, prepared_statement)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   res = mysql_use_result(conn);
   
   // output fields 1 to 4 of each row 
   
   while ((row = mysql_fetch_row(res)) != NULL){
	  strcpy(loan_status,row[4]);
	    
   }//end while
  
   mysql_free_result(res);
  // mysql_close(conn); 
//end fetch everything
		}

//****************************************************************************************************************all contributions of a person

//prepare statement
	   strcpy(prepared_statement,""); //empty the prepared statement

		strcat(prepared_statement,"SELECT * FROM contributions WHERE contributor ='");
		strcat(prepared_statement,replace(_fullNames,"_"," "));
		strcat(prepared_statement,"'");
		printf("\nUSING_Conts: %s",prepared_statement);
{
		if (mysql_query(conn, prepared_statement)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   res = mysql_use_result(conn);
   
   // output fields 1 to 4 of each row 
   
   while ((row = mysql_fetch_row(res)) != NULL){
	  //printf("\n%s\t%s\t%s\t%s\t%s",row[2],row[3],row[4],row[5],row[7]);
	  strcat(personalContTable,row[2]);strcat(personalContTable,"	 "); strcat(personalContTable,row[3]);strcat(personalContTable,"	");
	  strcat(personalContTable,row[4]);strcat(personalContTable,"	 "); strcat(personalContTable,row[5]);strcat(personalContTable,"	");
	  strcat(personalContTable,row[7]);strcat(personalContTable,"$"); //strcat(personalContTable,"	");
	   
   }//end while
   
   //printf("\n%s",personalContTable);

   mysql_free_result(res);
  // mysql_close(conn); 
//end fetch everything
		}


//****************************************************************************************************************all loan details of a person

//prepare statement
	   strcpy(prepared_statement,""); //empty the prepared statement

		strcat(prepared_statement,"SELECT * FROM loanpay WHERE payer ='");
		strcat(prepared_statement,replace(_fullNames,"_"," "));
		strcat(prepared_statement,"' AND status='confirmed'"); //strcat(prepared_statement,"'");
		printf("\nUSING_Conts: %s",prepared_statement);
{
		if (mysql_query(conn, prepared_statement)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   res = mysql_use_result(conn);
   
   // output fields 1 to 4 of each row 
   loan_repayed=0;
   while ((row = mysql_fetch_row(res)) != NULL){
	  //printf("\n%s\t%s\t%s\t%s\t%s",row[2],row[3],row[4],row[5],row[7]);
	  strcat(personal_loan_Table,row[2]);strcat(personal_loan_Table,"	 "); strcat(personal_loan_Table,row[3]);strcat(personal_loan_Table,"	");
	  strcat(personal_loan_Table,row[4]);strcat(personal_loan_Table,"	 "); strcat(personal_loan_Table,row[5]);strcat(personal_loan_Table,"	");
	  strcat(personal_loan_Table,row[6]);strcat(personal_loan_Table,"	"); strcat(personal_loan_Table,"$")//;strcat(personal_loan_Table,"	");
	  
	   loan_repayed +=atoi(row[2]);
   }//end while
   
   itoa(loan_repayed,tloan_repayed_Holder,10);  //convert total to string
   //strcat(tTotal,tTotalHolder);
   //printf("\n%s",personalContTable);

   mysql_free_result(res);
  // mysql_close(conn); 
//end fetch everything
		}


//calculate total benefits.



   
	
	if( strcmp( Buffer, "my contribution" )==0){   //command check contributions
		printf("\n%s",personalContTable);
			retval = send(msgsock, personalContTable, sizeof(personalContTable), 0);
			printf("\n--> %s has seen his contribution -->",replace(_fullNames,"_"," "));
			strcpy(personalContTable,"");
			}

	else if( strcmp( Buffer, "contribution check" )==0){
		//printf("\n%d",total);
		//printf("\n%s",tTotalHolder);	
         retval = send(msgsock, tTotalHolder, sizeof(tTotalHolder), 0);
		 printf("\n--> %s has recieved a total of all contributions by all members -->",replace(_fullNames,"_"," "));
			}
	else if( strcmp( Buffer, "benefits check" )==0){
         retval = send(msgsock, tbenefitsHolder, sizeof(tbenefitsHolder), 0);
		 printf("\n--> benefit records have been sent to %s -->",replace(_fullNames,"_"," "));
			}

	else if( strcmp( Buffer, "loan status" )==0){
		printf("\nloan status: %s",loan_status);
		if( strcmp( loan_status, "accepted" )==0)
         retval = send(msgsock, loan_approved, sizeof(loan_approved), 0);
		else if( strcmp( loan_status, "pending" )==0) 
		retval = send(msgsock, loan_pending, sizeof(loan_pending), 0);
		else
		retval = send(msgsock, loan_reject, sizeof(loan_reject), 0);
		printf("\n--> %s has been notified of his loan status!-->",replace(_fullNames,"_"," "));
			}
	else if( strcmp( Buffer, "load repayment details" )==0){
		
		retval = send(msgsock, personal_loan_Table, sizeof(personal_loan_Table), 0);
		printf("\n--> Notifying %s of his loan repayment details!-->",replace(_fullNames,"_"," "));
			} 

	else if(strstr(Buffer,"idea")&&strstr(Buffer,"\"")){
	idea=Buffer;
	add_to_ideas();
	printf("\n%s' idea has been written down to ideas text file",replace(_fullNames,"_"," "));	
    retval = send(msgsock, idea_submit, sizeof(idea_submit), 0);
	printf("\n--> %s has been notified about keeping the idea -->",replace(_fullNames,"_"," "));
	}

	else if(strstr(Buffer,"loan")&&strstr(Buffer,"request")){
	loan_request=Buffer;
	add_to_loans();
	printf("\n%s' loan request has been recoreded into loans text file",replace(_fullNames,"_"," "));	
    retval = send(msgsock, loan_submit, sizeof(loan_submit), 0);
	printf("\n-->sent notification to %s -->",replace(_fullNames,"_"," "));
	}

	else if(strstr(Buffer,"loan")&&strstr(Buffer,"repayment")){
	loan_request=Buffer;
	add_to_loans();
	printf("\n%s' loan repayment has been recorded into loans text file",replace(_fullNames,"_"," "));	
    retval = send(msgsock, loan_repay_submit, sizeof(loan_repay_submit), 0);
	printf("\n-->sent loan repayment notification to %s -->",replace(_fullNames,"_"," "));
	}

	
	else if((strstr(Buffer,"contribution"))&&(!strstr(Buffer,"check"))){
	//check for integers
	strcpy(contributionToStrore,Buffer);
	separate(contributionToStrore," ",cont_holder);

	intstrlen=strlen(cont_holder[1]);
	for(indexer=0;indexer<intstrlen;indexer++){
		if(cont_holder[1][indexer]>=48 && cont_holder[1][indexer]<=57){
		intcount++;
		}
	}
	printf("\nfound %d numbers",intcount);

	Rintstrlen=strlen(cont_holder[2]);
	for(Rindexer=0;Rindexer<Rintstrlen;Rindexer++){
		if(cont_holder[2][Rindexer]>=48 && cont_holder[2][Rindexer]<=57){
		Rintcount++;
		}
	}
	//printf("\nfound %d numbers in receipt",Rintcount);
	
	digit_occurance=intcount+Rintcount;
	//printf("\n\ttotal occurance is %d \n",digit_occurance);
	
	 // the contributions string should contain atleast 6 numbers coz it is in monetary and receipt number temrms
//	if(digit_occurance>6){ 

		//printf("\nwhats gonna be stored is %s ",Buffer);
		contribution=Buffer;
		add_to_contribution();

		retval = send(msgsock, cont_submit, sizeof(cont_submit), 0);
    printf("\n%s' contribution has been stored in contributions text file",replace(_fullNames,"_"," "));	
	printf("\n--> Sending notification to %s -->",replace(_fullNames,"_"," "));
	//} if(digit_occurance>6)

	}


/*
	 if(!( strcmp( Buffer, "my contribution" )==0)&& !( strcmp( Buffer, "contribution check" )==0) && !( strcmp( Buffer, "benefits check" )==0)&&
		!( strcmp( Buffer, "loan status" )==0) && !( strcmp( Buffer, "load repayment details" )==0) && 
		!(strstr(Buffer,"idea")&&strstr(Buffer,"\""))&& !(strstr(Buffer,"loan")&&strstr(Buffer,"request"))&&
		!((strstr(Buffer,"contribution"))&&(!strstr(Buffer,"check")))
	
		){
	printf("Server: %s has entered unknown command!\n",replace(_fullNames,"_"," "));
	printf("\n--> Telling %s to enter valid commands!-->",replace(_fullNames,"_"," "));

        if (socket_type != SOCK_DGRAM)
            retval = send(msgsock, U_request, sizeof(U_request), 0);
        else
            retval = sendto(msgsock, U_request, sizeof(U_request), 0, (struct sockaddr *)&from, fromlen);
 
              if (retval == SOCKET_ERROR)
              
                     fprintf(stderr,"Server: send() failed: error %d\n", WSAGetLastError());
					 
               
              else
                     printf("Server: send() is OK.\n");
	}
*/
		

        if (socket_type != SOCK_DGRAM)
       {
           // printf("Server: I'm waiting more connection, try running the client\n");
           // printf("Server: program from the same computer or other computer...\n");
           printf("\n****************** Server is waiting for more requests.....\n");
        //closesocket(msgsock);
			continue;
        }
            printf("Server: UDP server looping back for more requests\n");
        continue;

		 free(Buffer); }while ( strcmp( Buffer, "quit" ) != 0 );
	   }

	   
	   getchar();
       return 0;
}



char contrReader[]="";FILE *contrFileWriter;FILE *contrFileReader;
void add_to_contribution(){
	 

    
	
	/*if ((contrFileReader = fopen("contributons.txt","r+")) == NULL){
       printf("Error openning contributions file");exit(1);}
 fscanf(contrFileReader,"%s", &contrReader);
	fclose(contrFileReader);*/


contrFileWriter = fopen("contributions.txt", "a+");
   if(contrFileWriter == NULL){printf("Error creating file!");   exit(1);}

   filterTime();

   
   strcat(contribution," ") ; strcat(contribution,"|");strcat(contribution,_fullNames);strcat(contribution,"|");strcat(contribution," ");strcat(contribution,systemtime);

	fprintf(contrFileWriter,"\n%s",contribution);
	
   fclose(contrFileWriter);

}

char ideasReader[]="";FILE *ideasFileWriter;FILE *ideasFileReader; char *ideaToken[500];
char idea_o_holder[30];char *idea_o_token[30];char final_idea[500];
void add_to_ideas(){
	/* if ((ideasFileReader = fopen("ideas.txt","r+")) == NULL){
       printf("Error openning ideas file");exit(1);}
 fscanf(ideasFileReader,"%s", &ideasReader);
	fclose(ideasFileReader); */


ideasFileWriter = fopen("ideas.txt", "a+");
   if(ideasFileWriter == NULL){printf("Error creating or opening ideas file!");   exit(1);}
/*if(ideasReader==NULL)
   fprintf(ideasFileWriter,"%s",idea);
   else*/
   filterTime();  //get system time and rearrange it like day/month/year day_time
   separate(idea,"\"",ideaToken);
   strcpy(idea_o_holder,ideaToken[0]); replace(ideaToken[1],"\"","_");strcpy(idea_sub_holder,ideaToken[1]);
   separate(idea_o_holder," ",idea_o_token);
   strcat(final_idea,idea_o_token[0]);strcat(final_idea,"|");strcat(final_idea,idea_o_token[1]);strcat(final_idea,"|");
   strcat(final_idea,idea_o_token[2]);strcat(final_idea,"|");strcat(final_idea,idea_sub_holder);strcat(final_idea,"|");
   strcat(final_idea,_fullNames);strcat(final_idea,"|");strcat(final_idea,systemtime);
  

   fprintf(ideasFileWriter,"\n%s",final_idea);
   // flush final_idea container for new data
   strcpy(final_idea,"");

   fclose(ideasFileWriter);
}


char loansReader[]="";FILE *loansFileWriter;FILE *loansFileReader;
void add_to_loans(){
	/* if ((ideasFileReader = fopen("ideas.txt","r+")) == NULL){
       printf("Error openning ideas file");exit(1);}
 fscanf(ideasFileReader,"%s", &ideasReader);
	fclose(ideasFileReader); */

loansFileWriter = fopen("loans.txt", "a+");
   if(loansFileWriter == NULL){printf("Error creating or opening loans file!");   exit(1);}

   strcat(loan_request," ") ; strcat(loan_request,"|");strcat(loan_request,_fullNames);strcat(loan_request,"|");

   fprintf(loansFileWriter,"\n%s",loan_request);

   fclose(loansFileWriter);
}



int ty;char *time_array[]={""};char *qq; int toke=0; 

void filterTime(){

	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    strftime(systemtime, sizeof(systemtime), "%c", tm);
    printf("time only is %s\n", systemtime);
  
  ty = 0;
    qq = strtok (systemtime, " ");

    while (qq != NULL)
    {
        time_array[a++] = qq; 
		qq = strtok (NULL, " ");
		toke +=1;
		
    }
   // for (ty=0;ty<toke;ty++){
		
		//printf("\n\t%s",time_array[ty]);
		
	//}
	printf("date only is  %s",systemtime);
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
  /*  for (a=0;a<tokens_counter;a++){
		
		printf("\n%s",new_storage[a]);
		
	}*/
}





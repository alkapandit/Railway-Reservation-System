#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"conio2.h"
#include"rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0; i<=80; i++)
        printf("_");
    printf("\nSelect an option");
    printf("\n1. Veiw Trains");
    printf("\n2. Book Ticket");
    printf("\n3. Veiw Ticket");
    printf("\n4. Search Ticket No");
    printf("\n5. Veiw All Bookings");
    printf("\n6. Veiw Train Bookings");
    printf("\n7. Cancel Ticket");
    printf("\n8. Cancel Trains");
    printf("\n9. Quit");
    printf("\n\nEnter Choice : ");
    scanf("%d",&choice);
    return choice;
}


 void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("d:\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("d:\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File created and saved!\n");

    }
    else
        printf("File already present\n");
    fclose(fp);

}

void view_trains()
{
    int i;
    Train tr;
    printf("\nTRAIN NO\tFROM\tTO\tFIRST FARE\tSECOND FARE\n");
    for(i=0;i<=80;i++)
        printf("_");
    FILE *fp=fopen("D:\\alltrains.dat", "rb");
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}
int check_train_no(char *trainno)
{
    Train tr;
    FILE *fp=fopen("d:\\alltrains.dat", "rb");
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}
Passenger * get_passenger_details()
{
clrscr();
gotoxy(60,1);
textcolor(LIGHTGREEN);
printf("Press 0 to exit");
gotoxy(1,1);
textcolor(YELLOW);
printf("Enter passenger name:");
static Passenger psn;
fflush(stdin);
fgets(psn.p_name,20,stdin);
//fgets4() adds "\n" at the end of file,
//Removing "\n" from the end of name.
char *pos;
pos=strchr(psn.p_name,'\n');
*pos='\0';
//checking for name entered as 0.
if(strcmp(psn.p_name,"0")==0)
{
    textcolor(LIGHTRED);
    gotoxy(1,25);
    printf("RESERVATION CANCELLED !\n");
    getch();
    textcolor(YELLOW);
    return NULL;
}
//taking gender input.
int valid;  //taking valid=1 for verifying input.
gotoxy(1,2);
printf("Enter gender(M/F) : ");
do
{
    valid=1;
    fflush(stdin);
    scanf("%c",&psn.gender);
    if(psn.gender=='0')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.gender!='M' && psn.gender!='F')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Gender should be M or F (in uppercase)");
        valid=0;
        getch();
        gotoxy(21,2);
        printf(" \b");
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t");
//entering train no as input.
gotoxy(1,3);    //reset the cursor at the 1st col 3rd row.
printf("Enter train number:");
do
{
    fflush(stdin);
    scanf("%s",&psn.train_no);
    if(strcmp(psn.train_no,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    valid=check_train_no(psn.train_no);
    if(valid==0)    //if train no is correct, returns 0, otherwise 1.
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Invalid Train No");
        getch();
        gotoxy(20,3);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(20,3);
        textcolor(YELLOW);
    }
}while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t\t\t\t");
gotoxy(1,4);
printf("Enter traveling class(First AC-F,Second AC-S) : ");
do
{
    valid=1;
    fflush(stdin);
    scanf("%c",&psn.p_class);
    if(psn.p_class=='0')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.p_class!='F' && psn.p_class!='S')
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! traveling class should be F or S (in uppercase)");
        valid=0;
        getch();
        gotoxy(51,4);
        printf(" \b");
        textcolor(YELLOW);
    }
}
while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t\t\t\t");
gotoxy(1,5);
printf("Enter your address : ");
fflush(stdin);
fgets(psn.address,20,stdin);
pos=strchr(psn.address,'\n');
*pos='\0';
//checking for address entered as 0.
if(strcmp(psn.address,"0")==0)
{
    textcolor(LIGHTRED);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t\t\t");
    gotoxy(1,25);
    printf("RESERVATION CANCELLED !\n");
    getch();
    textcolor(YELLOW);
    return NULL;
}
printf("Enter your age : ");
do
{
    valid=1;
    fflush(stdin);
    scanf("%d",&psn.age);
    if(psn.age==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !\n");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    if(psn.age<0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Age should be positive");
        valid=0;
        getch();
        gotoxy(18,6);
        printf(" \t\t\t\t\t\t\t\t\t\t");
        gotoxy(18,6);
        textcolor(YELLOW);
    }
}while(valid==0);
gotoxy(1,25);
printf("\t\t\t\t\t\t\t\t\t\t");
gotoxy(1,7);
printf("Enter mobile number : ");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t");//for clearing previous message.
            gotoxy(1,25);
            printf("Reservation Canceled\n");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid mobile number");
            getch();
            gotoxy(23,7);
            printf("\t\t\t\t\t\t\t");
            gotoxy(23,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
return &psn;
}
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("D:\\allbookings.dat", "rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE *fp=fopen("D:\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
        Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==10)
    {
        textcolor(LIGHTRED);
        printf("All sheets in train no %s and %c are full",p.train_no,p.p_class);
        return -1;
    }
    printf("%d\n",&ticket_count);

    int ticket_no=last_ticket_no()+1;
    printf("%d\n",last_ticket_no());
    //int ticket_no=ticket_count+1;
    p.ticketno=ticket_no;
    FILE *fp=fopen("d:\\allbookings.dat", "ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
int accept_ticket_no()
{
    int valid;
    int ticket_no;
    printf("Enter a valid ticket no : ");
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Canceling input\n");
            getch();
            textcolor(YELLOW);
            clrscr();
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Ticket number should be positive");
            getch();
            valid=0;
            gotoxy(26,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(26,1);
            textcolor(YELLOW);
        }
    }while(valid=0);
    return ticket_no;
}
void view_ticket(int ticket_no)
{
    int i;
    FILE *fp=fopen("d:\\allbookings.dat", "rb");
    if(fp==NULL)
    {
        textcolor(YELLOW);
        printf("Sorry! File cannot be opened");
        return ;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNO details of the ticket no %d found!",ticket_no);
    }
    fclose(fp);
}
char *accept_mob_no()
{
    static char mob_no[12];
    char *pos;
    int valid;
    printf("Enter valid mobile number : ");
    do
    {
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
        {
            *pos='\0';
            if(strcmp(mob_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t\t\t");//for clearing previous message.
                gotoxy(1,25);
                printf("Canceling Input...\n");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }
        }
         valid=check_mob_no(mob_no);
            if(valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Invalid mobile number");
                getch();
                gotoxy(29,1);
                printf("\t\t\t\t\t\t\t");
                gotoxy(29,1);
                textcolor(YELLOW);
            }
    }while(valid==0);
    clrscr();
    return mob_no;
}
int *get_ticket_no(char*p_mob_no)
{
    int count=0;
    FILE*fp=fopen("d:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
          ++count;
        }
    }
    if(!count)
    {
        fclose(fp);
        return NULL;
    }
    int *p=(int*)malloc((count+1)*sizeof(int));
    rewind(fp);
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
         *(p+i)=pr.ticketno;
         i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_tickets(char*pmob_no,int*pticket_no)
{
    if(pticket_no==NULL)
    {

        textcolor(LIGHTRED);
        printf("Sorry! No ticket booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return ;
    }
    printf("Following are tickets booked for the mobile no %s",pmob_no);
    int i;
    printf("\n\n TICKET NUMBERS\n");
    printf("-----------------------------\n");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("\n%d",*(pticket_no+i));
    }
     textcolor(WHITE);
     printf("\nPress any key to go back to main screen");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}
char*accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(GREEN);
     printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number : ");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {

                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t\t\t");//for clearing previous message.
                gotoxy(1,25);
                printf("Canceling Input...\n");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! invalid train number");
            getch();
            gotoxy(22,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(22,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}
void view_bookings(char*train_no)
{
    int found=0,i;
    FILE*fp=fopen("d:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return ;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\t\tAGE\tMOBILE NO\n");
    for(i=0;i<=80;i++)
    {
        printf("_");
    }
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of booking in train no %s found",train_no);

    }
    textcolor(WHITE);
    printf("\n\n Press any key to continue");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
void view_all_bookings()
{
    clrscr();
    int found=0,i;
    FILE*fp=fopen("d:\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return ;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\t\tAGE\tMOBILE NO\n");
    for(i=0;i<=80;i++)
    {
        printf("_");
    }
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
        gotoxy(41,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
        found=1;
    }
      if(!found)
    {
        clrscr();
    }
    textcolor(WHITE);
    printf("\n\n Press any key to continue");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}
int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("d:\\allbookings.dat", "rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
    FILE *fp2=fopen("d:\\temp.dat", "wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\temp.dat");
    }
    else
    {
        result=remove("d:\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("d:\\temp.dat","d:\\allbookings.dat");
        if(result!=0)
        return 2;
    }
    return found;
}








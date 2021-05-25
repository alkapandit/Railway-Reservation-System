#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice,ticket_no;
    char*pmob_no;
    int result;
    char*ptrain_no;
    int pticket_no;
    Passenger *ptr;
    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
        switch(choice)
        {
            case 1:
               view_trains();
               getch();
               clrscr();
                break;
            case 2:
               ptr=get_passenger_details();
               clrscr();
               if(ptr!=NULL)
               {
                   ticket_no=book_ticket(*ptr);
                   if(ticket_no==-1)
                   {
                       textcolor(LIGHTRED);
                       printf("booking failed");
                   }
                   else
                   {
                       textcolor(LIGHTGREEN);
                       printf("Ticket successfully booked\nYour ticket no is %d",ticket_no);
                   }
                   textcolor(WHITE);
                   printf("\nPress any key to go back to the main screen");
                   getch();
                   clrscr();
               }
                break;
            case 3:
                clrscr();
                ticket_no=accept_ticket_no();
                if(ticket_no!=0);
                {
                    view_ticket(ticket_no);
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to the main screen");
                getch();
                clrscr();
                break;
            case 4:
                clrscr();
                pmob_no=accept_mob_no();
                if(pmob_no!=NULL)
                {
                    pticket_no=get_ticket_no(pmob_no);
                    view_all_tickets(pmob_no,pticket_no);
                }
                clrscr();
                break;
            case 5:
               clrscr();
               view_all_bookings();
               clrscr();
                break;
            case 6:
               clrscr();
               ptrain_no=accept_train_no();
               if(ptrain_no!=NULL)
               {
                   view_bookings(ptrain_no);
               }
               clrscr();
                break;
            case 7:
               clrscr();
               ticket_no=accept_ticket_no();
               if(ticket_no!=0)
               {
                   result=cancel_ticket(ticket_no);
                   if(result==0)
                   {
                       textcolor(LIGHTRED);
                       printf("Sorry! No bookings against ticket no %d",ticket_no);
                   }
                   else if(result==1)
                   {
                       textcolor(LIGHTRED);
                       printf("Ticket no %d successfully cancel",ticket_no);
                   }
                   else if(result==2)
                   {
                       textcolor(LIGHTRED);
                       printf("Sorry Error in cancellation. Try again");
                   }
                    textcolor(WHITE);
                    printf("\n\n Press any key to go back to main screen");
                }
                getch();
                clrscr();
                break;
            case 8:
                //cancel_train();
                break;
            default:
                textcolor(LIGHTRED);
                gotoxy(1,29);
                printf("Wrong choice! Try again");
                getch();
                clrscr();
        }

    }

    return 0;
}

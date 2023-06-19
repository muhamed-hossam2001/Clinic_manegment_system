#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <vsadmin.h>
#include "STDTYPES.h"
#include "Config.h"

u8 Slots[][20]={"2pm to 2:30pm","2:30pm to 3pm","3pm to 3:30pm","4pm to 4:30pm","4:30pm to 5pm"};
u8 SureSlot[5];

/* In Admin Mode*/
/*the data of patient */
typedef struct DataAdmin
{
    u8 name[20];
    u8  id;
    u8 Gender[5];
    u8 Age;
    u8 slot[20];

}DataAdmin;

/*creating struct to collect data of patientAdminMode*/
typedef struct PatientAdminMode
{
    DataAdmin data;
    struct PatientAdminMode *next;

}PatientAdminMode;

/*creating head and tail of linked list */
PatientAdminMode *HeadAdmin=NULL;
PatientAdminMode *TailAdmin=NULL;
u8 NumberReservationAdmin=0;
u8 LenSlot=0;
u8 Choice1=1;
u8 Choice2=1;

/*creat new Reservation for Admin patient*/
PatientAdminMode *CreatNewReservationAdmin(DataAdmin data1)
{
    PatientAdminMode *NewReservat=(PatientAdminMode *)malloc(sizeof (PatientAdminMode));
    strcpy(NewReservat->data.name,data1.name);
    NewReservat->data.Age=data1.Age;
    NewReservat->data.id=data1.id;
    strcpy(NewReservat->data.Gender,data1.Gender);
    NewReservat->next=NULL;
    return NewReservat;
}

void InsertReservation (PatientAdminMode *Node)
{
    if (NumberReservationAdmin == 0)
    {
        HeadAdmin = TailAdmin = Node;
    }
    else
    {
        TailAdmin->next=Node;
        TailAdmin= Node;
    }
    NumberReservationAdmin++;

}
u8 IDIsExist(u8 id)
{
    PatientAdminMode *temp=HeadAdmin;

    while(temp!=NULL)
    {
        if(temp->data.id==id)
        {
            return 0;
        }
        temp=temp->next;

    }
    return 1;
}

u8 IDWhereExist(u8 id)
{
    PatientAdminMode *temp=HeadAdmin;

    for (u8 i = 0; i < NumberReservationAdmin; ++i)
    {
        if(temp->data.id==id)
        {
            return i ;
        }
        temp=temp->next;

    }


}

void Resveded(u8 *slot)
{
    for (int h = 0; h <5 ; ++h)
    {
        if(!strcmp(slot,Slots[h]))
        {
            SureSlot[LenSlot++]=h;
        }
    }
}

u8 WhereReserved(u8 *slot)
{
    for (int u = 0; u <5 ; ++u)
    {
        if(!strcmp(slot,Slots[u]))
        {
            for (int o = 0; o <strlen(SureSlot) ; ++o)
            {
                if (u==SureSlot[o])
                    return SureSlot[o];
            }
        }
    }

}

int IsReserved(u8 *slot)
{
    for (int u = 0; u <5 ; ++u)
    {
        if(!strcmp(slot,Slots[u]))
        {
            for (int o = 0; o <LenSlot ; ++o)
            {
                if (u==SureSlot[o])
                    return 1;
            }
        }
    }
    return 0;
}

void CanselSlot(u8 id,u8 position)
{

    PatientAdminMode *temp = HeadAdmin;
    for (int l = 0; l <position ; ++l)
    {
        temp=temp->next;
    }

    u8 DelPos=WhereReserved(temp->data.slot);
    for (int h = DelPos; h <4 ; ++h)
    {
        SureSlot[h]=SureSlot[h+1];
    }
    LenSlot--;

}

void CancelRecervation(u8 id)
{   if(!IDIsExist(id))
    {
        u8 position=IDWhereExist(id);
        PatientAdminMode *temp=HeadAdmin;
        if(position==0)
        {

            if (NumberReservationAdmin == 1)
            {
                free(HeadAdmin) ;
                HeadAdmin = NULL;
                CanselSlot( temp->data.id,position);
                NumberReservationAdmin--;
            }
            else
            {
                HeadAdmin=HeadAdmin->next;
                CanselSlot( temp->data.id,position);
                free(temp);
                NumberReservationAdmin--;

            }


            printf("The Cancelation is Done :)\n");
        }
        else if (position==NumberReservationAdmin-1)
        { PatientAdminMode *temp2;
            while (temp->next!=TailAdmin)
            {
                temp=temp->next;
            }
            temp->next=NULL;
            temp2=TailAdmin;
            //  CanselSlot( temp->data.id,position);
            free(temp2);
            TailAdmin=temp;
            NumberReservationAdmin--;
            printf("The Cancelation is Done :)\n");
        }
        else
        {
            PatientAdminMode *past=HeadAdmin;
            PatientAdminMode *curr=HeadAdmin->next;
            for (int i=1; i<position; i++)
            {
                past=past->next;
                curr=curr->next;
            }
            past->next=curr->next;
            CanselSlot( curr->data.id,position);
            free(curr);
            NumberReservationAdmin--;
            printf("The Cancelation is Done :)\n");
        }

    }
    else
    {
        printf("Incorrect Id ,You don't reseve before :)\n");
    }
}

void EditingReservation(u8 id)
{
    if(!IDIsExist(id))
    {
        u8 position=IDWhereExist(id);
        PatientAdminMode *temp=HeadAdmin;
        for (int i = 0; i <position ; ++i)
        {
            temp=temp->next;
        }
        printf("PLease ,Enter new data :)\n");
        printf("Enter the Name please :");
        gets(temp->data.name);
        printf("Enter the Age please :");
        scanf("%d", &temp->data.Age);
        printf("Enter the Gender please :");
        scanf("%s", &temp->data.Gender);

        printf("The editing information succeeded :)\n");

    }
    else
    {
        printf("Incorrect ID ,You don't reseve before :)\n");
    }

}

void ReserveSlot (u8 id)
{ u8 reserve[20];
    PatientAdminMode *temp=HeadAdmin;
    if(!IDIsExist(id))
    {
        int position=IDWhereExist(id);
        printf("The Slots are :\n");
        for (int k = 0; k <5 ; ++k)
        {
            printf("%s\n",Slots[k]);
        }
        printf("please enter the slot that suit you :)\n");
        for (int l = 0; l <position ; ++l)
        {
            temp=temp->next;
        }
        gets(reserve);
        gets(reserve);

        if(IsReserved(reserve))
        {
            printf("Sorry ,this slot is Reserved oridy :)\n");
        }
        else
        {
            strcpy(temp->data.slot,reserve);
            Resveded(reserve);
        }


    }
    else
    {
        printf("Incorrect ID ,You don't reseve before :)");
    }

}



/* In User Mode*/
/*the data of patient */

void  ViewDataPatient( u8 id)
{
    if(!IDIsExist(id))
    {
        u8 position=IDWhereExist(id);
        PatientAdminMode *temp=HeadAdmin;
        for (int k = 0; k <position ; ++k)
        {
            temp=temp->next;
        }
        printf("The name is : %s\n",temp->data.name);
        printf("The age is : %d\n",temp->data.Age);
        printf("The Gender is : %s\n",temp->data.Gender);
        printf("The id is : %d\n",temp->data.id);
        printf("The slot with doctor from : %s\n",temp->data.slot);

    }
    else
    {
        printf("Incorrect Id ,You don't reseve before :)\n");
    }
}
void TodaysReservations()
{
    int flag=0;
    for (int l = 0; l <5 ; ++l)
    {
        for (int k = 0; k <LenSlot ; ++k)
        {
            if(l==SureSlot[k])
                flag=1;
        }
        if (flag==0)
            printf("%s\n",Slots[l]);
        flag=0;

    }
}


int main()
{
    while (Choice1)
    {
        printf("press 1 if you are Admin :)\n");
        printf("press 2 if you are User :)\n");
        scanf("%d",&Choice1);
if (Choice1==AdminMode)
{
    int Password=1234;
    int PasswordSearch;
    int CounterPW=0;
    int i;
    for(i=0;i<3;i++)
    {
            printf("Enter the Password please :\n");
            scanf("%d", &PasswordSearch);
            if (PasswordSearch == Password)
            {
                printf("login is succeeded :)\n");
                break;
            }
            else
            {
                CounterPW++;
                printf(" Incorrect Password\nplease try again\n");
            }
    }

    if(CounterPW==3)
    {
        printf("Your tries is expired\n please assure with password and try later\n");
    }
    else
        {
        Choice2=1;
        while (Choice2)
        {
            printf("\n\nPress 1 if you want to modify data :\n");
            printf("Press 2 if you want to cancel reservation :\n");
            printf("Press 3 if you want to reserve slot with doctor :\n");
            printf("Press 4 if you want to reserve new slot  :\n");
            printf("Press 0 if you want to exit the program :\n");
            scanf("%d", &Choice2);
            switch (Choice2)
            {
                case 0:
                {
                    printf("Exit form Admin mode is done\n");
                    break;
                }
                case 1:
                {
                    int IDModify;
                    printf("Enter the id you want to modify :)\n");
                    scanf("%d", &IDModify);
                    EditingReservation(IDModify);
                    break;
                }
                case 2:
                {
                    int IDModify;
                    printf("Enter the id you want to cancel :)\n");
                    scanf("%d", &IDModify);
                    CancelRecervation(IDModify);
                    break;
                }
                case 3:
                {
                    int IDModify;
                    printf("Enter the id you want to reserve :)\n");
                    scanf("%d", &IDModify);
                    ReserveSlot(IDModify);
                    break;
                }
                case 4:
                {
                    DataAdmin Reservat;
                    printf("Enter the ID please :");
                    scanf("%d", &Reservat.id);
                    if (IDIsExist(Reservat.id))
                    {
                        printf("Enter the Name please :");
                        gets(Reservat.name);
                        gets(Reservat.name);
                        printf("Enter the Age please :");
                        scanf("%d", &Reservat.Age);
                        printf("Enter the Gender please :");
                        scanf("%s", &Reservat.Gender);

                        InsertReservation(CreatNewReservationAdmin(Reservat));
                    }
                    else
                    {
                        printf("The Id must Be unique ,please try Again later :)");
                    }
                        break;
                }
                default:
                {
                        printf("Incorrect Choice ,please try again :)\n");
                }
            }
        }


        }



    }
else if(Choice1==UserMode)
{
    Choice2=1;
    while (Choice2)
    {
        printf("Press 1 if you want to Show Your information :\n");
        printf("Press 2 if you want to View todays reservations :\n");
        printf("Press 0 if you want to exit the program :\n");

        scanf("%d", &Choice2);
        switch (Choice2)
        {
            case 0:
            {
                printf("Exit form User mode is done\n");
                break;
            }
            case 1:
                {
                int IDModify;
                printf("Enter the id you want to modify :)\n");
                scanf("%d", &IDModify);
                ViewDataPatient(IDModify);
                break;
            }
            case 2:
            {

                printf("The Available slots are :-\n ");
                TodaysReservations();
                break;
            }
            default:
            {
                printf("Invalid Choice2 :)\n");
            }

        }
    }
}
else
{
    printf("you entered wrong dara please enter whither Admin mode or User mode !");
}
    }

    return 0;
}

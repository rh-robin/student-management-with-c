#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include <ctype.h>
#include<time.h>

//========== all function declaration ====
void title();
void userValidation();
void loginMsg();
void menu();
void createList();
void addToList(int id, char fName[25], char lName[25], char gender, float cgpa, char phn[13]);
int phoneValidation(char phn[13]);
int idValidation(int id);
void add();
void update();
void viewTableTitle();
void view();
void viewByCgpa();
void sortingList();
void search();
void dlt();
void doExit();

//====for setting cursor position
void gotoxy(short x, short y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//======structure========
struct node
{
    int id;
    char fName[25], lName[25], phn[13], gender;
    float cgpa;
    struct node *next;
    struct node *prev;
} *H, *C, *visit, *temp;


int id,i;
char fName[25], lName[25],phn[13], gender;
float cgpa;
FILE *file;

int valid=1,list;


int main()
{
    userValidation();
    createList();
    menu();
    return 0;
}

/* function for user validation*/
void userValidation()
{
    char userName[6]="robin", passWord[4]="123",uName[20],pass[20];
    title();
    while(1)
    {
        if(valid!=1)
        {
            system("cls");
            title();
            printf("\t\t\t\t\tinvalid userName or Password. please try again \n\n");
        }
        printf("\t\t\t\t\tUser Name: ");
        scanf("%s",uName);
        fflush(stdin);
        printf("\t\t\t\t\tPassword: ");
        scanf("%s",pass);
        fflush(stdin);
        if(strcmp(userName,uName)==0 && strcmp(passWord,pass)==0)
        {
            valid=1;
            loginMsg();
            break;
        }
        else
        {
            valid=0;
        }
    }
}
/* login message */
void loginMsg()
{
    clock_t clk1=clock()+2000;
    system("cls");
    title();
    printf("\n\n\t\t\t\t\tloging in");
    while(clock()<clk1);
}

/* function for showing title of the project*/
void title()
{
    valid=1;
    printf("\n\n\n\t\t\t\t==================================================");
    printf("\n\t\t\t\t=                                                =");
    printf("\n\t\t\t\t=            Student Management System           =");
    printf("\n\t\t\t\t=                                                =");
    printf("\n\t\t\t\t==================================================\n\n");
}

/* function to create menu*/
void menu()
{
    int opt;
    while(1)
    {
        system("cls");
        title();
        if(valid!=1)
        {
            system("cls");
            title();
            printf("\n\t\t\t\t\tPlease enter a valid option.\n");
        }
        printf("\n\t\t\t\t\t1. Add Student ");
        printf("\n\t\t\t\t\t2. View All Student ");
        printf("\n\t\t\t\t\t3. View By CGPA ");
        printf("\n\t\t\t\t\t4. Search Student ");
        printf("\n\t\t\t\t\t5. Update Student ");
        printf("\n\t\t\t\t\t6. Delete Student ");
        printf("\n\t\t\t\t\t7. Save And Exit ");
        printf("\n\n\t\t\t\t\tEnter your option: ");
        scanf("%d",&opt);
        if(opt==1)
            add();
        else if(opt==2)
            view();
        else if(opt==3)
            viewByCgpa();
        else if(opt==4)
            search();
        else if(opt==5)
            update();
        else if(opt==6)
            dlt();
        else if(opt==7)
            doExit();
        else
            valid=0;
    }
}


//===============start of add function==============
void add()
{
    char again='Y';
    while(toupper(again)=='Y')
    {
        system("cls");
        title();

        printf("\n\t\t\t\t\tAdd Student:");
        printf("\n\t\t\t\t\t-----------------\n");

        while(1)
        {
            if(valid!=1)
                printf("\n\t\t\t\t\tEnter a valid ID: ");
            printf("\n\t\t\t\t\tEnter ID: ");
            scanf("%d",&id);
            if(idValidation(id)!=0)
            {
                valid=1;
                break;
            }
            else
                valid=0;
        }
        printf("\n\t\t\t\t\tEnter First Name: ");
        scanf("%s",fName);
        printf("\n\t\t\t\t\tEnter Last Name: ");
        scanf("%s",lName);
        while(1)
        {
            printf("\n\t\t\t\t\tEnter Gender(M/F): ");
            fflush(stdin);
            scanf("%c",&gender);
            if(toupper(gender)=='M' || toupper(gender)=='F')
                break;
            else
                printf("\n\t\t\t\t\tWrong character.\n");
        }
        while(1)
        {
            if(valid!=1)
                printf("\n\t\t\t\t\tEnter a valid CGPA");
            printf("\n\t\t\t\t\tEnter CGPA: ");
            scanf("%f",&cgpa);
            if(cgpa>=1 && cgpa<=4)
            {
                valid=1;
                break;
            }
            else
                valid=0;
        }
        while(1)
        {
            if(valid!=1)
                printf("\n\t\t\t\t\tEnter a valid number");
            printf("\n\t\t\t\t\tEnter Phone Number: ");
            scanf("%s",phn);
            fflush(stdin);
            if(phoneValidation(phn)!=0)
            {
                valid=1;
                break;
            }
            else
                valid=0;
        }
        addToList(id,fName,lName,gender,cgpa,phn);
        fflush(stdin);
        printf("\n\t\t\t\t\tAdd more student(Y/N): ");
        scanf("%c",&again);
        if(toupper(again)=='N')
            break;
    }
}
// validation of phone number
 int phoneValidation(char phn[13])
 {
     if(strlen(phn)==11)
     {
         for(i=0; i<strlen(phn); i++)
         {
             if(isalpha(phn[i])!=0)
             {
                 return 0;
                 break;
             }
         }
     }
     else
        return 0;
 }
 // validation of ID
 int idValidation(int id)
 {
     visit=H;
     while(visit!=NULL)
     {
         if(visit->id==id)
         {
             return 0;
             break;
         }
         visit=visit->next;
     }
     return 1;
 }

//=============End of add function============


//=============create list function============
void createList()
{
    H=(struct node*)malloc(sizeof( struct node));
    C=(struct node*)malloc(sizeof( struct node));
    H=NULL;
    C=NULL;


    FILE *viewFile;
    viewFile=fopen("student-data.txt","r");
    while(fscanf(viewFile,"%d %s %s %c %f %s\n",&id,fName,lName,&gender,&cgpa,phn)!=EOF)
    {
        struct node *new_node;
        new_node=(struct node*)malloc(sizeof(struct node));
        new_node->id=id;
        strcpy(new_node->fName,fName);
        strcpy(new_node->lName,lName);
        new_node->gender=gender;
        new_node->cgpa=cgpa;
        strcpy(new_node->phn,phn);
        new_node->next=NULL;
        if(H==NULL)
        {
            H=new_node;
            C=new_node;
            H->prev=NULL;
            C->prev=NULL;
        }
        else
        {
            new_node->prev=C;
            C->next=new_node;
            C=C->next;
        }
    }
    fclose(viewFile);
}
//=============End of create list function============


//=============start of add to list function============
void addToList(int id, char fName[25], char lName[25], char gender, float cgpa, char phn[13])
{
    struct node *new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->id=id;
    strcpy(new_node->fName,fName);
    strcpy(new_node->lName,lName);
    new_node->gender=gender;
    new_node->cgpa=cgpa;
    strcpy(new_node->phn,phn);
    new_node->next=NULL;
    if(H==NULL)
    {
        H=new_node;
        C=new_node;
        H->prev=NULL;
        C->prev=NULL;
    }
    else
    {
        new_node->prev=C;
        C->next=new_node;
        C=C->next;
    }
}
//=============end of add to list function============


//=============Start of view function============
void viewTableTitle()
{
    //createList();
    system("cls");
    title();
    sortingList();
    printf("\n\t\t\t\t\t\tAdd Student:");
    gotoxy(5,13);
    printf("ID");
    gotoxy(25,13);
    printf("First Name");
    gotoxy(50,13);
    printf("Last Name");
    gotoxy(75,13);
    printf("Gender");
    gotoxy(90,13);
    printf("CGPA");
    gotoxy(103,13);
    printf("Phone");
    printf("\n");
    for(i=0; i<=115; i++)
        printf("=");
    printf("\n");
}
void view()
{
    int row=16;
    viewTableTitle();
    if(H!=NULL)
    {
        visit=H;
        while(visit!=NULL)
        {
            gotoxy(5,row);
            printf("%d",visit->id);
            gotoxy(25,row);
            printf("%s",visit->fName);
            gotoxy(50,row);
            printf("%s",visit->lName);
            gotoxy(75,row);
            if(toupper(visit->gender)=='M')
                printf("Male");
            else
                printf("Female");
            gotoxy(90,row);
            printf("%.2f",visit->cgpa);
            gotoxy(103,row);
            printf("%s",visit->phn);
            row++;
            visit=visit->next;
        }
    }
    else
        printf("\n\t\t\t\t\t\tNo student added.");
    printf("\n\n\t\t\t\t\t\tPress any key to continue");
    getch();
}
//============== End of view function==========

//==========view by cgpa======
void viewByCgpa()
{
    int row; float minCgpa;
    char again='Y';
    while(toupper(again)=='Y')
    {
        row=16;
        system("cls");
        title();
        printf("\n\t\t\t\t\t\tEnter minimum CGPA: ");
        scanf("%f",&minCgpa);
        viewTableTitle();
        if(H!=NULL)
        {
            visit=H;
            while(visit!=NULL)
            {
                if((visit->cgpa>=minCgpa) && (visit->cgpa<=4))
                {
                    gotoxy(5,row);
                    printf("%d",visit->id);
                    gotoxy(25,row);
                    printf("%s",visit->fName);
                    gotoxy(50,row);
                    printf("%s",visit->lName);
                    gotoxy(75,row);
                    if(toupper(visit->gender)=='M')
                        printf("Male");
                    else
                        printf("Female");
                    gotoxy(90,row);
                    printf("%.2f",visit->cgpa);
                    gotoxy(103,row);
                    printf("%s",visit->phn);
                    row++;
                }
                visit=visit->next;
            }
        }
        else
            printf("\n\t\t\t\t\t\tNo student exist in the list.");
        fflush(stdin);
        printf("\n\n\t\t\t\t\t\tSearch Again?[Y/N].");
        scanf("%c",&again);
        if(toupper(again)=='N')
            break;
    }
    printf("\n\n\t\t\t\t\t\tPress any key to continue");
    getch();

}
//========== end view by cgpa======

//========sorting List
void sortingList()
{
    visit=H;
    struct node *nextPtr;
    while(visit!=NULL)
    {
        nextPtr=visit->next;
        while(nextPtr!=NULL)
        {
            if((visit->id)>(nextPtr->id))
            {
                id=visit->id;
                strcpy(fName,visit->fName);
                strcpy(lName,visit->lName);
                gender=visit->gender;
                cgpa=visit->cgpa;
                strcpy(phn,visit->phn);
                visit->id=nextPtr->id;
                strcpy(visit->fName,nextPtr->fName);
                strcpy(visit->lName,nextPtr->lName);
                visit->gender=nextPtr->gender;
                visit->cgpa=nextPtr->cgpa;
                strcpy(visit->phn,nextPtr->phn);
                nextPtr->id=id;
                strcpy(nextPtr->fName,fName);
                strcpy(nextPtr->lName,lName);
                nextPtr->gender=gender;
                nextPtr->cgpa=cgpa;
                strcpy(nextPtr->phn,phn);
            }
            nextPtr=nextPtr->next;
        }
        visit=visit->next;
    }
}

//=============End of sorting function============
void search()
{
    int ok;
    char again='Y';
    while(toupper(again)=='Y')
    {
        system("cls");
        title();
        printf("\n\n\t\t\t\t\tEnter ID to search: ");
        scanf("%d",&id);
        visit=H;
        while(visit!=NULL)
        {
            if(visit->id==id)
            {
                ok=1;
                id=visit->id;
                strcpy(fName,visit->fName);
                strcpy(lName,visit->lName);
                gender=visit->gender;
                cgpa=visit->cgpa;
                strcpy(phn,visit->phn);
                break;
            }
            else
                ok=0;
            visit=visit->next;
        }
        if(ok==0)
        {
            printf("\n\n\t\t\t\t\tThis ID is not exist ");
        }
        else
        {
            printf("\n\n\t\t\t\t\tID: %d",id);
            printf("\n\n\t\t\t\t\tFirst Name: %s",fName);
            printf("\n\n\t\t\t\t\tLast Name: %s",lName);
            if(toupper(gender)=='M')
                printf("\n\n\t\t\t\t\tGender: Male");
            else
                printf("\n\n\t\t\t\t\tGender: Female");
            printf("\n\n\t\t\t\t\tCGPA: %.2f",cgpa);
            printf("\n\n\t\t\t\t\tPhone: %s",phn);
        }
        fflush(stdin);
        printf("\n\n\t\t\t\t\tSearch Again?[Y/N]: ");
        scanf("%c",&again);
        if(toupper(again)=='N')
            break;
    }
}
void update()
{
    int ok;
    char again='Y';
    while(toupper(again)=='Y')
    {
        system("cls");
        title();
        printf("\n\n\t\t\t\t\tEnter ID to Update: ");
        scanf("%d",&id);
        visit=H;
        while(visit!=NULL)
        {
            if(visit->id==id)
            {
                ok=1;
                id=visit->id;
                strcpy(fName,visit->fName);
                strcpy(lName,visit->lName);
                gender=visit->gender;
                cgpa=visit->cgpa;
                strcpy(phn,visit->phn);
                break;
            }
            else
                ok=0;
            visit=visit->next;
        }
        if(ok==0)
        {
            printf("\n\n\t\t\t\t\tThis ID is not exist ");
        }
        else
        {
            printf("\n\n\t\t\t\t\tID: %d",id);
            printf("\n\n\t\t\t\t\tFirst Name: %s",fName);
            printf("\n\n\t\t\t\t\tLast Name: %s",lName);
            if(toupper(gender)=='M')
                printf("\n\n\t\t\t\t\tGender: Male");
            else
                printf("\n\n\t\t\t\t\tGender: Female");
            printf("\n\n\t\t\t\t\tCGPA: %.2f",cgpa);
            printf("\n\n\t\t\t\t\tPhone: %s",phn);

            printf("\n\n\n\t\t\t\t\tEnter new data to update: ");
            while(1)
            {
                if(valid!=1)
                    printf("\n\t\t\t\t\tEnter a valid CGPA");
                printf("\n\n\t\t\t\t\tEnter New CGPA: ");
                scanf("%f",&cgpa);
                if(cgpa>=1 && cgpa<=4)
                {
                    valid=1;
                    break;
                }
                else
                    valid=0;
            }
            visit->cgpa=cgpa;
            while(1)
            {
                if(valid!=1)
                    printf("\n\t\t\t\t\tEnter a valid number");
                printf("\n\t\t\t\t\tEnter New Phone Number: ");
                scanf("%s",phn);
                fflush(stdin);
                if(phoneValidation(phn)!=0)
                {
                    valid=1;
                    break;
                }
                else
                    valid=0;
            }
            strcpy(visit->phn,phn);
        }
        printf("\n\n\t\t\t\t\tSearch again to update?[Y/N]: ");
        fflush(stdin);
        scanf("%c",&again);
        if(toupper(again)=='N')
            break;
    }
}
void dlt()
{
    int ok;
    char again='Y';
    while(toupper(again)=='Y')
    {
        system("cls");
        title();
        printf("\n\n\t\t\t\t\tEnter ID to delete: ");
        scanf("%d",&id);
        visit=H;
        while(visit!=NULL)
        {
            if(visit->id==id)
            {
                ok=1;
                if(visit==H)
                {
                    H=visit->next;
                    H->prev=NULL;
                }
                else if(visit->next==NULL)
                    visit->prev->next=NULL;
                else
                {
                    visit->next->prev=visit->prev;
                    visit->prev->next=visit->next;
                }
                break;
            }
            else
                ok=0;
            visit=visit->next;
        }
        if(ok==0)
        {
            printf("\n\n\t\t\t\t\tThis ID is not exist ");
        }
        else
        {
            printf("\n\n\t\t\t\t\tDeleted Successfully");
        }
        printf("\n\n\t\t\t\t\tDelete another?[Y/N]: ");
        fflush(stdin);
        scanf("%c",&again);
        if(toupper(again)=='N')
            break;
    }
}
void doExit()
{
    file= fopen("student-data.txt","w");
    visit=H;
    while(visit!=NULL)
    {
        fprintf(file,"%d %s %s %c %f %s\n",visit->id,visit->fName,visit->lName,visit->gender,visit->cgpa,visit->phn);
        visit=visit->next;
    }
    fclose(file);
    exit(1);
}

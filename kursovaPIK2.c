#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

typedef struct user
{
    char username[30];
    double startingWeight;
    double currentWeight;
} User;
typedef struct ex
{
    int id;
    int timeInSec;
} Exercise;

char *remove1(char* mystr);
int initialization(User *);
void doExercise(User *);

int main()
{
    User cUser;
    doExercise(&cUser);

    return 0;
}

void doExercise(User *user)
{
    int cID, startSec, endSec,contEx=1,res=0,ofs=0;
    double newCurWeight;
    Exercise ex;
    FILE *fp;
    char en[4];
    printf("\n Welcome to our gym 'BIG BOY'\n");
    do
    {

        if(contEx)
        {
            printf("\n Choose one of our machines:\n     1-Leg press\n     2-Bench press\n     3-Smith machine\n     4-Barbells\n     5-Treadmill\n     6-Spin bike\n     7-Jump rope\n     8-Dumbbells\n");

            do
            {
                scanf(" %d",&cID);

            }
            while(cID!=1&&cID!=2&&cID!=3&&cID!=4&&cID!=5&&cID!=6&&cID!=7&&cID!=8);
            res=initialization(user);
            if(res)
            {
                startSec=clock();
                printf(">>END<< for end of current exercise\n");
                do
                {
                    scanf(" %s",&en);

                }
                while(en=="END"||en=="end");
                endSec=clock();
                ex.id=cID;
                ex.timeInSec=(endSec-startSec)/1000;
                fp=fopen(user->username,"ab");
                if(fp!=NULL)
                {
                    fwrite(&ex,sizeof(Exercise),1,fp);
                    printf("%d %d",ex.id, ex.timeInSec);
                }

            }

        }
        if(res)
        {
            printf("0 for end of workout, 1 for continue\n");
            scanf(" %d",&contEx);
        }
        else
            return;

    }
    while (contEx!=0);

    printf("Please enter your current weight\n");
    do
    {
        scanf(" %s", &newCurWeight);
    }
    while(user->currentWeight<20&&user->currentWeight>400);
    fclose(fp);
    fp=fopen(user->username,"rb+");
    if(fp!=0){
        ofs=sizeof(char)*30 + sizeof(double);
        fseek(fp,ofs , SEEK_END);
        fwrite(&newCurWeight,sizeof(double),1,fp);
    }
    //printf("%s  %lf  %lf \n",user->username,newCurWeight, user->startingWeight);

    fclose(fp);

}

int initialization(User *user)
{
    char username[30];
    struct dirent *de;
    int flag=0,i;
    FILE *fp;

    printf("enter your username: ");
    scanf(" %s", username);
    DIR *dr = opendir(".");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }
    while ((de = readdir(dr)) != NULL)
    {
        i =strcmp(remove1(de->d_name), username);
        if(!i)
        {
            strcpy(user->username,username);
            printf("Login successful!\n" );
            flag=1;
            return 1;
        }

    }

    if (flag==0)
    {
        //getchar();
        char answer;
        double a;
        char test[10];
        printf("User does not exist!\n Do you want to be registered?\n       Y/N \n" );
        scanf(" %c",&answer);
        if(answer=='Y')
        {
            strcpy(user->username,username);
            printf("enter your current weight: ");
            scanf(" %s", &test);
            a = atof(test);
            user->currentWeight= a;
            user->startingWeight = a;


            fp=fopen(username,"ab+");


            if(fp!=NULL)
            {
                fwrite(user,sizeof(User),1,fp);
                //printf("%s  %lf  %lf \n",user->username,user->currentWeight, user->startingWeight);


            }
            return 1;

        }
        else
        {
            printf("You can't use our gym without registration");
            return 0;
        }

    }
    closedir(dr);
    fclose(fp);
    return 0;

}

char *remove1(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
        return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}

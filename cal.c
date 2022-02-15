#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include "time.h"

// Global Variables
int curr_year,curr_month,month_days,day,week_day=0,startingday;
char *months[]={"January","Feburary","March","April","May","June","July","August","September","October","November","December"};
int month[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // array to store no. of days

// Functions
int first_weekday(int curr_year, int curr_month) // zellar's algorith
{
  if (curr_month == 1) {
        curr_month = 13;
        curr_year--;
    }
    if (curr_month == 2) {
        curr_month = 14;
        curr_year--;
    }
    int q = 1; // day = 1
    int m = curr_month;
    int k = curr_year % 100;
    int j = curr_year / 100;
    int h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    h = h % 7;
    return h-1; // coz zellar's algorith starts from saturday =0 but below in function sunday=0.
}

void check_leap_year(int year) // checking for leap year
{
  if((year%4==0&&year%100!=0)||year%400==0)month[1]=29;  // if leap year then Feburary days = 29;
}

int main(int argc, char const *argv[])  // main function
{
  if(argv[1]==NULL)  // cal
  {
    // printf("cal\n");
    // for getting current year and month from the system
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds);
    curr_year=current_time->tm_year + 1900;
    curr_month=current_time->tm_mon + 1; // month starts form 1

    check_leap_year(curr_year);
    startingday=first_weekday(curr_year,curr_month);

    if(startingday==-1)startingday=6; // to make saturday = 6
    month_days=month[curr_month-1];
    printf("\n              %s %d               \n",months[curr_month-1],curr_year);
    printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    for(week_day=0;week_day<startingday;week_day++)
    {
      printf("     "); // pading of 5
    }

    for(day=1;day<=month_days;day++)
    {
      printf("%5d",day);
      if(++week_day>6)
      {
          printf("\n");
          week_day=0;
      }
    }
    startingday=week_day;
    printf("\n");
  }

  else if( !strcmp(argv[1],"-3") )// cal -3
  {
    // printf("cal -3\n");
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds);
    if(argv[2]==NULL)
    {
      curr_year=current_time->tm_year + 1900;
      curr_month=current_time->tm_mon + 1;
    }
    else if( (argv[2]!=NULL) && (argv[3]!=NULL) && (argv[4]==NULL) )
    {
      if( (atoi(argv[2])>12) || (atoi(argv[2])<0) )
      {
        printf("cal: %s is not a month number (1..12)\n",argv[2]);
        exit(0);
      }
      curr_year=atoi(argv[3]);
      curr_month=atoi(argv[2]);
    }
    else
    {
      printf("cal: Not valid\n");
      exit(0);
    }
    for(int i=curr_month-1; i<=curr_month+1; i++)
    {
      int flag_1,flag_2;
      if(i==0) // why ? -> coz if month is 1 we have to go one year back to print December also
      {
        flag_1 = 1;
        i = 12;
        curr_year -= 1;
      }

      if(i==13)  // why ? -> coz if month is 12 we have to go one year ahead to print January also
      {
        flag_2 = 2;
        i=1;
        curr_year += 1;
      }

      check_leap_year(curr_year);
      startingday=first_weekday(curr_year,i);

      if(startingday==-1)startingday=6; // to make saturday = 6
      month_days=month[i-1]; // coz month is an array with starting index as 0
      printf("\n              %s %d               \n",months[i-1],curr_year);
      printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
      for(week_day=0;week_day<startingday;week_day++)
      {
        printf("     "); // pading of 5
      }

      for(day=1;day<=month_days;day++)
      {
        printf("%5d",day);
        if(++week_day>6)
        {
            printf("\n");
            week_day=0;
        }
      }
      startingday=week_day;
      if(i==12&&flag_1==1)
      {
        i=0;
        curr_year += 1;
      }
      if(i==1&&flag_2==2)
      {
        break;
      }
      printf("\n");
    }
  }

  else if(argv[3]==NULL)  // cal mm yyyy m = 1 yyyy = 2
  {
    if( (atoi(argv[1])>12) || (atoi(argv[1])<0) )
    {
      printf("cal: %s is not a month number (1..12)",argv[1]);
    }
    else
    {
      curr_month = atoi(argv[1]);
      curr_year = atoi(argv[2]);
      check_leap_year(curr_year);
      startingday=first_weekday(curr_year,curr_month);
      if(startingday==-1)startingday=6; // to make saturday = 6
      month_days=month[curr_month-1];
      printf("\n              %s %d               \n",months[curr_month-1],curr_year);
      printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
      for(week_day=0;week_day<startingday;week_day++)
      {
        printf("     "); // pading of 5
      }

      for(day=1;day<=month_days;day++)
      {
        printf("%5d",day);
        if(++week_day>6)
        {
            printf("\n");
            week_day=0;
        }
      }
      startingday=week_day;
      printf("\n");
    }
  }

  else if(argv[2]==NULL) // cal yyyy
  {
    // printf("cal yyyy\n");
    if( !atoi(argv[1]) )
    {
      printf("cal: Not valid\n");
      exit(0);
    }
    curr_year = atoi(argv[1]);
    check_leap_year(curr_year);
    startingday=first_weekday(curr_year,1); // getting the Starting Day of a year
    if(startingday==-1)startingday=6; // to make saturday = 6
    printf("\n                 %s                 ",argv[1]);
    for(int i=0; i<12; i++)
    {
        month_days=month[i];
        printf("\n\n               %s               \n",months[i]);
        printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        for(week_day=0;week_day<startingday;week_day++)
        {
          printf("     "); // pading of 5
        }

        for(day=1;day<=month_days;day++)
        {
          printf("%5d",day);
          if(++week_day>6)
          {
              printf("\n");
              week_day=0;
          }
        }
        startingday=week_day;
     }
     printf("\n");
  }
  else
  {
    printf("cal: not valid\n");
  }
  printf("\n");
  return 0;
}

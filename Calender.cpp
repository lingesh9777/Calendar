#include<iostream>
#include<windows.h>
#include<conio.h>

#define SPACE 32
#define VL 179
#define HL 196
#define LT 218
#define RT 191
#define TT 194
#define LST 195
#define RST 180
#define BT 193
#define LB 192
#define RB 217
#define CROSS 197
#define BS 8
#define TOTCOLS 80
#define TOTROWS 25
#define DIM 7
#define WIDTH 5
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWM 80
using namespace std;


void gotoxy(int x,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y =y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int isLeap(int yr)
{
    return ((yr%400==0)||((yr%4==0) && (yr%100!=0)))?1:0;
}
int DayOfWeek( int y, int m, int d ) // returns Day of Week:0 = Sunday, 1= Monday...
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} //--DayOfWeek( )--------*/

void colHeadings()
{
    int row;
    int col;
    int ctr;
    row = (TOTROWS-(DIM + (DIM+1)))/2;
    col = (TOTCOLS -((WIDTH*DIM)+(DIM+1)))/2;
    char *day[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
    row+=1;
    col+=2;
	for(ctr=0;ctr<DIM;ctr++){
        gotoxy(col+(ctr*(WIDTH+1)),row);
        printf("%s",day[ctr]);

	}

}
void drawDabba()
{
    int row;
    int col;
    row = (TOTROWS-(DIM + (DIM+1)))/2;
    col = (TOTCOLS -((WIDTH*DIM)+(DIM+1)))/2;

	gotoxy(col,row);
	int ctr1;
	int ctr2;
	int ctr3;
	printf("%c",LT);
	for(ctr2 =0;ctr2<DIM;ctr2++)
    {
        for(ctr1 =0;ctr1<5;ctr1++)
        {
            printf("%c",HL);
        }
        printf("%c",TT);
    }
    printf("%c%c",BS,RT);

    for(ctr3 =0;ctr3<7;ctr3++)
    {
        row+=1;
        gotoxy(col,row);
        for(ctr2=0;ctr2<DIM;ctr2++)
        {
            printf("%c",VL);
            for(ctr1=0;ctr1<5;ctr1++)
                printf("%c",SPACE);
        }
        printf("%c",VL);
        row+=1;
        gotoxy(col,row);
        printf("%c",LST);
        for(ctr2 =0;ctr2<DIM;ctr2++)
        {
            for(ctr1 =0;ctr1<5;ctr1++)
            {
                printf("%c",HL);
            }
            printf("%c",CROSS);
        }
        printf("%c%c",BS,RST);
    }
    gotoxy(col,row);
    printf("%c",LB);
	for(ctr2 =0;ctr2<DIM;ctr2++)
    {
        for(ctr1 =0;ctr1<5;ctr1++)
        {
            printf("%c",HL);
        }
        printf("%c",BT);
    }
    printf("%c%c",BS,RB);
}
void cleaner()
{
    int row;
    int col;
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    row += 3;
    col += 3;
    int ctr;
    int week;
    for (week = 0; week <6; week += 1)
    {
        for(ctr = 0; ctr <DIM; ctr += 1)
        {
            gotoxy(col + (ctr * (WIDTH+1)) , row);
            printf("  ");
        }
        row+=2;
    }
}


void calendar(int month,int year)
{
    int row;
    int col;
    row = (TOTROWS-(DIM + (DIM+1)))/2;
    col = (TOTCOLS -((WIDTH*DIM)+(DIM+1)))/2;
    int days_months[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    char *monthName[] ={"","January","February","March","April","May","June","July","August","September","October","November","December"};
    row +=3;
    col+=3;
    int day;
    int ctr;
    if(isLeap(year))
        days_months[2]=29;
    else
        days_months[2]=28;
    gotoxy(30,3);
    printf("%10s, %d",monthName[month],year);
    cleaner();
    for(day=1,ctr=DayOfWeek(year,month,1);day<=days_months[month];day++)
    {
        gotoxy(col+(ctr*(WIDTH+1)),row);
        printf("%2d",day);
        ctr+=1;
        if(ctr==DIM)
        {
            row+=2;
            ctr=0;
        }
    }
}



int main()
{
    int month;
    int year;
    int key;
    month = 7;
    year = 2004;
    drawDabba();
    colHeadings();
    do{
        calendar(month,year);
        key = getch();
        if(key==13)
            break;
        key =getch();
        switch(key)
        {
            case LEFT : month-=1; break;
            case RIGHT: month+=1; break;
            case UP: year-=1; break;
            case DOWM : year+=1; break;
        }
        if(month>12)
        {
             month = 1;
             year+=1;
        }
        if(month<1)
        {
            month=12;
            year-=1;
        }
    }while(key!=13);

}


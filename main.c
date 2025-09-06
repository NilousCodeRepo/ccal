//TODO: error checking
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define __USE_XOPEN//for strptime()
/*
void important_date()
{}
*/

void current_date()
{
	struct tm *tm;
	time_t cdate, day, month, year, days_in_month, start_day;
	char date_str[64];

	time(&cdate);//initialize time in secs in cdate
	tm = localtime(&cdate);

	day = tm->tm_mday;//days in month[1-31]
	start_day = tm->tm_wday;//days in week [1-7]
	month = tm->tm_mon + 1;
	year = tm->tm_year + 1900;

	// Determine the number of days in the current month
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
			|| month == 10 || month == 12) 
	{
		days_in_month = 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) 
	{
		days_in_month = 30;
	}
	else 
	{
		days_in_month = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
			? 29 : 28;
	}

	// Print the month and year
	strftime(date_str, sizeof(date_str), "%B %Y", tm);
	printf("     %s\n", date_str);
	printf("Su Mo Tu We Th Fr Sa\n");

	// Print the calendar
	for (int i = 0; i < start_day; i++) 
	{
		printf("   ");
	}

	for (int i = 1; i <= days_in_month; i++) 
	{
		if (i == day) 
		{
			printf(" |%2d|", i);
		}
		else 
		{
			printf("%3d", i);
		}
		if ((i + start_day) % 7 == 0 || i == days_in_month) 
		{
			printf("\n");
		}
	}

}

void next_date(time_t day, time_t month, time_t year)
{
	struct tm *tm;
	time_t ndate;

	time(&ndate);
	tm = localtime(&ndate);
	printf ("the next date will be: %04d-%02d-%02d\n",	tm->tm_year+1900 + year,
																										 	tm->tm_mon+1 + month,
																											tm->tm_mday + day);
}

int main(int argc, char** argv)
{
	int opt;
	time_t tloc;
	const time_t timep = time(&tloc);

	if((opt = getopt(argc, argv,"bih")) != -1)
	{
		switch(opt)
		{
			case 'h': printf("-b: calculate next date\n-i: mark date as important\n");
			break;
			case 'b':
			break;
			case 'i':
			{
				time_t d,m,y;
		
				printf("insert date to calculate:\n");
				scanf("%d%d%d",&d,&m,&y);
		
				next_dete(d,m,y);
			}
			break;	
		}
	}
	else
	{
		current_date();
	}
	
	return 0;
}



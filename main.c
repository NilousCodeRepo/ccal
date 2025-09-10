//TODO: error checking

#include <stdio.h>
#define __USE_XOPEN//for strptime()
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void print_cal();

void important_date(time_t imp_day, time_t imp_mon, time_t imp_year)
{
	struct tm *tm;
	time_t imp_date;
	char buf[64];

	FILE *fptr;
	fptr = fopen("save.txt", "w+");

	time(&imp_date);
	tm = localtime(&imp_date);	

	tm->tm_mday = imp_day;
	tm->tm_mon = imp_mon - 1; 
	tm->tm_year = imp_year - 1900;
	strftime(buf, sizeof(buf), "%B %d %Y", tm);
	//TODO: write to file the results of strftime
	fprintf(fptr, "%s\n", buf);
	
	fclose(fptr);
}

void current_date()
{
	print_cal();
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

void print_cal()
{
	struct tm *tm, *imp_date;
	time_t cdate, day, month, year, days_in_month, start_day;
	char date_str[64];

	FILE *fptr;
	fptr = fopen("save.txt", "r");

	time(&cdate);//initialize time in secs in cdate
	tm = localtime(&cdate);
	imp_date = localtime(&cdate);

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

if(fptr != NULL)
{
	//TODO: broken comparison
	if(fscanf(fptr, "%ld-%ld-%ld\n")== 
		strftime(date_str, sizeof(date_str), "%B %d %Y", tm))
	{
		// Print the calendar
		for (int i = 0; i < start_day; i++) 
		{
			printf("  *");
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

	fclose(fptr);
}
	else
	{ 
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
			case 'i':
			{
				time_t d,m,y;
	
				printf("insert reminder:\n");
				scanf("%d%d%d",&d,&m,&y);

				important_date(d,m,y);
			}
			break;
			case 'b':
			{
				time_t d,m,y;
		
				printf("insert date to calculate:\n");
				scanf("%d%d%d",&d,&m,&y);
		
				next_date(d,m,y);
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



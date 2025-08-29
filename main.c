//TODO: check errors;

#include <stdio.h>
#include <time.h>
#include <unistd.h>//for getopts. There will not be --args in cmd
#include <stdlib.h>
#include <string.h>

time_t next_time(time_t day, time_t month, time_t year);
void current_date();
time_t important_date();

int main(int argc, char* argv[])
{
	int options;
	time_t tloc;
	const time_t timep = time(&tloc);
	char buf[26];

	//use a while for more options at the same time
	if((options = getopt(argc, argv, "abhi")) != -1)
	{
		{
			switch(options)
			{
				case 'h': printf("-b: calculate next date\n");
				break;

				case 'b':
				{
					time_t d,m,y;

					printf("enter d/m/y to calculate:\n",d,m,y);
					scanf("%d%d%d",&d,&m,&y);
					next_time(d,m,y);
				}
				break;
				
				default:
				     printf("?? getopt returned character code 0%o ??\n",options);
			}
		}
	}
	else
	{
		current_date();
	}

	return 0;
}

time_t  next_time(time_t day, time_t month, time_t year)
{
    time_t now;
    struct tm *tm;

    now = time(0);
    if ((tm = localtime (&now)) == NULL) {
        printf ("Error extracting time stuff\n");
        return 1;
    }

    printf ("%04d-%02d-%02d\n",
        tm->tm_year+1900+year, tm->tm_mon+1+month, tm->tm_mday + day);
}

void current_date()
{
    time_t tloc;
    struct tm *tm;
    char date_str[50];
    int day, month, year, days_in_month, start_day, i, j;

    time(&tloc);
    tm = localtime(&tloc);

    if (tm == NULL) {
        printf("Error extracting time information\n");
        return;
    }

    day = tm->tm_mday;
    month = tm->tm_mon + 1;
    year = tm->tm_year + 1900;
    start_day = tm->tm_wday; // Day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)

    // Determine the number of days in the current month
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        days_in_month = 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_in_month = 30;
    } else {
        days_in_month = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
    }

    // Print the month and year
    strftime(date_str, sizeof(date_str), "%B %Y", tm);
    printf("     %s\n", date_str);
    printf("Su Mo Tu We Th Fr Sa\n");

    // Print the calendar
    for (i = 0; i < start_day; i++) {
        printf("   ");
    }
    for (i = 1; i <= days_in_month; i++) {
        if (i == day) {
            printf(" |%2d|", i);
        } else {
            printf("%3d", i);
        }
        if ((i + start_day) % 7 == 0 || i == days_in_month) {
            printf("\n");
        }
    }
}



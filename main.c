#include <stdio.h>
#include <time.h>
#include <unistd.h>//fot getopts. There will not be --args in cmd

time_t next_time(time_t day, time_t month, time_t year);
void current_date();
void important_day();

int main(int argc, char* argv[])
{
	int options;
	time_t tloc;
	const time_t timep = time(&tloc);
	char buf[26];

	//use a while for more options in the same time
	if((options = getopt(argc, argv, "abh")) != -1)
	{
		{
			switch(options)
			{
				case 'h': printf("a: current time\n b: calculate next date\n");
				case 'a': printf("%s\n",ctime_r(&timep,buf));
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

void current_date()//print it so that is nicely formatted
{
	time_t tloc;
	const time_t timep = time(&tloc);
	char buf[26];

 	printf("%s\n",ctime_r(&timep,buf));
}
//
//void important_day()
//{
//	printf("select a date to mark:*",d,m,y);
//}
//

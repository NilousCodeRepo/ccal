#include <stdio.h>
#include <time.h>

int main()
{
	time_t tloc;
	const time_t timep = time(&tloc);
	char buf[26];

	printf("%s\n",ctime_r(&timep,buf));//thread safe version of the ctime()
	//TODO: Visualize month + day of the month in a schematized way

}

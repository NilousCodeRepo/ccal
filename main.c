#include <stdio.h>
#include <time.h>
#include <unistd.h>//fot getopts. There will not be --args in cmd

int main(int argc, char* argv[])
{
	int options;

	time_t tloc;
	const time_t timep = time(&tloc);
	char buf[26];

	while((options = getopt(argc, argv, "a")) != -1)
		{
			switch(options)
			{
				case 'a': printf("%s\n",ctime_r(&timep,buf));
				break;

				default:
				     printf("?? getopt returned character code 0%o ??\n",options);
			}
		}

	return 0;
}

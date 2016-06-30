#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[100];
	int fp;

	assert(argc > 1);
	memset(buf, 0, 100);
	printf("Input: %s\n", argv[1]);

	fp = open("/dev/pen1", O_RDWR);

	write(fp, argv[1], strlen(argv[1]));

	while(read(fp, buf, 128));

	printf("Message: %s\n", buf);

	return 0;
}

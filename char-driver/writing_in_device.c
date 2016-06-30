#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[100];
    char device_filename[100] = "/dev/char_device";
	int fp;

    if(argc < 2){
        printf("Usage: %s \"message\"\n", argv[0]);
        return -1;
    }

	memset(buf, 0, 100);

    printf("Opening device file [%s]\n\n", device_filename);

	fp = open(device_filename, O_RDWR);

    printf("Writing [%s] in [%s]...\n", argv[1], device_filename);
	write(fp, argv[1], strlen(argv[1]));
    printf("Writing successful\n\n");

    printf("Reading from [%s]...\n", device_filename);
	while(read(fp, buf, 128));
	printf("Reading succesful!\n");

    printf("\nMessage read: [%s]\n", buf);

	return 0;
}

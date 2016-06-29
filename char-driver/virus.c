#include <stdlib.h>

int main(){
	system("sudo rmmod char_driver");
	system("sudo insmod char_driver_virus.ko");

	return 0;
}

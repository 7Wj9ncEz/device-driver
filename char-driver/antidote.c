#include <stdlib.h>

int main(){
	system("sudo rmmod char_driver_virus");
	system("sudo insmod char_driver.ko");

	return 0;
}

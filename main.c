#include <stdio.h>
#include <stdlib.h>
#include "Application/app.h"

#define NORMAL setvbuf(stdout, NULL, _IONBF, 0)

int main(int argc, char **argv)
 {
	NORMAL;
	appStart();
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {

    const char *tmp = argv[1];
    int userYear = atoi(tmp);

    if((userYear % 4 == 0 && userYear % 100 != 0) || (userYear % 400 == 0)) {
        printf("%d was a leap year\n", userYear);
    } else {
        printf("%d was not a leap year\n", userYear);
    }

    return 1;
}

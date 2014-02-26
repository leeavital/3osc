#include <stdio.h>
#include "3osc.h"
#include "ftable.h"

int main(){
    oscInit();
    oscStartLoop();
    oscWait();
}

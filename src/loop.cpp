#include "loop.h"
#include <unistd.h>


void Worker2::doWork(const QString &parameter){  
    int Switch = 1;
    while(true){
        if(Switch == 1){
        emit resultReady("1");
        Switch = 2;
        }
        else {
            emit resultReady("2");
            Switch = 1;
        }
        sleep(5);
    } 
}
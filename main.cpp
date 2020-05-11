
#include <iostream>
#include "Success.h"
#include <random>

using namespace std;

int main(int argc, const char* argv[]){
    
    PCB P;
    
   
    P.ProcessMaking(5, 3, 8);
    //P.printingProcesses();
   
    
    
    
    
    
    //P.tempoMakingProcess();
    //P.countingATT_FIFO();
    //P.countingATT_SJF();
    P.countingATT_SRT();
    cout<<endl;
    
    
    
    
   
    return 0;
}

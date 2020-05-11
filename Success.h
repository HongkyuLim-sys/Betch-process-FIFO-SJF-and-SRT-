#ifndef Success_h
#define Success_h


class PCB{

private:
    
   typedef struct process{
        int index;   //process index number
        int active;  //Active
        int ArrTime; //Arrival Time
        int TCTime;  //Tocal CPU Time
        int RCTime;  //Remaining CPU Time
        int TT;      // Turnaround Time
        process* next;
    }* processIndex;
    
    processIndex head;
    processIndex curr;
    processIndex temp;
    processIndex temp2;
    
public:

    PCB();
    void tempoMakingProcess(); //임시로 process 만듬
    int rIntUniDis(); //return a random integer from an Uniform distribution / k is 1000
    int rIntNorDis(int d, int v); //return a random integer from an normal distribution
    void ProcessMaking(int processIndexNum, int d, int v);
    int smallestElement(struct process* head);
    processIndex shortestRCT(int countingStatus);
    processIndex shortestRCT_SRT(int countingStatus);
    void AddingTT(int countingStatus, int index);
    void sortArray(int array[], int nElement);
    double countingATT_FIFO();
    double countingATT_SJF();
    double countingATT_SRT();
    void printingProcesses();
    processIndex tester = new process;
};


#endif /* Success_h */


#include "Success.h"
#include <iostream>
#include <random>
using namespace std;


PCB::PCB(){
    head = NULL;
    curr = NULL;
    temp = NULL;
    temp2 = NULL;
}

int PCB::rIntUniDis(){
    LOOP:
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 10); //k is 20
    
    int i = dis(gen);
    
    if(i <= 0){
        goto LOOP;
    }
    
    return i;
}

int PCB::rIntNorDis(int d, int v){
   LOOP:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (d,v);
    int i = int(distribution(generator));
    
    if(i<=0){
        goto LOOP;
    }
    
    return i;
}

//
void PCB::tempoMakingProcess(){
   
    processIndex n = new process;
    n->index=0;
    n->active = 1;
    n->ArrTime = 4;
    n->TCTime = 2; //mean and DS are undecided yet
    n->RCTime = n->TCTime;
    n->TT = 0;
    n->next=NULL;
    
    head= n;
    
    processIndex n1 = new process;
    n1->index=1;
    n1->active = 1;
    n1->ArrTime = 4;
    n1->TCTime =7; //mean and DS are undecided yet
    n1->RCTime = n1->TCTime;
    n1->TT = 0;
    n1->next=NULL;
    
    head->next = n1;
    
    processIndex n2 = new process;
    n2->index=2;
    n2->active = 1;
    n2->ArrTime = 8;
    n2->TCTime = 4; //mean and DS are undecided yet
    n2->RCTime = n2->TCTime;
    n2->TT = 0;
    n2->next=NULL;
    
    head->next->next = n2;
    
    processIndex n3 = new process;
    n3->index=3;
    n3->active = 1;
    n3->ArrTime = 7;
    n3->TCTime = 7; //mean and DS are undecided yet
    n3->RCTime = n3->TCTime;
    n3->TT = 0;
    n3->next=NULL;
    
    head->next->next->next = n3;
    
    processIndex n4 = new process;
    n4->index=2;
    n4->active = 1;
    n4->ArrTime = 10;
    n4->TCTime = 1; //mean and DS are undecided yet
    n4->RCTime = n4->TCTime;
    n4->TT = 0;
    n4->next=NULL;
    
    head->next->next->next->next = n4;
     
}


//

void PCB::ProcessMaking(int nProcess ,int d ,int v){
    
    int i = 0;
    processIndex processPtr = new process;
    while(i<nProcess){
        
        processIndex n = new process;
        n->index=i;
        n->active = 1;
        n->ArrTime = rIntUniDis();
        n->TCTime = rIntNorDis(d, v); //mean and DS are undecided yet
        n->RCTime = n->TCTime;
        n->TT = 0;
        n->next=NULL;
    
        if(head != NULL){
            processPtr=head;
            while(processPtr->next != NULL){
                processPtr = processPtr->next;
            }
            processPtr->next = n;
        }else{
            head = n;
        }
        
        i++;
    }
    
}


 PCB::processIndex PCB::shortestRCT(int countingStatus){
     
     processIndex shortestRCTP = new process;
     processIndex headPtr = new process;
     headPtr = head;
     
     int min = INT_MAX;
     cout<<"min : "<<min<<endl;
     
     while(headPtr != NULL){
         cout<<"------------------"<<endl;
                cout<<"index ->\t"<<headPtr->index<<endl;
                cout<<"active ->\t"<<headPtr->active<<endl;
                cout<<"Arrival Time ->\t"<<headPtr->ArrTime<<endl;
                cout<<"Total CPU Time ->\t"<<headPtr->TCTime<<endl;
                cout<<"Remaining CPU Time ->\t"<<headPtr->RCTime<<endl;
                cout<<"Turnaround Time ->\t"<<headPtr->TT<<endl;
                cout<<"------------------"<<endl;
         cout<<"[][][][][][][][]"<<endl;
         if((min>headPtr->RCTime)&&(headPtr->active!=0)&&(headPtr->ArrTime<=countingStatus)){
             min = headPtr->RCTime;
             cout<<"min in while : "<<min<<endl;
         }
         headPtr = headPtr->next;
     }
     cout<<"shortestRCT testing"<<endl;
     //finding a process that has min
     processIndex headPtr2 = new process;
     headPtr2 = head;
     
     while(headPtr2 != NULL){
         if((headPtr2->RCTime == min)&&(headPtr2->active!=0)&&(headPtr2->RCTime>0)){
             shortestRCTP = headPtr2;
         }
         headPtr2 = headPtr2->next;
     }
     
     return shortestRCTP;
 }

 

//to find the process that has the shortest Remaining time
PCB::processIndex PCB::shortestRCT_SRT(int countingStatus){
    
    processIndex shortestRCTP = new process;
    shortestRCTP=NULL;
    
    processIndex headPtr = new process;
    headPtr = head;
    
    int min = INT_MAX;
    int check =0;
    
    while(headPtr != NULL){
        
        if((min>headPtr->RCTime)&&(headPtr->active!=0)&&(headPtr->ArrTime<=countingStatus)){
            min = headPtr->RCTime;
            check++;
        }
        headPtr = headPtr->next;
    }
    
    
    if(check>0){
        //finding a process that has min
        processIndex headPtr2 = new process;
        headPtr2 = head;
    
        while(headPtr2 != NULL){
       
            if((headPtr2->RCTime == min)&&(headPtr2->active!=0)&&(headPtr2->RCTime>0)){
                
                if(shortestRCTP==NULL){
                    shortestRCTP = headPtr2;
                }
            }
            headPtr2 = headPtr2->next;
        }
    
        return shortestRCTP;
    }
    else{
        return NULL;
    }
}


void PCB::printingProcesses(){
    
    curr=head;
    
    while(curr!=NULL){
        
        cout<<"------------------"<<endl;
        cout<<"index ->\t"<<curr->index<<endl;
        cout<<"active ->\t"<<curr->active<<endl;
        cout<<"Arrival Time ->\t"<<curr->ArrTime<<endl;
        cout<<"Total CPU Time ->\t"<<curr->TCTime<<endl;
        cout<<"Remaining CPU Time ->\t"<<curr->RCTime<<endl;
        cout<<"Turnaround Time ->\t"<<curr->TT<<endl;
        cout<<"------------------"<<endl;
        
        curr = curr->next;
    }
    
}

void PCB::AddingTT(int countingStatus, int index){
    
    processIndex count = new process;
    count = head;
    while(count!=NULL){
        processIndex countIndex = new process;
        countIndex = count;
        
        if((countIndex->active!=0)&&(countIndex->TCTime!=0)&&(countIndex->ArrTime<=countingStatus)){
            countIndex->TT = countingStatus-countIndex->ArrTime;
            //
            cout<<"####################################"<<endl;
            cout<<"countingStatus : "<<countingStatus<<endl;
            cout<<"index : \t"<<countIndex->index<<endl;
            cout<<"RCT : \t"<<countIndex->RCTime<<endl;
            cout<<"TT : \t"<<countIndex->TT<<endl;
            cout<<"####################################"<<endl;
            //
        }
        
        count=count->next;
        
    }
}

//to organize an array in ascending order
void PCB::sortArray(int array[], int nElement){
    int i, j, min, temp;
    for (i = 0; i < nElement - 1; i++) {
       min = i;
       for (j = i + 1; j < nElement; j++)
          if (array[j] < array[min])
             min = j;
       temp = array[i];
       array[i] = array[min];
       array[min] = temp;
    }
}

double PCB::countingATT_FIFO(){
    
    //counting number of process
    int nProcess=0;
    processIndex processPtr1 = new process;
    processPtr1 = head;
    
    while(processPtr1!=NULL){
        nProcess++;
        processPtr1=processPtr1->next;
    }
    //
    
    
    
    double ATT=0.0;
    int ArrTimeCompare[nProcess]; //array of every ArrTime
    int j = 0;
    int countingStatus = 0;
    
    
    //making an array of Arrival times to compare
    processIndex processPtr2 = new process;
    processPtr2=head;
    
    while(processPtr2 != NULL){
        ArrTimeCompare[j]=processPtr2->ArrTime;
        j++;
        processPtr2=processPtr2->next;
    }
    
    //sorting ArrTimeCompare[] in order
    sortArray(ArrTimeCompare, nProcess);
    
    countingStatus = ArrTimeCompare[0];
    int gap =0;
    
    for(int i=0; i<nProcess; i++){
        
        //adjusting countingStatus to catch up the gap
        gap = ArrTimeCompare[i]-countingStatus;
        
        if(gap>0){
            countingStatus = countingStatus + gap;
        }
        
        //finding process that has the ArrTime
        processIndex processPtr3 = new process;
        processPtr3 = head;
       
        while(processPtr3!=NULL){
            //finding the process
            if(processPtr3->ArrTime==ArrTimeCompare[i]){
                if(processPtr3->RCTime<=0){
                    processPtr3->active=0;
                }
                else{
                    while(processPtr3->RCTime>0){
                        processPtr3->RCTime--;
                        countingStatus++;
                        AddingTT(countingStatus,processPtr3->index);
                        
                        if(processPtr3->RCTime==0){
                            processPtr3->active=0;
                            break;
                        }
                    }
                }
            }
            
            processPtr3=processPtr3->next;
        }
    }
    
    //calculating ATT
    
    processIndex processPtr4 = new process;
    processPtr4 = head;
    
    while(processPtr4!=NULL){
        ATT = ATT + processPtr4->TT;
        processPtr4=processPtr4->next;
    }
    
    ATT = ATT/nProcess;
    cout<<"ATT_FIFO : "<<ATT<<endl;
    return ATT; 
}


double PCB::countingATT_SJF(){
    
    //counting number of process
    int nProcess=0;
    processIndex processPtr1 = new process;
    processPtr1 = head;
    
    while(processPtr1!=NULL){
        nProcess++;
        processPtr1=processPtr1->next;
    }
    
    double ATT=0.0;
    int ArrTimeCompare[nProcess]; //array of every ArrTime
    int j = 0;
    int countingStatus = 0;
       
    
    
    //making an array of Arrival times to compare
    curr=head;
    while(curr != NULL){
        ArrTimeCompare[j]=curr->ArrTime;
        j++;
        curr=curr->next;
    }
       
    //sorting ArrTimeCompare[] in order
    sortArray(ArrTimeCompare, nProcess);
    
    
    countingStatus = ArrTimeCompare[0];
    int gap = 0;
    
    for(int i=0; i<nProcess; i++){
        
        //adjusting countingStatus to catch up the gap
        gap = ArrTimeCompare[i]-countingStatus;
        
        if(gap>0){
            countingStatus = countingStatus + gap;
        }
        
        
        if(i==0){
            processIndex processPtr2 = new process;
            processPtr2 = head;
            processIndex processPtr3 = new process;
            processPtr3 = head;
            
            //find the process that has the first arrival time
            while(processPtr3!=NULL){
                if(ArrTimeCompare[i]==processPtr3->ArrTime){
                    processPtr2 = processPtr3;
                    //comparing RCTime of processes that have the same Arrival times.
                    temp = head;
                    while(temp!=NULL){
                        if((temp->RCTime < processPtr3->RCTime)&&(temp->ArrTime==processPtr3->ArrTime)){
                            processPtr2 = temp;
                        }
                        temp = temp->next;
                    }
                    
                    if(processPtr2->RCTime<=0){
                        processPtr2->active=0;
                    }
                    break;
                }
                processPtr3=processPtr3->next;
            }
            
            //
            cout<<"$$$$$$$$$$$$$$$"<<endl;
            cout<<"index : \t"<<processPtr2->index<<endl;
            cout<<"RCT : \t"<<processPtr2->RCTime<<endl;
            cout<<"active : \t"<<processPtr2->active<<endl;
            cout<<"TT : \t"<<processPtr2->TT<<endl;
            cout<<"$$$$$$$$$$$$$$$"<<endl;
            //
            
            //process the RCTime of the process picked above
            while(processPtr2->RCTime>0){
                processPtr2->RCTime--;
                countingStatus++;
                AddingTT(countingStatus,processPtr2->index);
                
                if(processPtr2->RCTime==0){
                    processPtr2->active=0;
                    break;
                }
            }
        }
        else{
            
            processIndex processPtr = new process;
            processPtr = shortestRCT(countingStatus);
            
            //
            cout<<"$$$$$$$$$$$$$$$"<<endl;
            cout<<"index : \t"<<processPtr->index<<endl;
            cout<<"RCT : \t"<<processPtr->RCTime<<endl;
            cout<<"active : \t"<<processPtr->active<<endl;
            cout<<"TT : \t"<<processPtr->TT<<endl;
            cout<<"$$$$$$$$$$$$$$$"<<endl;
            //
            if(processPtr->RCTime<=0){
                processPtr->active=0;
            }
            else{
                while(processPtr->RCTime>0){
                   processPtr->RCTime--;
                    countingStatus++;
                    AddingTT(countingStatus,processPtr->index);
                    
                    if(processPtr->RCTime==0){
                        processPtr->active=0;
                        break;
                    }
                }
            }
        }
    }
     
    //calculating ATT
    while(head!=NULL){
        ATT = ATT+head->TT;
        head=head->next;
    }
    ATT = ATT/nProcess;
    cout<<"ATT_SJF : "<<ATT<<endl;
    return ATT;
}


double PCB::countingATT_SRT(){
    
    //counting number of process
    int nProcess=0;
    processIndex processPtr1 = new process;
    processPtr1 = head;
    
    while(processPtr1!=NULL){
        nProcess++;
        processPtr1=processPtr1->next;
    }
    //
    double ATT=0.0;
    int ArrTimeCompare[nProcess]; //array of every ArrTime
    int j = 0;
    int countingStatus = 0;
       
    //making an array of Arrival times to compare
    processIndex processPtrForArray = new process;
    processPtrForArray=head;
       
    while(processPtrForArray != NULL){
        ArrTimeCompare[j]=processPtrForArray->ArrTime;
        j++;
        processPtrForArray=processPtrForArray->next;
    }
    
    //sorting ArrTimeCompare[] in order
    sortArray(ArrTimeCompare, nProcess);
    
    
   
    countingStatus = ArrTimeCompare[0];
    int timeInterval;
    
    for(int i =0; i<nProcess; i++){
        cout<<"for 번수 : "<<i<<endl;
        processIndex MinRCTProcessPtr = new process;
        
       //countingStatus가 ArrTimeCompare[i]보다 더 진행되어진 상태..--------->>>>>>>>>>
        
        
        if(i<nProcess-1){
            
            //--
            timeInterval = ArrTimeCompare[i+1]-ArrTimeCompare[i];
                   
            if(i>0){
                    
                if(timeInterval>0){
                    countingStatus = ArrTimeCompare[i];
                }
                       
                cout<<"counting Status check : "<<countingStatus<<endl;
                //finding a process that contains the shortest RCT in a range of Arrival time order.
                //MinRCTProcessPtr is the process that has the shortest RCTime now.
                MinRCTProcessPtr = shortestRCT_SRT(countingStatus);
                
                //
                if(MinRCTProcessPtr!=NULL){//++
                cout<<"$$$$$$$$-----$$$$$$$"<<endl;
                cout<<"index : \t"<<MinRCTProcessPtr->index<<endl;
                cout<<"RCT : \t"<<MinRCTProcessPtr->RCTime<<endl;
                cout<<"active : \t"<<MinRCTProcessPtr->active<<endl;
                cout<<"TT : \t"<<MinRCTProcessPtr->TT<<endl;
                cout<<"$$$$$$$$$$$$$$$"<<endl;
                }//++
                //
                       
            }
            //--
            
            //if{timeinterval}--timeInterval = ArrTimeCompare[i+1]-ArrTimeCompare[i];
            
            if(MinRCTProcessPtr!=NULL){//++
                if(timeInterval>0){
                    cout<<"timeInterval : "<<timeInterval<<endl;
                //finding out the process that has the earliest Arrival Time
                    if(i==0){
                        cout<<"countingStatus(i==0) : "<<countingStatus<<endl;
                        cout<<"i==0"<<endl;
                        processIndex processPtrFor0 = new process;
                        processPtrFor0 = head;
                        while(processPtrFor0!=0){
                            if(processPtrFor0->index == i){
                                MinRCTProcessPtr = processPtrFor0;
                            }
                            processPtrFor0 = processPtrFor0->next;
                        }
                        //
                        cout<<"$$$$$$$$$$$$$$$"<<endl;
                        cout<<"index : \t"<<MinRCTProcessPtr->index<<endl;
                        cout<<"RCT : \t"<<MinRCTProcessPtr->RCTime<<endl;
                        cout<<"active : \t"<<MinRCTProcessPtr->active<<endl;
                        cout<<"TT : \t"<<MinRCTProcessPtr->TT<<endl;
                        cout<<"$$$$$$$$$$$$$$$"<<endl;
                        //
                    }
                //
                
                /*
                timeInterval = ArrTimeCompare[i+1]-ArrTimeCompare[i];
                cout<<"timeInterval : "<<timeInterval<<endl;
                //what if timeInterval is 0?
                */
                
                    //if MinRCTProcessPtr's RCTime is bigger than timeInterval--->>
                    if(MinRCTProcessPtr->RCTime>=timeInterval){
                        cout<<"BIGGER"<<endl;
                        
                        while(timeInterval>0){
                            MinRCTProcessPtr->RCTime--;
                            countingStatus++;
                            timeInterval--;
                            AddingTT(countingStatus, MinRCTProcessPtr->index);
                            
                            if(MinRCTProcessPtr->RCTime==0){
                                MinRCTProcessPtr->active=0;
                                break;
                            }
                        }
                        
                    }
                    //if MinRCTProcessPtr's RCTime is smaller than timeInterval
                    else{
                        cout<<"SMaller"<<endl;
                        int RemainToNextArr=0;
                        int progressCount = 0;
                        
                        while(MinRCTProcessPtr->RCTime>0){
                            MinRCTProcessPtr->RCTime--;
                            countingStatus++;
                            progressCount++;
                            AddingTT(countingStatus, MinRCTProcessPtr->index);
                            
                            if(MinRCTProcessPtr->RCTime==0){
                                MinRCTProcessPtr->active=0;
                                break;
                            }
                        }
                        
                        cout<<"countingStaus : "<<countingStatus<<endl;
                        // time remained until reaching to the next arrival time is
                        RemainToNextArr = ArrTimeCompare[i+1] - countingStatus;
                        
                        
                        //find a process that contains the shortest RCTime
                        processIndex fillingGap = new process;
                        fillingGap = shortestRCT_SRT(countingStatus);
                        
                        //using RemainToNextArr. 나머지 GAP 사용
                        cout<<"checking 123"<<endl;
                        if(fillingGap!=NULL){
                            cout<<"fillingGap!=NULL"<<endl;
                            while(RemainToNextArr>0){
                                cout<<"remainToNextArr : "<<RemainToNextArr<<endl;
                                
                                fillingGap->RCTime--;
                                RemainToNextArr--;
                                countingStatus++;
                                AddingTT(countingStatus, fillingGap->index);
                                if(fillingGap->RCTime==0){
                                    fillingGap->active=0;
                                    fillingGap = shortestRCT_SRT(countingStatus);
                                }
                                if((RemainToNextArr<=0)||(!shortestRCT_SRT(countingStatus))){
                                    break;
                                }
                            }
                        }
                    }
                }//if
            }//++
        }
        //for the last arrival time in the array
        else if(i==nProcess-1){
            
            //--
                   
            if(i>0){
                    
                if(countingStatus<=ArrTimeCompare[i]){
                    countingStatus = ArrTimeCompare[i];
                }
                
                cout<<"counting Status check : "<<countingStatus<<endl;
                //finding a process that contains the shortest RCT in a range of Arrival time order.
                //MinRCTProcessPtr is the process that has the shortest RCTime now.
                MinRCTProcessPtr = shortestRCT_SRT(countingStatus);
                //
                if(MinRCTProcessPtr!=NULL){//++
                cout<<"$$$$$$$$-----$$$$$$$"<<endl;
                cout<<"index : \t"<<MinRCTProcessPtr->index<<endl;
                cout<<"RCT : \t"<<MinRCTProcessPtr->RCTime<<endl;
                cout<<"active : \t"<<MinRCTProcessPtr->active<<endl;
                cout<<"TT : \t"<<MinRCTProcessPtr->TT<<endl;
                cout<<"$$$$$$$$$$$$$$$"<<endl;
                }//++
                //
                       
            }
            //--
            if(MinRCTProcessPtr!=NULL){//++
                while(MinRCTProcessPtr->RCTime>0){
                    MinRCTProcessPtr->RCTime--;
                    countingStatus++;
                    AddingTT(countingStatus, MinRCTProcessPtr->index);
                    if(MinRCTProcessPtr->RCTime==0){
                        MinRCTProcessPtr->active=0;
                        break;
                    }
                }
            }//++
        }
    }
    
    //Dealing with process that has leftover RCTime.
    processIndex DealLeftover = new process;
    while(shortestRCT_SRT(countingStatus)){
        DealLeftover = shortestRCT_SRT(countingStatus);
        while(DealLeftover->RCTime>0){
            DealLeftover->RCTime--;
            countingStatus++;
            AddingTT(countingStatus, DealLeftover->index);
            if(DealLeftover->RCTime==0){
                DealLeftover->active = 0;
            }
        }
    }
    
    //calculating ATT
    while(head!=NULL){
        ATT = ATT+head->TT;
        head=head->next;
    }
    
    ATT = ATT/nProcess;
    cout<<"ATT_SRT : "<<ATT<<endl;
    return ATT;
}


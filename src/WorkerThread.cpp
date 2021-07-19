#include <chrono>
#include <iostream>
#include "WorkerThread.h"
#include <fstream>
#include <string>

using namespace std;

//to access queue
extern SyncQueue Qobject;

WorkerThread :: WorkerThread(int WThCount):WorkThreadCount(WThCount){
    MTable.clear();
    t.resize(WThCount);
}

WorkerThread :: ~WorkerThread(){
}

/*
Name: CreateThreeWorkerThread()
Description: This function creates three worker thread
Parameter: NA
Return Value: NA
*/
void WorkerThread :: CreateThreeWorkerThread(){
   
   /* Create three threads */
   for(unsigned int i =0;i<(unsigned int)WorkThreadCount;i++){
      t[i] = std::thread (&WorkerThread::FillMTable,this);
      t[i].detach();
     }
}

bool isNumber(string str){
    while(str.size()!=0 and str.back()==' ')
        str.pop_back();

    for(char c:str){
        if((c>='0' and c<='9')) {}
        else
            return false;
    }
    return true;
}

bool isBeVerd(string str){
    if(str=="is" || str=="are" || str=="were" || str=="was" || str=="have" || str=="has" 
        || str=="will" || str=="shall" || str=="would" || str=="should" || str=="being"
        || str=="may" || str=="might" || str=="must" || str=="can" || str=="could"  || 
        str=="Is" || str=="Are" || str=="Were" || str=="Was" || str=="Have" || str=="Has"
        || str=="May" || str=="Can" || str=="more" || str=="most" || str=="some")
        return true;

    return false;
}

bool isPreposition(string str){
    if(str=="to" || str=="behind" || str=="up" || str=="down" || str=="from" || str=="top" 
        || str=="bottom" || str=="into" || str=="inside" || str=="besides" || str=="onto" ||
        str=="upwards" || str=="downwords" || str=="towards" || str=="between" || str=="among"
        || str=="left" || str=="right" || str=="out" || str=="by" || str=="of" || str=="In" ||
        str=="since" || str=="then" || str=="in"  || str=="on" || str=="with" || str=="for"
        || str=="at" || str=="At" || str=="If" || str=="if" || str=="For" || str=="than" ||
        str=="To" || str=="away" || str=="On" || str=="each" || str=="every" || str=="but")
            return true;
    return false;
} 

bool isPronouns(string str){
    if(str=="i" || str=="we" || str=="he" || str=="she" || str=="you" || str=="ours" ||
            str=="Our" || str=="yours" || str=="your" || str=="myself" || str=="ourself" ||
            str=="nobody" || str=="anybody" || str=="noone" || str=="anyone" || str=="everybody"
            || str=="somebody" || str=="someone" || str=="very" || str=="few" || str=="this" ||
            str=="that"  || str=="there" || str=="his" || str=="their" || str=="her" || str=="another"
            || str=="be" || str=="it" || str=="our" || str=="him" || str=="they" || str=="or"
            || str=="as" || str=="many" || str=="any" || str=="all" || str=="own" || str=="too"
            || str=="them" || str=="these")
            return true;
    return false;
}

bool isWh(string str){
    if(str=="when" || str=="When" || str=="where" || str=="Where" || str=="what" || str=="What"
        || str=="How" || str=="how" || str=="which" || str=="Which" || str=="had")
        return true;
    return false;
}
bool isCommonWord(string str){
    int sz=str.size();
    for(int i=0;i<sz;i++){
        if(str[i]>='A' and str[i]<='Z')
            str[i]+=32;
    }
    if(isPreposition(str))
        return true;
    else if(str=="a" || str=="the" || str=="am" || str=="\"" || str=="\'" || str=="(" || str==")"
            || str=="[" || str=="]" || str=="{" || str=="}" || str=="\\" || str=="|" || str=="%"
            || str=="off" || str=="it" || str=="other" || str=="as" || str=="not" || str=="&"  
            || str=="and" || str=="so" || str=="i" || str=="an" || str=="s")
        return true;
    else if(isWh(str))
        return true;
    else if(isPronouns(str))
        return true;
    else if(isBeVerd(str))
        return true;
    
    return false;
}

/*
Name: AddWordtoMTable()
Description: This function adds words to MTable
Parameter: string str    word read from file
Return Value: NA
*/
void WorkerThread :: AddWordtoMTable(std:: string str){

    //WorkThMutexobj.lock();
    unique_lock<mutex> lock1(WorkThMutexobj,defer_lock);
    lock1.lock();
    map<string, int>::iterator it = MTable.find(str);
    if(isNumber(str)){
        // Numbers are not important data to analyze
        //cout<<"----"<<str<<"----"<<endl;
    }
    else if(isCommonWord(str)){
        // Common Words are not important data to analyze
    }
    else if (it != MTable.end())
        it->second = it->second+1;
    else{
        MTable.insert(std::make_pair(str, 1));  
    } 
    lock1.unlock();
    //WorkThMutexobj.unlock();
}

/*
Name: FillMTable()
Description: This function reads the file and calls AddWordtoMTable() function
Parameter: NA
Return Value: NA
*/
void  WorkerThread :: FillMTable(){
   while(1){
       string filename= Qobject.GetFilefrmQ();
       if(!filename.empty()){
           ifstream  file (filename.c_str());
           string line;
           
           if (file.is_open()){  
               while ( getline (file,line)){
                   std::size_t prev = 0, pos;
                   while ((pos = line.find_first_of("~`=!@#$%^&*)/\?-_|[,. }](_-+{;':""></", prev)) != std::string::npos){
                       if (pos > prev){
                           AddWordtoMTable(line.substr(prev, pos-prev));
                       }
                   prev = pos+1;
                   }
                   if (prev < line.length()){
                       AddWordtoMTable(line.substr(prev, std::string::npos));
                   }
               }

           file.close();
           }
           else{
               cout << "-Unable to open file-" << endl;
           }
       } 
   }
}

/*
Name: getTableEntry()
Description: This function returns the MTable
Parameter: NA
Return value: multimap<int,string,greater<int>>    a sorted multimap
*/
multimap<int,string,greater<int>> WorkerThread:: getTableEntry(){   
   multimap<int ,string,greater<int>> mmtbl;
   mmtbl.clear();
   map<string,int>::iterator iter; 
         for(iter=MTable.begin(); iter!=MTable.end(); ++iter){
             mmtbl.insert(make_pair(iter->second,iter->first));
         }
  return mmtbl;
}

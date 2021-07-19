#include "SyncQueue.h"

SyncQueue :: SyncQueue(){
    CountFileSize = 0;
}

SyncQueue :: ~SyncQueue(){
}

/*
Name: AddFileNameinQ()
Description: This function add filepath to synchornized queue
Parameter: string filepath
Return value: NA
*/ 
void SyncQueue :: AddFileNameinQ(string filepath){
    MutexObject.lock();
    Queue.push(filepath);
    CountFileSize++;
    MutexObject.unlock();
}

/*
Name: GetFilefrmQ()
Description: This function read the filepath from synchronized queue
Parameter: NA
Return value : string    filepath
*/
string SyncQueue :: GetFilefrmQ(){
    string filename="";
    //MutexObject.lock();
    unique_lock<mutex> lock1(MutexObject,defer_lock);
    lock1.lock();
    if(!Queue.empty()){
        filename = Queue.front();
        Queue.pop();
    }
    lock1.unlock();
    //MutexObject.unlock();
    return filename;
}

/*
Name: GetCount()
Description: This function returns the size of synchronized queue
             This check is required before fetching filepath from queue
Parameter: NA
Return value: int
*/
int SyncQueue :: GetCount(){
    int CountSize = 0;
    CountSize=Queue.size();
    return CountSize;
}

/*
Name: GetFileCount()
Description: This function returns the total number of file processed by synchornized queue
Parameter: NA
Return value: int
*/
int SyncQueue :: GetFileCount(){
    return CountFileSize;
}

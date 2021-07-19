//File : Queue.h
//Desc : This creates queue to to store .txt files. SearchThread fill this queue untill the searching is over.
//Date : Jan 2018
//Author : Pranab Nandy

#ifndef SYNCQUEUE_H
#define SYNCQUEUE_H

#include <string>
#include <mutex>
#include <queue>
#include <iostream>

using namespace std;

class SyncQueue{
	public:  
		SyncQueue();
	    ~SyncQueue();
	    
        /*writes filename in Queue */  
		void AddFileNameinQ(string filename); 

       /*reads the filename from Queue and returns the filename */
		string GetFilefrmQ(void);
                       
        /*returns nubmer of files present queue*/ 
	    int GetCount();
                
        /*returns number of files processed by queue*/
        int GetFileCount();
                                
   
    private :
    //mutext object for synchronization on queue
    mutex MutexObject;
 
    //synchronized queue to save filename. This queue is processed by Searchthread and Workerthread  
    queue <string> Queue;
                
    //store number of files processed by queue       
    int CountFileSize; 
};
#endif /* QUEUE_H */

#include "SearchThread.h"
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>
#include <fnmatch.h>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <iterator>
#include <iostream>

using namespace std;

//to access Queue object
extern SyncQueue Qobject;

//filter to search only .txt file
static const char * filter = "*.txt";

//SearchFinished flag is set when search of .txt file is over
extern unsigned char SearchFinishedFlag;


SearchThread :: SearchThread(){

}

SearchThread :: ~ SearchThread(){

}
/*
Name: StartSearchTxtFiles()
Description: This funcion search for all .txt file in specified path
Parameter: string filepath    path of directory
Return Value: int 
*/
int SearchThread :: StartSearchTxtFiles(string filepath){

    ftw(filepath.c_str(),SearchThread::callback, 16);

    //if Serach is over then SearchFinishedFlag =1
    SearchFinishedFlag = 1;
    return SearchFinishedFlag;
}

int SearchThread:: callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_F) {
        if(fnmatch(filter, fpath, FNM_CASEFOLD) == 0) {               
		     Qobject.AddFileNameinQ(fpath);
        }
    }
    return 0;
}

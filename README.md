# Multi-threaded-Word-Ranking-Apllication
Created a multi-threaded text ﬁles’ word ranking command line application in C++. Here Search Thread is responsible for searching all the text
ﬁles in the given directory and its subdirectories while other 5 Worker Threads do the processing of the searched ﬁles from Sync Queue simultaneously and store the results in Master Table data strucrure.


<h1> System Design </h1>


![Methodology](/Image/first1.PNG)

# Modules

There are three modules SerachThread, SyncQueue and WorkerThread.

## SearchThread

This module search for .txt file in the path specified as command line argument. In addition, it sends file to SyncQueue module. SearchThread stop working once searching is over.

## SyncQueue

This module send the file in a synchronized Queue. This module provides file to WorkerThread module for processing. SyncQueue provides access of its Queue to only one WorkerThread at a time.

## WorkerThread

This module has  5 workerthread and each thread get the file to process from SyncQueue module.After getting the file, each workerthread reads the file and fetch words to save in a data structure called Master Table. Master Table is a data structure, which contains words with their frequency.

Once the file search is complete and all text files finish processing, the program prints out the top 10 words
and their counts.We just want to find the top 10 words across a directory tree of text files.

# How to run the program

**$ make**

**$ ./wordindex.out DIR**


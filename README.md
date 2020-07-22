# Implementing file system crawler, indexer and search engine
## File Parser
parse a text file to individual words
| Program Files | |
| --- | --- |
| [FileParser.h](https://github.com/bellaroseee/SysProg-hw2/blob/master/FileParser.h) | header file for parsing file |
| [FileParser.c](https://github.com/bellaroseee/SysProg-hw2/blob/master/FileParser.c) | implementation for file parser |

| Test Files | |
| --- | --- |
| [test_fileparser.cc](https://github.com/bellaroseee/SysProg-hw2/blob/master/test_fileparser.cc) | unit test for file parser | 
## File System Crawler and Indexer
| Program Files | |
| --- | --- |
| [DocTable.h](https://github.com/bellaroseee/SysProg-hw2/blob/master/DocTable.h) | header file for Document Table <br/> filenames and document IDs |
| [DocTable.c](https://github.com/bellaroseee/SysProg-hw2/blob/master/DocTable.cc) | implementation for Document Table |
| [CrawlFileTree.h](https://github.com/bellaroseee/SysProg-hw2/blob/master/CrawlFileTree.h) | header file for Directory Crawler |
| [CrawlFileTree.c](https://github.com/bellaroseee/SysProg-hw2/blob/master/CrawlFileTree.c) | implementation for Directory Crawler |
| [MemIndex.h](https://github.com/bellaroseee/SysProg-hw2/blob/master/MemIndex.h) | heder file for Memory Inverted Index |
| [MemIndex.c](https://github.com/bellaroseee/SysProg-hw2/blob/master/MemIndex.c) | implementation for Memory Inverted Index |

| Test Files | |
| --- | --- |
| [test_doctable.cc](https://github.com/bellaroseee/SysProg-hw2/blob/master/test_doctable.cc) | unit test for doctable |
| [test_crawlfiletree.cc](https://github.com/bellaroseee/SysProg-hw2/blob/master/test_crawlfiletree.cc) | unit test for file crawler | 
| [test_memindex.cc](https://github.com/bellaroseee/SysProg-hw2/blob/master/memindex.cc) | unit test for memory indexer |
## Search Engine
| Program Files | |
| --- | --- |
| [searchshell.c](https://github.com/bellaroseee/SysProg-hw2/blob/master/searchshell.cc) | query processor <br/> process a query and return a list of matching documents |

## Test Result
![alt_text](https://raw.githubusercontent.com/bellaroseee/SysProg-hw2/master/public/hw2-test-.jpg)

## Memory Check
![alt_text](https://raw.githubusercontent.com/bellaroseee/SysProg-hw2/master/public/memory-check.jpg)

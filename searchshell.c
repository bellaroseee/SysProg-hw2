/*
 * Copyright ©2020 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2020 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

#define MAX_INPUT_SIZE 1024

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);


// Search the parsed user query in the index, printing out
// the file path and the rank.
//
// Arguments:
// - dt: Doctable database
// - mi: MemIndex to search result
// - query: parse and tokenized user query
// - qlen: length of query
//
// Returns: none
static void ProcessQueries(DocTable *dt, MemIndex *mi, char **query, int qlen);

// Read query from stdin and split the query into word
// tokens.
//
// Arguments:
// - f: the stream to read user input from
// - query: query entered by user when prompted
// - retstr: output parameter to return user input
//
// Returns:
// - retstr: parsed user input
// - length of query
static int GetNextLine(FILE *f, char **query, char *retstr);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char **argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.

  char* rootdir;
  DocTable *doctable;
  MemIndex *index;

  rootdir = argv[1];
  printf("Indexing \'%s\'\n", rootdir);

  // start crawling from a directory
  if (!CrawlFileTree(rootdir, &doctable, &index)) {
    fprintf(stderr, "Failed to crawl the directory.\n");
    Usage();
  }

  // holds the query entered by user
  char **query = (char**) malloc(MAX_INPUT_SIZE);
  // holds the return string from query processing in GetNextLine
  char *retstr = (char*) malloc(MAX_INPUT_SIZE);
  int qlen;

  while (1) {
    printf("enter query:\n");

    qlen = GetNextLine(stdin, query, retstr);
    if (qlen == 0) {
      // if user entered ctrl-d
      // Free everything
       DocTable_Free(doctable);
       MemIndex_Free(index);
       free(query);
       free(retstr);
       fprintf(stderr, "Failed to get query.\n");
       Usage();
    }

    ProcessQueries(doctable, index, query, qlen);
  }

  // free everything
  DocTable_Free(doctable);
  MemIndex_Free(index);
  free(query);
  free(retstr);

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable *dt, MemIndex *mi, char **query, int qlen) {
  LinkedList *retlist;
  SearchResult *result;
  LLIterator *llit;

  retlist = MemIndex_Search(mi, (char**) query, qlen);
  // if MemIndex_Search is not successful, retuns.
  if (retlist == NULL) {
    return;
  }

  // allocate LLiterator
  llit = LLIterator_Allocate(retlist);

  while (LLIterator_IsValid(llit)) {
    // for each result in retlist, print the path and the rank
    LLIterator_Get(llit, (LLPayload_t) &result);
    // get path from DocTable with docid
    printf(" %s (%u)\n", DocTable_GetDocName(dt, result->docid), result->rank);
    LLIterator_Next(llit);
  }

  // free everything
  LLIterator_Free(llit);
  LinkedList_Free(retlist, &free);
  return;
}

static int GetNextLine(FILE *f, char **query, char* retstr) {
  int i;

  if (fgets(retstr, MAX_INPUT_SIZE-1, f) != NULL) {
    // remove '\n'
    *(retstr + (strlen(retstr) - 1)) = '\0';

    // convert input queries to lower case words
    i = 0;
    char *temp = retstr;
    while (i < strlen(retstr)) {
      *(retstr + i) = tolower(*(retstr+i));
      i++;
    }

    // populate the query with token
    i = 0;
    while ((*(query+i) = strtok_r(temp, " ", &temp))) {
      i++;
    }

    // retuns the query length
    return i;
  }
  return 0;
}

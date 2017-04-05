#include <stdio.h>
#include <stdlib.h>

#include "log.h"

int logCreated = 0;

void Log(char *msg)
{
  FILE *file;

  if(!logCreated){
    file = fopen(LOGFILE, "w");
    logCreated = 1;
  }
  else{
    file = fopen(LOGFILE, "a");
  }

  if(file == NULL){
    if(logCreated){
      logCreated = 0;
    }
    return;
  }
  else{
    fputs(msg, file);
    fclose(file);
    file = NULL;
  }

  if(file != NULL){
    fclose(file);
    file = NULL;
  }
}

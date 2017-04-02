#ifndef LIBLOADER_H
  #define LIBLOADER_H

  #include "interface.h"

  typedef int (*playT)(int, const SMap*, STurn*);
  typedef void (*initG)(unsigned int, unsigned int, SPlayerInfo*);
  typedef void (*endG)(unsigned int, unsigned int);

  void** loadLib(int nbLib, char *argv[], initG initTab[], playT playTab[], endG endTab[]);
  void freeLib(void **libs, int nbLib);

#endif

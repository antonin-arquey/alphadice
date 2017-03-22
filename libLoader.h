#ifndef LIBLOADER_H
  #define LIBLOADER_H

  #include "interface.h"

  typedef int (*playT)(int, const SMap*, STurn*);
  typedef void (*initG)(unsigned int, unsigned int, SPlayerInfo*);

  void** loadLib(int nbLib, char *lib1, char *lib2, initG initTab[], playT playTab[]);
  void freeLib(void **libs, int nbLib);

#endif

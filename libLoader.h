#ifndef LIBLOADER_H
  #define LIBLOADER_H

  typedef int (*playT)(int, const SMap*, STurn*);
  typedef void (*initG)(unsigned int, unsigned int, SPlayerInfo*);

  void** loadLib(int nbLib, char *argv[], initG initTab[], playT playTab[]);
  void freeLib(void **libs, int nbLib);

#endif

#ifndef H_GL_UTILS
#define H_GL_UTILS

//Pour x == 0 parfait pour malloc/calloc et tout les appels systèmes
#define CHK(x) \
  do { \
    if (!(x)) { \
      fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
	  if(errno==0) errno=ECANCELED; \
      perror(#x); \
      exit(EXIT_FAILURE); \
    } \
  } while (0)

//Pour x < 0 parfait pour les erreurs de socket
#define CHKNEG(x) \
  do { \
    if ((x) < 0) { \
      fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
	  if(errno==0) errno=ECANCELED; \
      perror(#x); \
      exit(EXIT_FAILURE); \
    } \
  } while (0)


#endif  // H_GL_UTILS 
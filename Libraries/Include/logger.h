#include <stdio.h>
#ifdef LOG
#define DEBUG(x) fprintf(stdout, "%s:%d:%s DEBUG:%s", __FILE__, __LINE__, __func__, x)
#define ERROR(x) fprintf(stderr, "%s:%d:%s ERROR:%s", __FILE__, __LINE__, __func__, x)
#else
#define DEBUG(x)
#define ERROR(x)
#endif
#ifndef UTILS_H
#define UTILS_H

#define LOGGING(...) printf(__VA_ARGS__)
#define ASSERT_LOGGING(cond,...) if(cond){printf(__VA_ARGS__);}
#define ERROR_LOGGING(...) fprintf(stderr,__VA_ARGS__)
#endif
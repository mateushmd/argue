#ifndef ARGUE_H
#define ARGUE_H

#define BYTE_ARG "<b>"
#define UBYTE_ARG "<ub>"
#define SHORT_ARG "<s>"
#define USHORT_ARG "<us>"
#define INT_ARG "<i>"
#define UINT_ARG "<ui>"
#define LONG_INT_ARG "<li>"
#define ULONG_INT_ARG "<uli>"
#define LONG_LONG_INT_ARG "<lli>"
#define ULONG_LONG_INT_ARG "<ulli>"
#define FLOAT_ARG "<f>"
#define DOUBLE_ARG "<d>"
#define CHAR_ARG "<c>"
#define STRING_ARG "<str>"
#define NO_ARG "<no>"

typedef struct
{
    int required;
    char *simplified;
    char *verbose;
    char *rhs;
    void *argPtr;
} Arg;

typedef struct
{
    int size;
    int cur;
    int argc;
    char **argv;
    Arg *args;
} ArgueContext;

ArgueContext *argue_createContext(int argc, char **argv, int possibleArgs);

int argue_addArg(ArgueContext *context, const char *simplified,
                 const char *verbose, const char *rhs, int required,
                 void *argPtr);

int argue_parse(ArgueContext *context);

char *argue_getError(const char *prefix);

#endif

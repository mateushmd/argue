#include "argue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *errorMessage;

int toByte(char *v, char *ptr) {}
int toUByte(char *v, unsigned char *ptr) {}
int toShort(char *v, short *ptr) {}
int toUShort(char *v, unsigned short *ptr) {}
int toInt(char *v, int *ptr) {}
int toUInt(char *v, unsigned int *ptr) {}
int toLInt(char *v, long int *ptr) {}
int toULInt(char *v, unsigned long int *ptr) {}
int toLLInt(char *v, long long int *ptr) {}
int toULLInt(char *v, unsigned long long int *ptr) {}
int toFloat(char *v, float *ptr) {}
int toDouble(char *v, double *ptr) {}
int toChar(char *v, char *ptr) {}
int toString(char *v, char **ptr) {}

ArgueContext *argue_createContext(int argc, char **argv, int possibleArgs)
{
    ArgueContext *context = malloc(sizeof(ArgueContext));

    if (context == NULL)
    {
        errorMessage = "failed to create context";
        return NULL;
    }

    context->size = possibleArgs;
    context->cur = 0;
    context->argc = argc;
    context->argv = argv;
    context->args = malloc(possibleArgs * sizeof(Arg));

    if (context->args == NULL)
    {
        errorMessage = "failed to create context";
        return NULL;
    }

    return context;
}

int argue_addArg(ArgueContext *context, const char *simplified,
                 const char *verbose, const char *rhs, int required,
                 void *argPtr)

{
    if (!simplified && !verbose)
    {
        errorMessage = "neither simplified nor verbose names were set";
        return 0;
    }

    if (!rhs)
    {
        errorMessage = "right hand side pattern not set";
        return 0;
    }

    if (!strncmp(rhs, NO_ARG, strlen(rhs)) && !argPtr)
    {
        errorMessage = "argument expects a value but no pointer was set";
        return 0;
    }

    int cur = context->cur;
    Arg *arg = &context->args[cur];
    arg->required = required;
    if (simplified)
        strncpy(arg->simplified, simplified, strlen(simplified));
    if (verbose)
        strncpy(arg->verbose, verbose, strlen(verbose));
    if (rhs)
        strncpy(arg->rhs, rhs, strlen(rhs));
    if (argPtr)
        arg->argPtr = argPtr;

    return 1;
}

char *argue_getError(const char *prefix)
{
    if (errorMessage == NULL)
        return NULL;

    char *msg;
    size_t tSize = strlen(errorMessage);

    if (!prefix)
    {
        strncpy(msg, errorMessage, tSize);
        return msg;
    }

    tSize += strlen(prefix);
    snprintf(msg, tSize, "%s: %s", prefix, errorMessage);
    return msg;
}

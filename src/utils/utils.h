#ifndef UTILS_H
#define UTILS_H

#include<stdlib.h>
#include<stdio.h>

#define LOGGING(...) printf(__VA_ARGS__)
#define ASSERT_LOGGING(cond,...) if(cond){printf(__VA_ARGS__);}
#define ERROR_LOGGING(...) fprintf(stderr,__VA_ARGS__)

#define GL_COLOR_RED 1.0f,0.0f,0.0f
#define GL_COLOR_GREEN 0.0f,1.0f,.0f
#define GL_COLOR_BLUE 0.0f,0.0f,1.0f
#define GL_COLOR_GRAY 0.5f,0.5f,0.5f
#define GL_COLOR_WHITE 1.0f,1.0f,1.0f
#define GL_COLOR_BLACK 0.0f,0.0f,0.0f

#ifdef SHADER_H

char* ReadFile(const char* file_path)
{
    FILE* file = fopen(file_path, "r");
    
    if(file == NULL)
        ERROR_LOGGING("file couldn't be opened.\n");
    
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    char* result = (char*)malloc(size + 1);

    int i = 0;
    int c = 0;
    while((c = fgetc(file)) != EOF)
    {
        result[i] = (char)c;
        ++i;
    }

    result[i] = '\0';
    
    fclose(file);

    return result;
}

#endif

#endif
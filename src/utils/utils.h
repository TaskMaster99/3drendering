#ifndef UTILS_H
#define UTILS_H

#define LOGGING(...) printf(__VA_ARGS__)
#define ASSERT_LOGGING(cond,...) if(cond){printf(__VA_ARGS__);}
#define ERROR_LOGGING(...) fprintf(stderr,__VA_ARGS__)

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
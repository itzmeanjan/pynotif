#include<unistd.h>

int does_file_exist(char *file){ // validates existence of file path, returns 1 on success and 0 on failure.
    return (access(file, F_OK)==0);
}
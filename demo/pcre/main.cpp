#include <pcre.h>
#include <iostream>
#include <pcreposix.h>
#include <string.h>

int main(int argc, char** argv){
    int options = REG_ICASE;
    const char *error;
    int err_offset=0;
    std::cout<<"REG:"<<argv[1]<<std::endl;
    std::cout<<"URL:"<<argv[2]<<std::endl;
    pcre* regex = pcre_compile(argv[1], options, &error, &err_offset, NULL);
    int match_vector[3];
    int rc = pcre_exec(regex, NULL, argv[2], strlen(argv[2]), 0, 0, match_vector, 3);
    if(rc>0){
        std::cout<<"matched"<<std::endl;
    } else {
        std::cout<<"not matched"<<std::endl;
    }



    return 0;
}

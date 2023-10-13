#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *message;
    enum {
        OK = 0,
        ERROR_ARGUMENTS,
    } type;
} Error;

void print_error(Error *error) {
    switch (error->type) {
    case ERROR_ARGUMENTS:
        fprintf(stderr, "Arguments error: %s\n", error->message);
        break;
    case OK:
        printf("OK\n");
        break;

    default:
        printf("Unknown error\n");
        break;
    }
}

void test(){
    Error error;
    error.type = OK;
    print_error(&error);

    error.type = ERROR_ARGUMENTS;
    error.message = "Error message";
    print_error(&error);
}

int main(int argc, char **argv) { 
    test();
    return 0; }
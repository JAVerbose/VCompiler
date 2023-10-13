#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define errors
typedef struct {
    char *message;
    enum {
        OK,
        ERROR_ARGUMENTS,
        ERROR_FILE_NOT_FOUND,
        ERROR_MEMORY,
        ERROR_READ_FILE,
        ERROR_EOF,
    } type;
} Error;

#define OK_ERROR ((Error){.type = OK})

void print_help(char **argv) {
    printf("Usage: \n\t%s [options]\n", argv[0]);
    printf("Options:\n");
}

Error NEW_ERROR(int type, char *message) {
    Error error;
    error.type = type;
    error.message = message;
    return error;
}

void print_error(Error *error) {
    switch (error->type) {
    case ERROR_ARGUMENTS:
        fprintf(stderr, "Arguments error: %s\n", error->message);
        break;
    case OK:
        printf("OK\n");
        break;
    case ERROR_FILE_NOT_FOUND:
        fprintf(stderr, "File not found: %s\n", error->message);
        break;
    case ERROR_MEMORY:
        fprintf(stderr, "Memory error: %s\n", error->message);
        break;
    case ERROR_READ_FILE:
        fprintf(stderr, "Read file error: %s\n", error->message);
        break;
    case ERROR_EOF:
        fprintf(stderr, "End of file reached: %s\n", error->message);
        break;
    default:
        printf("Unknown error\n");
        break;
    }
}

void test() {
    Error error;
    error.type = OK;
    print_error(&error);

    error.type = ERROR_ARGUMENTS;
    error.message = "Error message";
    print_error(&error);

    error = NEW_ERROR(ERROR_ARGUMENTS, "Error message");
    print_error(&error);
}

int get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char *read_content(char *filename) {
    FILE *file = fopen(filename, "rb");

    if (!file) {
        Error new_error = NEW_ERROR(ERROR_FILE_NOT_FOUND, filename);
        print_error(&new_error);
        return NULL;
    }

    int file_size = get_file_size(file);
    printf("file_size = %d\n", file_size);
    char *content = malloc(file_size + 1);

    if (!content) {
        Error new_error = NEW_ERROR(ERROR_MEMORY, NULL);
        print_error(&new_error);
        return NULL;
    }

    int file_size_read = fread(content, 1, file_size, file);
    printf("file_size_read = %d\n", file_size_read);

    if (file_size_read == 0) {
        Error new_error = NEW_ERROR(ERROR_READ_FILE, "file_size_read == 0");
        print_error(&new_error);
        return NULL;
    }

    if (file_size_read != file_size) {
        if (feof(file)) {
            Error new_error = NEW_ERROR(ERROR_EOF, "file_size_read != file_size");
            print_error(&new_error);
        } else if (ferror(file)) {
            Error new_error = NEW_ERROR(ERROR_READ_FILE, "ferror(file)");
            print_error(&new_error);
        }
        return NULL;
    }

    content[file_size] = '\0';
    fclose(file);

    return content;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_help(argv);
        return 0;
    }

    char *content = read_content(argv[1]);

    if (!content) {
        return 1;
    }

    printf("%s\n", content);

    free(content);
    return 0;
}
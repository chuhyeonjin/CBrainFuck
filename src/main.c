#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 30000

void PrintError(const char* message) {
  fprintf(stderr, "\033[0;31mError:\033[0m %s\n", message);
}

void PrintWarning(const char* message) {
  printf("\033[0;33mWarning:\033[0m %s\n", message);
}

void ReadFile(const char* path, char** data_pointer, long* size_pointer) {
  FILE* file = fopen(path, "rb");
  long file_size;

  if (file == NULL) {
    PrintError("cannot open file");
    exit(EXIT_FAILURE);
  }

  fseek(file, 0L, SEEK_END);
  file_size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  *size_pointer = file_size;

  *data_pointer = malloc(file_size + 1);
  if (*data_pointer == NULL) {
    PrintError("cannot allocate memory");
    exit(EXIT_FAILURE);
  }

  if (fread(*data_pointer, 1, file_size, file) != file_size) {
    PrintError("cannot read file");
    exit(EXIT_FAILURE);
  }

  fclose(file);
}

char GetAsciiChar() {
  while (1) {
    int character = getchar();

    while (1) {
      if (getchar() == '\n') {
        break;
      }
    }

    if (character > 127) {
      printf("\033[A\33[2K");
    } else {
      return character;
    }
  }
}

int main(int argc, char** argv) {
  char data[MAX_DATA_SIZE] = {0};
  char* code;
  long code_size;
  long data_cursor = 0;
  long code_cursor = 0;

  if (argc < 2) {
    PrintError("no input file");
    exit(EXIT_FAILURE);
  }

  ReadFile(argv[1], &code, &code_size);

  while (1) {
    switch (code[code_cursor]) {
      case '>':
        data_cursor++;
        break;
      case '<':
        data_cursor--;
        break;
      case '+':
        data[data_cursor]++;
        break;
      case '-':
        data[data_cursor]--;
        break;
      case '.':
        putchar(data[data_cursor]);
        break;
      case ',':
        data[data_cursor] = GetAsciiChar();
        break;
      case '[':
        if (data[data_cursor] == 0) {
          long nested = 1;
          while (nested) {
            code_cursor++;
            switch (code[code_cursor]) {
              case '[':
                nested++;
                break;
              case ']':
                nested--;
                break;
            }
          }
        }
        break;
      case ']':;
        long nested = 1;
        while (nested) {
          code_cursor--;
          switch (code[code_cursor]) {
            case '[':
              nested--;
              break;
            case ']':
              nested++;
              break;
          }
        }
        code_cursor--;
        break;
      case 0:
        printf("\n");
        exit(EXIT_SUCCESS);
        break;
      default:
        break;
    }
    code_cursor++;
  }

  free(code);

  return EXIT_SUCCESS;
}
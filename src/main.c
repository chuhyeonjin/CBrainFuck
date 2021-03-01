#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 30000

void PrintError(char* message) {
  fprintf(stderr, "\033[0;31mError:\033[0m %s\n", message);
}

void PrintWarning(char* message) {
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

  *data_pointer = malloc(file_size);
  if (*data_pointer == NULL) {
    PrintError("cannot allocate memory");
    exit(EXIT_FAILURE);
  }

  if (fgets(*data_pointer, file_size, file) == NULL) {
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

  ReadFile(argv[1], &code, &code_size);

  while (1) {
    switch (code[code_cursor]) {
      case 62:
        data_cursor++;
        break;
      case 60:
        data_cursor--;
        break;
      case 43:
        data[data_cursor]++;
        break;
      case 45:
        data[data_cursor]--;
        break;
      case 46:
        putchar(data[data_cursor]);
        break;
      case 44:
        data[data_cursor] = GetAsciiChar();
        break;
      case 91:
        break;
      case 93:
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
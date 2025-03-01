#include "headers.h"

int readfile(FILE *fp, char **text);

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Usage: %s [-a] <assembly_file> <output_file>\n", argv[0]);
    printf("       %s [-d] <object_file> <output_file>\n", argv[0]);

    return 1;
  }

  // mode of operation
  char *mode = argv[1]; 

  if (mode[0] != '-')
  {
    printf("Invalid mode of operation: %s\n", mode);
    return 1;
  } else {

    mode++;

    if (*mode != 'a' && *mode != 'd')
    {
      printf("Invalid mode of operation: %s\n", mode);
      return 1;
    }
  }

  // open file
  FILE *fp;
  char *infile = argv[2];

  if ((fp = fopen(infile, "r")) == NULL)
  {
    printf("Cannot open file: %s\n", infile);
    return 1;
  }

  // read file
  char *text[MAX_BUFFER];
  int linecount = 0;

  if ((linecount = readfile(fp, text)) == -1)
  {
    printf("Error reading file: %s\n", infile);

    fclose(fp);
    return 1;
  }
    
  // debug
  #ifndef NDEBUG
  int i = 0;
  while (i < linecount)
    printf("%s", text[i++]);

  printf("\n");
  #endif

  // open file for output
  FILE *fp2;
  char *outfile = argv[3];
  if ((fp2 = fopen(outfile, "w")) == NULL)
  {
    printf("Cannot open file: %s\n", outfile);

    fclose(fp);
    return 1;
  }

  // assemble or disassemble
  if (*mode == 'a')
    assemble(text, linecount, fp2);
  else
    disassemble(text, linecount, fp2);

  // cleanup
  int l = 0;
  while (l < linecount) {
    free(text[l]);
    l++;
  }
  fclose(fp);
  fclose(fp2);
}

int readfile(FILE *fp, char **text) {
  int lines_allocated = 10;

  // read lines
  char s[MAX_BUFFER]; 
  int i = 0;

  while (fgets(s, sizeof s, fp) != NULL) {
    if (i >= lines_allocated) {
      // double allocated space
      lines_allocated *= 2;
      if ((text = realloc(text, lines_allocated * MAX_BUFFER)) == NULL) {
        return -1;
      }
    }
    text[i] = strdup(s);

    i++;
  }

  return i;
}
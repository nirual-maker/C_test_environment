#include <stdio.h>

int main(void)
{
  FILE* file = fopen("test.txt", "r");
  if (file == NULL)
  {
    return 1;
  }
  int ch;
  while ((ch = fgetc(file)) != EOF)
  {
    printf("%c", ch);
  }
  fclose(file);
  return 0;
}

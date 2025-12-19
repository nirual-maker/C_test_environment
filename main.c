#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_START_SIZE 256
const char* user_commands[11] = { "quit",
                                  "help",
                                  "load",
                                  "crop",
                                  "place",
                                  "undo",
                                  "print",
                                  "switch",
                                  "tree",
                                  "bmps",
                                  "save" };

typedef enum _ReturnValues_
{
  RETURN_QUIT,
  RETURN_BAD_ALLOC,
  RETURN_INVALID_AMMOUNT_PARAMETERS,
  RETURN_INVALID_CANVAS_SIZE,
  RETURN_SUCCESS,
  RETURN_INVALID
} ReturnValues;

typedef enum _ErrorId_
{
  ERROR_BAD_ALLOC,
  ERROR_INVALID_AMOUNT_PARAMETERS,
  ERROR_INVALID_CANVAS_SIZE,
  ERROR_COMMAND_UNKNOWN,
  ERROR_WRONG_NUMBER_ARGUMENTS,
  ERROR_BMP_ID_NOT_FOUND,
  ERROR_CANNOT_OPEN_FILE,
  ERROR_INVALID_FILE,
  ERROR_CROP_COORDS_OUTSIDE_BMP,
  ERROR_CROP_COORDS_INVALID_RECTANGLE,
  ERROR_CANVAS_COORDS_INVALID,
  ERROR_BMP_NOT_FIT_CANVAS,
  ERROR_INVALID_BLEND_MODE,
  ERROR_ALREADY_AT_ROOT_LAYER,
  ERROR_LAYER_ID_NOT_FOUND,
  ERROR_INVALID_FILE_PATH
} ErrorId;

typedef enum _Modes_
{
  MODE_QUIT,
  MODE_HELP,
  MODE_LOAD,
  MODE_CROP,
  MODE_PLACE,
  MODE_UNDO,
  MODE_PRINT,
  MODE_SWITCH,
  MODE_TREE,
  MODE_BMPS,
  MODE_SAVE,
  MODE_DEFAULT
} Modes;

typedef enum _PromptId_
{
  PROMPT_WELCOME_MESSAGE,
  PROMPT_HELP,
} PromptId;

//----------------------------------------------------------------------------------------------------------------------
/// program structure functions
ReturnValues programLoop(int canvas_width, int canvas_height);
ReturnValues getCommandLineArguments(int argc, char* argv[], int* canvas_width, int* canvas_height);
ReturnValues executeModes(Modes mode);
ReturnValues getUserMode(Modes* mode);
ReturnValues modeQuit(void);
ReturnValues modeHelp(void);
ReturnValues modeLoad(void);
ReturnValues modeCrop(void);
ReturnValues modePlace(void);
ReturnValues modeUndo(void);
ReturnValues modePrint(void);
ReturnValues modeSwitch(void);
ReturnValues modeTree(void);
ReturnValues modeBmps(void);
ReturnValues modeSave(void);

//----------------------------------------------------------------------------------------------------------------------
/// helper functions
void validateParameter(int* value, char* paramenter);
char* getUserInputArbitraryLength(void);
char* getNextWordInString(char* string);
char* searchCharInString(char* string, char character);
int countWordsInString(char* string_to_count);

//----------------------------------------------------------------------------------------------------------------------
/// printing functions
void printErrorMessage(ErrorId error_id);
void printWelcomeMessage(int canvas_width, int canvas_height);

int main(int argc, char* argv[])
{
  int canvas_width = 0;
  int canvas_height = 0;
  ReturnValues return_value = getCommandLineArguments(argc, argv, &canvas_width, &canvas_height);
  if (return_value == RETURN_INVALID_AMMOUNT_PARAMETERS || return_value == RETURN_INVALID_CANVAS_SIZE)
    return return_value;
  printWelcomeMessage(canvas_width, canvas_height);
  return programLoop(canvas_width, canvas_height);
}

//----------------------------------------------------------------------------------------------------------------------
/// program structure functions
ReturnValues programLoop(int canvas_width, int canvas_height)
{
  ReturnValues return_value = RETURN_QUIT;
  Modes mode = MODE_DEFAULT;
  while (1)
  {
    printf(" > ");
    return_value = getUserMode(&mode);
    if (return_value == RETURN_BAD_ALLOC)
    {
      printErrorMessage(ERROR_BAD_ALLOC);
      return return_value;
    }
    if (return_value == RETURN_INVALID)
      continue;
    
    return_value = executeModes(mode);
    if (return_value == RETURN_BAD_ALLOC)
    {
      printErrorMessage(ERROR_BAD_ALLOC);
      return RETURN_BAD_ALLOC;
    }
    if (return_value == RETURN_QUIT)
      return RETURN_QUIT;
  }
}

ReturnValues getCommandLineArguments(int argc, char* argv[], int* canvas_width, int* canvas_height)
{
  if (argc != 3)
  {
    printErrorMessage(ERROR_INVALID_AMOUNT_PARAMETERS);
    return RETURN_INVALID_AMMOUNT_PARAMETERS;
  }
  validateParameter(canvas_width, argv[1]);
  validateParameter(canvas_height, argv[2]);
  if (*canvas_width <= 0 || *canvas_height <= 0 || *canvas_width == -1 || *canvas_height == -1)
  {
    printErrorMessage(ERROR_INVALID_CANVAS_SIZE);
    return RETURN_INVALID_CANVAS_SIZE;
  }
  return RETURN_SUCCESS;
}

ReturnValues getUserMode(Modes* mode)
{
  int argument_count = 0;
  char* command = NULL;

  char* user_input = getUserInputArbitraryLength();
  if (user_input == NULL)
    return RETURN_BAD_ALLOC;
  argument_count = countWordsInString(user_input);
  command = getNextWordInString(user_input);


  for (size_t i = 0; i < sizeof(user_commands) / sizeof(user_commands[0]); i++)
  {
    if (strncmp(command, user_commands[i], strlen(user_commands[i])) == 0)
    {
      *mode = i;
      switch (argument_count)
      {
        case 1: // quit help undo print tree bmps
          free(user_input);
          return RETURN_SUCCESS;
        case 2: // load switch save
          break;
        case 5: // place
          break;
        case 6: // crop
          break;
        default:
          break;
      }
    }
  }
  free(user_input);
  printErrorMessage(ERROR_COMMAND_UNKNOWN);
  return RETURN_INVALID;
}

ReturnValues executeModes(Modes mode)
{
  switch (mode)
  {
    case MODE_QUIT:
      return modeQuit();
    case MODE_HELP:
      return modeHelp();
    case MODE_LOAD:
      return modeLoad();
    case MODE_CROP:
      return modeCrop();
    case MODE_PLACE:
      return modePlace();
    case MODE_UNDO:
      return modeUndo();
    case MODE_PRINT:
      return modePrint();
    case MODE_SWITCH:
      return modeSwitch();
    case MODE_TREE:
      return modeTree();
    case MODE_BMPS:
      return modeBmps();
    case MODE_SAVE:
      return modeSave();
    default:
      return RETURN_INVALID;
  }
}

ReturnValues modeQuit(void)
{
  return RETURN_QUIT;
}

ReturnValues modeHelp(void)
{
  printf("\n");
  printf("Available commands:\n");
  printf(" help\n");
  printf(" load <PATH>\n");
  printf(" crop <BMP_ID> <TOP_X> <TOP_Y> <BOTTOM_X> <BOTTOM_Y>\n");
  printf(" place <BMP_ID> <CANVAS_X> <CANVAS_Y> <BLEND_MODE>\n");
  printf(" undo\n");
  printf(" print\n");
  printf(" switch <LAYER_ID>\n");
  printf(" tree\n");
  printf(" bmps\n");
  printf(" save <FILE_PATH>\n");
  printf(" quit\n");
  printf("\n");
  return RETURN_SUCCESS;
}

ReturnValues modeLoad(void)
{
  printf("Mode load selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeCrop(void)
{
  printf("Mode crop selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modePlace(void)
{
  printf("Mode place selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeUndo(void)
{
  printf("Mode undo selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modePrint(void)
{
  printf("Mode print selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeSwitch(void)
{
  printf("Mode switch selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeTree(void)
{
  printf("Mode tree selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeBmps(void)
{
  printf("Mode bmps selected!\n");
  return RETURN_SUCCESS;
}

ReturnValues modeSave(void)
{
  printf("Mode save selected!\n");
  return RETURN_SUCCESS;
}

//----------------------------------------------------------------------------------------------------------------------
/// helper functions
void validateParameter(int* value, char* paramenter)
{
  size_t char_counter = 0;
  while (1)
  {
    if (paramenter[char_counter] == '\0')
    {
      *value = atoi(paramenter);
      return;
    }
    if (paramenter[char_counter] >= '0' && paramenter[char_counter] <= '9')
    {
      char_counter++;
      continue;
    }
    *value = -1;
    return;
  }
}

char* getUserInputArbitraryLength(void)
{
  int buffer_start_size = BUFFER_START_SIZE;
  int buffer_actual_size = 0;
  char*  user_input = NULL;
  char* temp_prt = NULL;
  char* newline_char = NULL;
  int counter = 0;
  int input_shift = 0;
  while(1)
  {
    if (buffer_actual_size == buffer_start_size)
      input_shift = 1; 
    buffer_actual_size += buffer_start_size;
    temp_prt = realloc(user_input, buffer_actual_size * sizeof(char));
    if (temp_prt == NULL)
    {
      if (user_input != NULL)
        free(user_input);
      return NULL;
    }
    user_input = temp_prt;
    temp_prt = NULL;
    counter = buffer_actual_size - buffer_start_size - input_shift;
    fgets(user_input + counter, buffer_start_size + input_shift, stdin);
    newline_char = searchCharInString(user_input + counter, '\n');
    if (newline_char != NULL)
    {
      *newline_char = '\0';
      temp_prt = realloc(user_input, (int)strlen(user_input) + 1);
      if (temp_prt == NULL)
      {
        free(user_input);
        return NULL;
      }
      user_input = temp_prt;
      temp_prt = NULL;
      return user_input;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
/// @brief Counts the number of individual words in a string.
/// @param string_to_count String to count number of words in.
/// @return Number of words found in string_to_count.
int countWordsInString(char* string_to_count)
{
  int word_counter = 0;
  int char_counter = 0;
  while(1)
  {
    if (string_to_count[char_counter] == '\0')
      return word_counter;
    if (string_to_count[char_counter] != ' ')
    {
      word_counter++;
      while(1)
      {
        if (string_to_count[char_counter] == '\0')
          return word_counter;
        if (string_to_count[char_counter] == ' ')
          break;
        char_counter++;
      }
    }
    char_counter++;
  }
}



//----------------------------------------------------------------------------------------------------------------------
/// @brief Serches a given character in a string.
/// @param string String to search in.
/// @param character Character to search for.
/// @return Pointer to found character. If not found, pointer is NULL.
char* searchCharInString(char* string, char character)
{
  for (char* iterator = string; *iterator != '\0'; iterator++)
  {
    if (*iterator == character)
      return iterator;
  }
  return NULL;
}

char* getNextWordInString(char* string)
{
  size_t char_counter = 0;
  while (1)
  {
    if (string[char_counter] != ' ')
      return &string[char_counter];
    char_counter++;
  }
}

//----------------------------------------------------------------------------------------------------------------------
/// printing functions
//----------------------------------------------------------------------------------------------------------------------
/// @brief prints the error message acorting to the error id
/// @param error_id ErrorId to specify the error
void printErrorMessage(ErrorId error_id)
{
  switch (error_id)
  {
    case ERROR_BAD_ALLOC:
      printf("[ERROR] Memory allocation failed!\n");
      break;
    case ERROR_INVALID_AMOUNT_PARAMETERS:
      printf("[ERROR] Invalid amount of command line parameters!\n");
      break;
    case ERROR_INVALID_CANVAS_SIZE:
      printf("[ERROR] Invalid canvas size specified!\n");
      break;
    case ERROR_COMMAND_UNKNOWN:
      printf("[ERROR] Command unknown!\n");
      break;
    case ERROR_WRONG_NUMBER_ARGUMENTS:
      printf("[ERROR] Wrong number of arguments!\n");
      break;
    case ERROR_BMP_ID_NOT_FOUND:
      printf("[ERROR] BMP ID not found!\n");
      break;
    case ERROR_CANNOT_OPEN_FILE:
      printf("[ERROR] Cannot open file!\n");
      break;
    case ERROR_INVALID_FILE:
      printf("[ERROR] Invalid file!\n");
      break;
    case ERROR_CROP_COORDS_OUTSIDE_BMP:
      printf("[ERROR] Crop coordinates are outside the BMP!\n");
      break;
    case ERROR_CROP_COORDS_INVALID_RECTANGLE:
      printf("[ERROR] Crop coordinates do not form a valid rectangle!\n	");
      break;
    case ERROR_CANVAS_COORDS_INVALID:
      printf("[ERROR] Canvas coordinates are invalid!\n");
      break;
    case ERROR_BMP_NOT_FIT_CANVAS:
      printf("[ERROR] BMP does not fit on the canvas!\n");
      break;
    case ERROR_INVALID_BLEND_MODE:
      printf("[ERROR] Invalid blend mode!\n");
      break;
    case ERROR_ALREADY_AT_ROOT_LAYER:
      printf("[ERROR] Already at root layer!\n");
      break;
    case ERROR_LAYER_ID_NOT_FOUND:
      printf("[ERROR] Layer ID not found!\n");
      break;
    case ERROR_INVALID_FILE_PATH:
      printf("[ERROR] Invalid file path!\n");
      break;
    default:
      break;
  }
}

void printWelcomeMessage(int canvas_width, int canvas_height)
{
  printf("\n");
  printf("Welcome to Image Structuring Program!\n");
  printf("The canvas is %d x %d pixels.\n", canvas_width, canvas_height);
  printf("\n");
}


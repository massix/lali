#include "config.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main()
{
  todo::config l_config("../config_file.example.todo");
  assert(l_config.parse_config() == true);

  assert(l_config[FILE_CONFIG_FILE] == "test_file");
  assert(l_config[FILE_NOTES_DB] == "/Users/myuser/notes.bin");

  assert(l_config[NOTE_ID_FORMAT] == "0x%04X");
  assert(l_config[NOTE_COUNT_COLOR] == "red");
  assert(l_config[NOTE_ID_COLOR] == "gray");
  assert(l_config[NOTE_TITLE_COLOR] == "cyan");
  assert(l_config[NOTE_BODY_COLOR] == "green");
  assert(l_config[NOTE_SEARCH_COLOR] == "red");

  assert(l_config[PRIORITY_LOW_COLOR] == "black");
  assert(l_config[PRIORITY_DEFAULT_COLOR] == "white");
  assert(l_config[PRIORITY_HIGH_COLOR] == "blue");

  assert(l_config[PRIORITY_LOW_TEXT] == "doesn't matter");
  assert(l_config[PRIORITY_DEFAULT_TEXT] == "look at it");
  assert(l_config[PRIORITY_HIGH_TEXT] == "do it now!");

  assert(l_config[LIST_FORMAT] == "[@ID@] @TITLE@ @IF_BODY@: @BODY@ :@END_IF_BODY@ @PRIORITY_TEXT@");

  assert(l_config.isAskForConfirmation() == true);
  assert(l_config.isMonochrome() == true);

  return 0;
}


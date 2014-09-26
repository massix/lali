#include "config.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main()
{
  todo::config l_config("config_file.example.todo");
  assert(l_config.parse_config() == true);

  assert(l_config[FILE_CONFIG_FILE] == "test_file");
  assert(l_config[FILE_NOTES_DB] == "/Users/myuser/notes.bin");

  assert(l_config[NOTE_COUNT_COLOR] == "red");
  assert(l_config[NOTE_ID_COLOR] == "gray");
  assert(l_config[NOTE_TITLE_COLOR] == "cyan");
  assert(l_config[NOTE_BODY_COLOR] == "green");

  assert(l_config[PRIORITY_LOW_COLOR] == "black");
  assert(l_config[PRIORITY_DEFAULT_COLOR] == "white");
  assert(l_config[PRIORITY_HIGH_COLOR] == "blue");

	return 0;
}


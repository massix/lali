#include "collection.h"
#include "element.h"
#include "application.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#define CONFIG_FILE ".todorc"

int main(int argc, char *argv[])
{
  todo::application l_app(argc, argv);
  return l_app.run();
}


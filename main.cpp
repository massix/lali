#include "collection.h"
#include "element.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE ".todorc"

void usage(const char *p_pgmname)
{
  fprintf(stdout, "%s <command> <parameters>\n", p_pgmname);
  fprintf(stdout, "   count              | counts the todos\n");
  fprintf(stdout, "   insert title body  | inserts a todo\n");
  fprintf(stdout, "   delete index       | removes a todo\n");
  fprintf(stdout, "   list               | lists all the todos\n");
}

int main(int argc, char *argv[])
{
  char * l_homefolder = getenv("HOME");
  std::string l_path = std::string(l_homefolder) + "/" + std::string(CONFIG_FILE);
  std::ifstream l_config;
  std::string l_binfile;

  l_config.open(l_path.c_str(), std::ifstream::in | std::ifstream::binary);
  l_config >> l_binfile;
  l_config.close();

  todo::collection l_collection(l_binfile);
  l_collection.read_file();

  const char * l_pgname = argv[0];

  if (argc == 1)
  {
    usage(l_pgname);
    return 0;
  }

  int32_t l_arg(0);
  while (l_arg < argc)
  {
    if (strcmp(argv[l_arg], "count") == 0)
    {
      fprintf(stdout, "You have %lu todos\n", l_collection.size());
    }
    else if (strcmp(argv[l_arg], "help") == 0)
    {
      usage(l_pgname);
      return 0;
    }
    else if (strcmp(argv[l_arg], "insert") == 0)
    {
      std::string l_title;
      std::string l_body;

      if (++l_arg < argc)
        l_title = std::string(argv[l_arg]);

      if (++l_arg < argc)
        l_body = std::string(argv[l_arg]);

      if (l_title.empty() and l_body.empty())
      {
        usage(l_pgname);
        return 127;
      }

      todo::element l_element(l_title, l_body);
      l_collection.push_back(l_element);
    }
    else if (strcmp(argv[l_arg], "list") == 0)
    {
      todo::collection::const_iterator l_iterator = l_collection.begin();
      for (uint32_t l_idx = 0; l_iterator != l_collection.end(); ++l_iterator, l_idx++) {
          fprintf(stdout, "[%d] %s", l_idx, l_iterator->m_title.c_str());
        if (not l_iterator->m_body.empty())
          fprintf(stdout, " => %s", l_iterator->m_body.c_str());
        fprintf(stdout, "\n");
      }
    }
    else if (strcmp(argv[l_arg], "delete") == 0)
    {
      if (++l_arg < argc)
      {
        uint32_t l_toErase = atoi(argv[l_arg]);
        if (l_collection.begin() + l_toErase < l_collection.end())
          l_collection.erase(l_collection.begin() + l_toErase);
        else {
          fprintf(stderr, "Index out of bounds..\n");
        }
      }
      else {
        usage(l_pgname);
        return 127;
      }
    }

    l_arg++;
  }

  l_collection.write_file();
	return 0;
}


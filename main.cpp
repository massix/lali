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

std::map<std::string, std::string> g_colors;
std::string printColor(std::string const & l_color, std::string const & l_string, bool bright = true, bool underline = false);
std::string printColor(std::string const & l_color, int l_number, bool bright = true, bool underline = false);

std::string printColor(std::string const & l_color, std::string const & l_string, bool bright, bool underline)
{
  std::string ret;
  if (underline) ret += g_colors["underscore"];
  if (bright) ret += g_colors["bright"];
  ret += g_colors[l_color];
  ret += l_string;
  ret += g_colors["reset"];

  return ret;
}

std::string printColor(std::string const & l_color, int l_number, bool bright, bool underline)
{
  char l_buffer[1024] = { 0 };
  sprintf(l_buffer, "%d", l_number);
  std::string ret;
  if (underline) ret += g_colors["underscore"];
  if (bright) ret += g_colors["bright"];
  ret += g_colors[l_color];
  ret += std::string(l_buffer);
  ret += g_colors["reset"];

  return ret;
}

void usage(const char *p_pgmname)
{
  fprintf(stdout, "%s <command> <parameters>\n", p_pgmname);
  fprintf(stdout, "   count              | counts the todos\n");
  fprintf(stdout, "   insert title body  | inserts a todo\n");
  fprintf(stdout, "   delete index       | removes a todo\n");
  fprintf(stdout, "   list               | lists all the todos\n");
  fprintf(stdout, "   modify index t b   | modify the todo at given index\n");
}

int main(int argc, char *argv[])
{
  todo::application l_app(argc, argv);
  return l_app.run();

/*  char * l_homefolder = getenv("HOME");*/
  //std::string l_path = std::string(l_homefolder) + "/" + std::string(CONFIG_FILE);
  //std::ifstream l_config;
  //std::string l_binfile;

  //g_colors["reset"]       = "\x1b[0m";
	//g_colors["bright"]      = "\x1b[1m";
	//g_colors["dim"]         = "\x1b[2m";
	//g_colors["underscore"]  = "\x1b[4m";
	//g_colors["blink"]       = "\x1b[5m";
	//g_colors["reverse"]     = "\x1b[7m";
	//g_colors["hidden"]      = "\x1b[8m";
	//g_colors["fgblack"]     = "\x1b[30m";
	//g_colors["fgred"]       = "\x1b[31m";
	//g_colors["fggreen"]     = "\x1b[32m";
	//g_colors["fgyellow"]    = "\x1b[33m";
	//g_colors["fgblue"]      = "\x1b[34m";
	//g_colors["fgmagenta"]   = "\x1b[35m";
	//g_colors["fgcyan"]      = "\x1b[36m";
	//g_colors["fgwhite"]     = "\x1b[37m";
	//g_colors["bgblack"]     = "\x1b[40m";
	//g_colors["bgred"]       = "\x1b[41m";
	//g_colors["bggreen"]     = "\x1b[42m";
	//g_colors["bgyellow"]    = "\x1b[43m";
	//g_colors["bgblue"]      = "\x1b[44m";
	//g_colors["bgmagenta"]   = "\x1b[45m";
	//g_colors["bgcyan"]      = "\x1b[46m";
	//g_colors["bgwhite"]     = "\x1b[47m";

  //l_config.open(l_path.c_str(), std::ifstream::in | std::ifstream::binary);
  //l_config >> l_binfile;
  //l_config.close();

  //todo::collection l_collection(l_binfile);
  //l_collection.read_file();

  //const char * l_pgname = argv[0];

  //if (argc == 1)
  //{
    //usage(l_pgname);
    //return 0;
  //}

  //int32_t l_arg(0);
  //while (l_arg < argc)
  //{
    //if (strcmp(argv[l_arg], "count") == 0)
    //{
      //fprintf(stdout, "You have %s todos\n", printColor("fgcyan", l_collection.size()).c_str());
    //}
    //else if (strcmp(argv[l_arg], "help") == 0)
    //{
      //usage(l_pgname);
      //return 0;
    //}
    //else if (strcmp(argv[l_arg], "insert") == 0)
    //{
      //std::string l_title;
      //std::string l_body;
      //uint32_t l_priority;
      
      //if (++l_arg < argc)
        //l_priority = atoi(argv[l_arg]);

      //if (++l_arg < argc)
        //l_title = std::string(argv[l_arg]);

      //if (++l_arg < argc)
        //l_body = std::string(argv[l_arg]);

      //if (l_title.empty() and l_body.empty())
      //{
        //usage(l_pgname);
        //return 127;
      //}

      //todo::element l_element(l_title, l_body);
      //l_collection.push_back(l_element);
    //}
    //else if (strcmp(argv[l_arg], "list") == 0)
    //{
      //todo::collection::const_iterator l_iterator = l_collection.begin();
      //for (uint32_t l_idx = 0; l_iterator != l_collection.end(); ++l_iterator, l_idx++) {
          //fprintf(stdout, "[%s] %s", 
              //printColor("fgcyan", l_idx).c_str(), 
              //printColor("fgblue", l_iterator->m_title).c_str());
        //if (not l_iterator->m_body.empty())
          //fprintf(stdout, " : %s", 
              //printColor("fgyellow", l_iterator->m_body).c_str());
        //fprintf(stdout, "\n");
      //}
    //}
    //else if (strcmp(argv[l_arg], "delete") == 0)
    //{
      //if (++l_arg < argc)
      //{
        //uint32_t l_toErase = atoi(argv[l_arg]);
        //if (l_collection.begin() + l_toErase < l_collection.end())
          //l_collection.erase(l_collection.begin() + l_toErase);
        //else {
          //fprintf(stderr, "%s\n", printColor("fgred", "Index out of bounds !!", true, true).c_str());
        //}
      //}
      //else {
        //usage(l_pgname);
        //return 127;
      //}
    //}
    //else if (strcmp(argv[l_arg], "modify") == 0)
    //{
      //if (++l_arg < argc)
      //{
        //uint32_t l_toModify = atoi(argv[l_arg]);
        //if (++l_arg < argc) {
          //std::string l_newTitle(argv[l_arg]);
          //std::string l_newBody;
          //if (++l_arg < argc) {
            //l_newBody = std::string(argv[l_arg]);
          //}
          
          //if (l_collection.begin() + l_toModify < l_collection.end()) {
            //todo::element & l_element = l_collection[l_toModify];
            //l_element.m_title = l_newTitle;
            //l_element.m_body = l_newBody;
          //}
        //}
        //else {
          //usage(l_pgname);
          //return 127;
        //}
      //}
      //else {
        //usage(l_pgname);
        //return 127;
      //}
    //}

    //l_arg++;
  //}

  //l_collection.write_file();
	/*return 0;*/
}


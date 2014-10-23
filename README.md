LALI: LIST A LIST
--------------------------

LALI (<b>L</b>ist **A** <b>LI</b>st) is my personal todo-list manager. I wrote this because:
 * I was bored;
 * I wasn't able to find a CLI todo-list program that was
   fitting my needs;
 * I wanted to write some code.

It is _almost_ fully configurable thanks to a configuration file which has to
be located in ```${HOME}/.lalirc```. The parser of the configuration file is
stupid, so you *have to* strictly follow the rules or you will get strange
behaviours, segmentation faults, issues everywhere.

The CLI interface isn't that smart at all, but at least is easily wrappable in
shell scripts in order to have different lists for your different needs.

This is what the help looks like:

```
     -[ LALI version 0.4.0dev ]-
Usage: ./src/lali <action> [parameters]
  List of available actions
         list   | l                  list all notes in the db
       insert   | i <parameters>     insert a new note
       modify   | m <parameters>     modify a given note
       delete   | d <parameters>     delete a given note
       search   | s <parameters>     search for given text in notes
       export   | e <parameters>     exports the current db in a different format

 List of available parameters
     --format   | -f <format>        format to use (see documentation)
       --note   | -n id              specify the note id
      --title   | -t text            the text that follows is the title
       --body   | -b text            the text that follows is the body
 --monochrome   | -m                 print a monochrome version
   --priority   | -p id              priority of the new note
     --todorc   | -r file            use this todorc file
     --tododb   | -d file            use this db of notes
    --version   | -v                 print version and exit
    --confirm   | -c                 ask for confirmation before deleting 
    --dry-run   |                    do not modify the db

 List of available exporters
         txt    |                    text file exporter

 List of parameters for exporting
     --output   | -o file            outputs to given file name
```


And this is an example (you can find it in the source repo) of the configuration
file with all the options you can customize:
```
# This is a comment
file_notes_db = /Users/myuser/notes.bin

# Some defaults
always_ask_for_confirmation = true
monochrome = yes

# Note colors
note_id_color = gray
note_title_color = cyan
note_body_color = green
note_search_color = red

# Note format is a valid printf format!
note_id_format = 0x%04X

# Format to be used when using action 'list'
list_format = [@ID@] @TITLE@ @IF_BODY@: @BODY@ :@END_IF_BODY@ @PRIORITY_TEXT@

# Priority colors
priority_low_color = black
priority_default_color = white
priority_high_color = blue

# Priority texts
priority_low_text = doesn't matter
priority_default_text = look at it
priority_high_text = do it now!

# This is another comment
```

The notes are stored in a binary file, you can export them in a more readable
format either by using the '-m' and '-f' options in order to get a parseable
output for tools like *sed* or *awk*, or use the txt exporter. The second
solution will probably need some tuning of the code in order to get a format
that you are comfortable with.

The code isn't pretty at all, it needs a lot of refactoring.
The build system isn't pretty at all, I might want to migrate to cmake one day.


The code is released using the WTFPL license.
```
DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE Version 2, December 2004

Copyright (C) 2004 Sam Hocevar

Everyone is permitted to copy and distribute verbatim or modified copies of this license document, and changing it is allowed as long as the name is changed.

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. You just DO WHAT THE FUCK YOU WANT TO.
```

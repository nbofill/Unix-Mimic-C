/* I pledge on my honor that I have not given or received any unauthorized
   assistance on this assignment/examination.*/

/* Nicolas Bofill : nbofill : 117243086 : Section 0108 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ournix.h"

void print_list(Directory *dir);
void recursive_pwd(Directory *dir);
void rmfs_help(Directory *dir);

/*mkfs initializes an Ournix type and changes it's current directory to the
  root directory*/
void mkfs(Ournix *const filesystem) {
  if (filesystem == NULL) {
    ;
  } else {
    
    filesystem->root = malloc(sizeof(Directory));

    filesystem->root->name = malloc(sizeof(char) + 1);
    /*the parameter "type" is set to 1 for directories and 0 for files*/
    filesystem->root->type = 1;
    filesystem->root->timestamp = 0;
    filesystem->root->sub_dir = NULL;
    filesystem->root->next = NULL;
    filesystem->root->prev_dir = NULL;

    strcpy(filesystem->root->name, "/");
    
    filesystem->curr_dir = filesystem->root;
  }
}

/*touch adds a file with the specified name into the current directory of the 
  Ournix parameter. If the file name is already used for a file, the timestamp
  of that file is updated. If the parameter name is already used for a
  directory, nothing occurs. The "type" field of a file is always set to 0 to 
  represent that it is a type file*/
int touch(Ournix *const filesystem, const char name[]) {
  
  Directory *curr, *new_file, *prev;
  
  /*check no change cases*/
  if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 
      || strcmp(name, "/") == 0) {
    
    return 1;
  }
  
  /*check error cases*/
  if (strcmp(name, "") == 0 || strstr(name, "/") != NULL || filesystem == NULL 
      || name == NULL) {
    
    return 0;
  }
  
  curr = filesystem->curr_dir->sub_dir;
  prev = curr;
  
  while (curr != NULL) {
    
    /*when file of same name exists, update timestamp*/
    if ((strcmp(name, curr->name) == 0) && curr->type == 0) {
      curr->timestamp += 1;
      return 1;
      
      /*when directory of same name exists, nothing changes*/
    } else if ((strcmp(name, curr->name) == 0) && curr->type == 1) {
      return 1;
      
      /*when a new file is added before the end of the list*/
    } else if (strcmp(name, curr->name) < 0) {
    
      new_file = malloc(sizeof(Directory));
      new_file->name = malloc(strlen(name) + 1);
      
      strcpy(new_file->name, name);
      new_file->type = 0;
      new_file->timestamp = 1;
      new_file->sub_dir = NULL;
      new_file->prev_dir = filesystem->curr_dir;
      new_file->next = curr;
      
      /*when the new file becomes the head*/
      if (curr == filesystem->curr_dir->sub_dir) {
	filesystem->curr_dir->sub_dir = new_file;
	
      } else { 
	prev->next = new_file;
      }
      
      return 1;
      
      /*when new file is added to the end of the list*/
    } else if (curr->next == NULL) {
      new_file = malloc(sizeof(Directory));
      new_file->name = malloc(strlen(name) + 1);
      
      strcpy(new_file->name, name); 
      new_file->type = 0;
      new_file->timestamp = 1;
      new_file->sub_dir = NULL;
      new_file->next = NULL;
      new_file->prev_dir = filesystem->curr_dir;
      
      curr->next = new_file;
      return 1;
    }
    
    prev = curr;
    curr = curr->next;
  }
  
  /*case for when there is no head*/
  
  new_file = malloc(sizeof(Directory));
  new_file->name = malloc(strlen(name) + 1);

  strcpy(new_file->name, name); 
  new_file->type = 0;
  new_file->timestamp = 1;
  new_file->sub_dir = NULL;
  new_file->next = NULL;
  new_file->prev_dir = filesystem->curr_dir;
  
  filesystem->curr_dir->sub_dir = new_file;
  return 1;
}

/*mkdir makes a new directory in the current directory of the Ournix parameter
  with the specified name. If a file or directory already uses the name, 
  nothing changes. The field "type" of a directory is always set to one to
  show that it is a directory and not a file*/
int mkdir(Ournix *const filesystem, const char name[]) {

  Directory *curr, *new_dir, *prev;

  /*check error cases*/
  if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 
      || strcmp(name, "/") == 0 || strcmp(name, "") == 0 || filesystem == NULL
      || name == NULL || strstr(name, "/") != NULL) {
    
    return 0;
  }
  
  curr = filesystem->curr_dir->sub_dir;
  prev = curr;
  
  while (curr != NULL) {
    /*if a file or directory with same name exists, nothing changes*/
    if (strcmp(curr->name, name) == 0) {
      return 1;

      /*when directory is added before end of list*/
    } else if (strcmp(name, curr->name) < 0) {

      new_dir = malloc(sizeof(Directory));
      new_dir->name = malloc(strlen(name) + 1);
      
      strcpy(new_dir->name, name); 
      new_dir->type = 1;
      new_dir->sub_dir = NULL;
      new_dir->next = curr;
      new_dir->prev_dir = filesystem->curr_dir;
      
      /*when new directory becomes the head*/
      if (curr == filesystem->curr_dir->sub_dir) {
	filesystem->curr_dir->sub_dir = new_dir;
	
      } else { 
	prev->next = new_dir;
      }
	
      return 1;
    
      /*when new directory is added to end of list*/
    } else if (curr->next == NULL) {
      new_dir = malloc(sizeof(Directory));
      new_dir->name = malloc(strlen(name) + 1);
      
      strcpy(new_dir->name, name);
      new_dir->type = 1;
      new_dir->next = NULL;
      new_dir->prev_dir = filesystem->curr_dir; 
      new_dir->sub_dir = NULL;
      
      curr->next = new_dir;
      return 1;
    }
    prev = curr;
    curr = curr->next;
  }
  
  new_dir = malloc(sizeof(Directory));
  new_dir->name = malloc(strlen(name) + 1);
  
  strcpy(new_dir->name, name);
  new_dir->type = 1;
  new_dir->next = NULL;
  new_dir->prev_dir = filesystem->curr_dir;
  new_dir->sub_dir = NULL;

  filesystem->curr_dir->sub_dir = new_dir;

  return 1;
}

/*cd changes the currect directory to that of the specified name as long as
  the desired directory exists within the subdirectory of the current
  directory. If name is "." the current directory does not change. If name
  is ".." the current directory changes to the parent directory of the current
  directory. If name is "/" the current directory changes to the root 
  directory*/
int cd(Ournix *const filesystem, const char name[]) {
  
  Directory *curr;
  
  /*check error cases*/
  if (filesystem == NULL || name == NULL) {
    return 0;
  }

  /*If name is "." the current directory remains the same*/
  if (strcmp(name, ".") == 0) {
    return 1;
  }

  /*If name is ".." the parent directory becomes the current directory*/
  if (strcmp(name, "..") == 0) {
    filesystem->curr_dir = filesystem->curr_dir->prev_dir;
    return 1;
  }

  /*If name is "/" the root becomes the current directory*/
  if (strcmp(name, "/") == 0) {
    filesystem->curr_dir = filesystem->root;
    return 1;
  }

  curr = filesystem->curr_dir->sub_dir;

  while (curr != NULL) {
    
    /*when the directory name exists*/
    if (strcmp(curr->name, name) == 0 && curr->type == 1) {
      filesystem->curr_dir = curr;
      return 1;
      
      /*when the name parameter refers to a file name*/
    } else if (strcmp(curr->name, name) == 0 && curr->type == 0) {
      return 0;
    }
  
    curr = curr->next;
  }
  /*when the name parameter is not a directory name*/
  return 0;
}

/*ls prints out files, directories, or both depending on the name parameter. 
  If name is corresponds to a current file, the file's name and timestamp is 
  printed. If name is refers to a subdirectory in the current directory, all
  the files and subdirectories in that subdirectory are printed. Certain
  characeters in the name parameter will also have different outcomes.*/
int ls(Ournix *const filesystem, const char name[]) {
  
  Directory *curr;
  
  if (filesystem == NULL || name == NULL) {
    return 0;
  }
  
  curr = filesystem->curr_dir->sub_dir;
  
  /*If name is "." print the files and subdirectories of the current dir*/
  if (strcmp(name, ".") == 0 || strcmp(name, "") == 0) {
    print_list(curr);
    return 1;
  }
  
  /*If name is ".." print the files and subdirectories of the current dir's
    parent directory*/
  if (strcmp(name, "..") == 0) {
    print_list(filesystem->curr_dir->prev_dir->sub_dir);
    return 1;
  }
  
  /*If name is "/" print the files and subdirectories of the root directory*/
  if (strcmp(name, "/") == 0) {
    print_list(filesystem->root->sub_dir);
    return 1;
  }
  
  while (curr != NULL) {
    
    /*if the name parameter is that of a file name in the current directory,
      print the file name and its timestamp*/
    if (strcmp(curr->name, name) == 0 && curr->type == 0) {
      printf("%s %d\n", curr->name, curr->timestamp); 
      return 1;
      
      /*If the name parameter is the same as a subdirectory in the current
	directory, print the files and directories of that subdirectory*/
    } else if (strcmp(curr->name, name) == 0 && curr->type == 1) {
      print_list(curr->sub_dir);
      return 1;
    }
    curr = curr->next;
  }

  /*if the name parameter does not correspond to an existing file or directory
    in the current directory*/
  return 0;
}

/*print_list is a helper method that prints the files and directory names 
  of the inputed Directory*/
void print_list(Directory *dir) {
  while (dir != NULL) {
    if (dir->type == 1) {
      printf("%s/\n", dir->name);
      
    } else {
      printf("%s\n", dir->name);
    }
    dir = dir->next;
  }
}

/*pwd prints the path of the file starting from the root directory*/
void pwd(Ournix *const filesystem) {
  if (filesystem == NULL) {
    ;
    /*when the current directory is the root directory, only print the name
      of the root directory*/
  } else if (filesystem->curr_dir == filesystem->root) {
    printf("/\n");
 
    /*when the current directory is not the root directory*/
  } else {
    recursive_pwd(filesystem->curr_dir);
    printf("\n");
  }
}

/*recursive_pwd is a helper method that iterates through the parent directories
  until it reaches the root directory, then it prints out the names of the
  directories as the method unwinds*/
void recursive_pwd(Directory *dir) {
  if (dir->prev_dir == NULL) {
    return;

  } else {
    recursive_pwd(dir->prev_dir);
  }

  printf("/");
  printf("%s", dir->name);
}

/*rmfs deallocates all of the dynamically-allocated memory used by the 
  Ounirx parameter*/
void rmfs(Ournix *const filesystem) {
  if (filesystem == NULL) {
    ;
  } else {
    rmfs_help(filesystem->root);
    filesystem->curr_dir = NULL;
  }  
  
}

/*rmfs_help is a helper method that iterates through all of the directories and
  files and deallocates them and their dynamically allocated parameters*/
void rmfs_help(Directory *dir) {
  if (dir == NULL) {
    return;
  
  } else {
    rmfs_help(dir->sub_dir);
    rmfs_help(dir->next);
  }

  free(dir->name);
  free(dir);
}

/*rm deletes both files and directories from the current directory. If a
  directory is deleted, all of the directories files and subdirectories are
  also deleted*/
int rm(Ournix *const filesystem, const char name[]) {
  
  Directory *curr;
  Directory *prev;
  
  /*check error cases*/
  if (filesystem == NULL || name == NULL || strcmp(name, ".") == 0 
      || strcmp(name, "..") == 0 || strcmp(name, "/") == 0 
      || strcmp(name, "/") == 0 || strstr(name, "/") != NULL) {
    
    return 0;
    
  } 
  
  curr = filesystem->curr_dir->sub_dir;
  prev = NULL;
  
  while (curr != NULL) {
    
    /*if name corresponds to a file name*/
    if (strcmp(name, curr->name) == 0 && curr->type == 0) {
      
      /*when the deleted file is the current head*/
      if (prev == NULL) {
	filesystem->curr_dir->sub_dir = curr->next;
	
	/*if the deleted file is the at the end of the list*/
      } else if (curr->next == NULL) {
	prev->next = NULL;
	
	/*if the deleted file is before end of the list and not the head*/
      } else {
	prev->next = curr->next;
      }
      
      free(curr->name);
      free(curr);
      
      return 1;
      
      /*when name refers to an existing directory*/
    } else if (strcmp(name, curr->name) == 0 && curr->type == 1) {
      
      /*when the delted directory is the head*/
      if (prev == NULL) {
	filesystem->curr_dir->sub_dir = curr->next;
	
	/*when the deleted directory is at the end of the list*/
      } else if (curr->next == NULL) {
	prev->next = NULL;

	/*when the deleted directory is before the end of the list*/
      } else {
	prev->next = curr->next;
	
      }
      
      rmfs_help(curr->sub_dir);
      free(curr->name);
      free(curr);
      
      return 1;
      
    } 
    
    prev = curr;
    curr = curr->next;
    
  }
  /*if the name did not correspond to a file or directory in the current
    directory*/
  return 0;
}

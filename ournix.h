#include "ournix-datastructure.h"

void mkfs(Ournix *const filesystem);
int touch(Ournix *const filesystem, const char name[]);
int mkdir(Ournix *const filesystem, const char name[]);
int cd(Ournix *const filesystem, const char name[]);
int ls(Ournix *const filesystem, const char name[]);
void pwd(Ournix *const filesystem);
void rmfs(Ournix *const filesystem);
int rm(Ournix *const filesystem, const char name[]);

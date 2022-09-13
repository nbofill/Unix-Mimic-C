
typedef struct Directory {
  char *name;
  int type;
  int timestamp;
  struct Directory *sub_dir;
  struct Directory *next;
  struct Directory *prev_dir;
} Directory;
  

typedef struct {
  struct Directory *root;
  struct Directory *curr_dir;
} Ournix;


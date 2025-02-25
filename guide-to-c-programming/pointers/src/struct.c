#include <stdio.h>
#include <string.h>

struct tag
{
  char lname[20]; /* last name */
  char fname[20]; /* first name */
  int age;        /* age */
  float rate;     /* e.g. 12.75 per hour */
};

struct tag my_struct; /* declare the structure my_struct */
struct tag *st_ptr;

void show_name(struct tag *p);  /* function prototype */

int main(void)
{
  strcpy(my_struct.lname, "Jensen");
  strcpy(my_struct.fname, "Ted");
  printf("\n%s ", my_struct.fname);
  printf("%s\n", my_struct.lname);

  // struct pointer
  st_ptr = &my_struct;

  // These are the same
  (*st_ptr).age = 63;
  st_ptr->age = 62;

  show_name(st_ptr);          /* pass the pointer */

  return 0;
}

void show_name(struct tag *p)
{
    printf("\n%s ", p->fname);  /* p points to a structure */
    printf("%s ", p->lname);
    printf("%d\n", p->age);
}
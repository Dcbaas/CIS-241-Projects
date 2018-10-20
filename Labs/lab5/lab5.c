#include <stdio.h>
#include <stdlib.h>

struct Mark {
  int x;
  int y;
};

typedef struct Mark Mark;

/* load the structure that p points to with the date from f */
void getInfo (FILE * f, Mark * p);

/* write the data stored in structure item into output file f */
void printInfo (FILE * f, Mark item);

/* compare what pointers a and b point to; to be used by qsort() */
int compare (const void * a, const void * b);

/* writes the data to an outfile */
void writeOutfile(Mark*);

int main()
{
  Mark list[100];
  Mark mark;
  int size = 0, i;
  FILE * fin;

  fin = fopen ("lab5.dat", "r");
  if ( fin == NULL )
  {
    printf ("Cannot open file.\n");
    exit(1);
  }

  while ( !feof(fin) )
  {
    getInfo (fin, &mark);
    list[size++] = mark;
  }

  // write a statement that uses qsort() to sort data in list
  qsort(list, 75, sizeof(Mark),compare);

  for (i = 0; i < size; i++)
    printInfo (stdout, list[i]);

  printf("\n");

  writeOutfile(list);

  fclose (fin);

  return 0;
}


void getInfo (FILE * f, Mark * p)
{
  fscanf (f, "%d%d", &(p->x), &(p->y));

}

void printInfo (FILE * f, Mark item)
{
  static int col = 0;
  fprintf (f, "(%d, %d) ", item.x, item.y);
  if ( ++col % 5 == 0 )
    fprintf(f, "\n");
}

void writeOutfile(Mark* list){
  FILE* outfile = fopen("outfile.txt", "w");
  if(!outfile){
    fprintf(stderr, "ERROR WITH OUTFILE");
  }

  for(int index = 0; index < 75; ++index){
    fprintf(outfile, "%d,%d\n", list[index].x, list[index].y);
  }

  fclose(outfile);
} 

// complete the definition of function compare
int compare (const void * a, const void * b)
{
  Mark* mark_a= (Mark*)a;
  Mark* mark_b= (Mark*)b;

  //compare the y values
  //less than
  if(mark_a->y < mark_b->y)
    return -1;
  //greater than
  else if(mark_a->y > mark_b->y)
    return 1;
  //The y values are equal compare the x values
  else{
    if(mark_a->x < mark_b->x)
      return -1;
    else if(mark_b->x < mark_a->x)
      return 1;
  }
  //Both structs are equal. return 0
  return 0;
}


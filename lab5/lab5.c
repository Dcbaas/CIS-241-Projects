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

	for (i = 0; i < size; i++)
		printInfo (stdout, list[i]);

	printf("\n");

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

// complete the definition of function compare
int compare (const void * a, const void * b)
{

}


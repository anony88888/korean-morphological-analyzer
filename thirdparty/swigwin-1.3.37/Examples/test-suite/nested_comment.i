%module nested_comment

// this example shows a problem with 'dump_nested' (parser.y).

// bug #949654
%inline %{
typedef struct s1 {
union {
int fsc; /* genie structure hiding - Conductor
*/
int fso; /* genie structure hiding - FSOptions
*/
struct {
double *vals;
int size;
} vector_val; /* matrix values are mainly used
in rlgc models */
char *name;
} n ;
} s2; 
%}

// comment in nested struct
%inline %{
struct a
{
  struct {
    /*struct*/
    struct {
      int b;
    } c;
  } d;
};
%}


#include <igraph.h>
#include <stdlib.h>

void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, " %li", (long int) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

int main() {
  
  igraph_vector_t v, v2;
  int i;
  real_t *ptr;

  /* simple init */
  igraph_vector_init(&v, 0);
  igraph_vector_destroy(&v);

  /* VECTOR(), igraph_vector_size */
  igraph_vector_init(&v, 10);
  for (i=0; i<igraph_vector_size(&v); i++) {
    VECTOR(v)[i]=10-i;
  }
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_reserve, igraph_vector_push_back */
  igraph_vector_init(&v, 0);
  igraph_vector_reserve(&v, 10);
  for (i=0; i<10; i++) {
    igraph_vector_push_back(&v, i);
  }

  /* igraph_vector_empty, igraph_vector_clear */
  if (igraph_vector_empty(&v)) {
    return 1;
  }
  igraph_vector_clear(&v);
  if (!igraph_vector_empty(&v)) {
    return 2;
  }
  igraph_vector_destroy(&v);

  /* igraph_vector_e, igraph_vector_e_ptr */
  igraph_vector_init(&v, 5);
  for (i=0; i<igraph_vector_size(&v); i++) {
    *igraph_vector_e_ptr(&v, i) = 100*i;
  }
  for (i=0; i<igraph_vector_size(&v); i++) {
    fprintf(stdout, " %li", (long int)igraph_vector_e(&v, i));
  }
  fprintf(stdout, "\n");
  igraph_vector_destroy(&v);

  /* igraph_vector_set */
  igraph_vector_init(&v, 5);
  for (i=0; i<igraph_vector_size(&v); i++) {
    igraph_vector_set(&v, i, 20*i);
  }
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_null */
  igraph_vector_init(&v, 0);
  igraph_vector_null(&v);
  igraph_vector_destroy(&v);
  igraph_vector_init(&v, 10);
  for (i=0; i<igraph_vector_size(&v); i++) {
    VECTOR(v)[i]=i+1;
  }
  igraph_vector_null(&v);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_tail, igraph_vector_pop_back */
  igraph_vector_init(&v, 10);
  for (i=0; i<igraph_vector_size(&v); i++) {
    VECTOR(v)[i]=i+1;
  }
  while (!igraph_vector_empty(&v)) {
    fprintf(stdout, " %li", (long int)igraph_vector_tail(&v));
    fprintf(stdout, " %li", (long int)igraph_vector_pop_back(&v));
  }
  fprintf(stdout, "\n");
  igraph_vector_destroy(&v);

  /* igraph_vector_init_seq, igraph_vector_order */
  igraph_vector_init_seq(&v, 1, 10);
  igraph_vector_init(&v2, 0);
  igraph_vector_order(&v, &v2, 10);
  print_vector(&v2, stdout);
  igraph_vector_destroy(&v2);
  igraph_vector_destroy(&v);

  /* igraph_vector_resize, igraph_vector_sort */
  igraph_vector_init(&v, 20);  
  for (i=0; i<10; i++) {
    VECTOR(v)[i]=10-i;
  }
  igraph_vector_resize(&v, 10);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_max, igraph_vector_init_copy */
  igraph_vector_init(&v, 10);
  for (i=0; i<igraph_vector_size(&v); i++) {
    VECTOR(v)[i]=100-i;    
  }
  for (i=0; i<10; i++) {
    fprintf(stdout, " %li", (long int)VECTOR(v)[i]);
  }
  fprintf(stdout, "\n");
  fprintf(stdout, " %li\n", (long int)igraph_vector_max(&v));

  igraph_vector_destroy(&v);
  ptr=(real_t*) malloc(10* sizeof(real_t));
  igraph_vector_init_copy(&v, ptr, 10);
  free(ptr);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);
  
  /* igraph_vector_copy_to */
  ptr=(real_t*) malloc(10* sizeof(real_t));
  igraph_vector_init_seq(&v, 11, 20);
  igraph_vector_copy_to(&v, ptr);
  for (i=0; i<10; i++) {
    fprintf(stdout, " %li", (long int)ptr[i]);
  }
  fprintf(stdout, "\n");
  free(ptr);
  igraph_vector_destroy(&v);

  /* igraph_vector_init_seq, igraph_vector_sum, igraph_vector_prod */
  igraph_vector_init_seq(&v, 1, 5);
  fprintf(stdout, " %li", (long int)igraph_vector_sum(&v));
  fprintf(stdout, " %li\n", (long int)igraph_vector_prod(&v));
  
  /* igraph_vector_remove_section */
  igraph_vector_remove_section(&v, 2, 4);
  fprintf(stdout, " %li", (long int)igraph_vector_sum(&v));
  fprintf(stdout, " %li\n", (long int)igraph_vector_prod(&v));
  igraph_vector_destroy(&v);

  /* igraph_vector_remove */
  igraph_vector_init_seq(&v, 1, 10);
  igraph_vector_remove(&v, 9);
  igraph_vector_remove(&v, 0);
  igraph_vector_remove(&v, 4);
  fprintf(stdout, " %li\n", (long int)igraph_vector_sum(&v));
  igraph_vector_destroy(&v);

  /* igraph_vector_move_interval */
  igraph_vector_init_seq(&v, 0, 9);
  igraph_vector_move_interval(&v, 5, 10, 0);
  if (igraph_vector_sum(&v) != 70) {
    return 3;
  }
  igraph_vector_destroy(&v);
    
  /* igraph_vector_isininterval */
  igraph_vector_init_seq(&v, 1, 10);
  if (!igraph_vector_isininterval(&v, 1, 10)) {
    return 4;
  }
  if (igraph_vector_isininterval(&v, 2, 10)) {
    return 5;
  }
  if (igraph_vector_isininterval(&v, 1, 9)) {
    return 6;
  }

  /* igraph_vector_any_smaller */
  if (igraph_vector_any_smaller(&v, 1)) {
    return 7;
  }
  if (!igraph_vector_any_smaller(&v, 2)) {
    return 8;
  }
  igraph_vector_destroy(&v);

  /* igraph_vector_is_equal */

  /* igraph_vector_binsearch */
  igraph_vector_init_seq(&v, 0, 9);
  for (i=0; i<igraph_vector_size(&v); i++) {
    if (!igraph_vector_binsearch(&v, 0, 0)) {
      return 9;
    }
  }
  if (igraph_vector_binsearch(&v, 10, 0)) {
    return 10;
  }
  if (igraph_vector_binsearch(&v, -1, 0)) {
    return 11;
  }
  for (i=0; i<igraph_vector_size(&v); i++) {
    VECTOR(v)[i]= 2*i;
  }
  for (i=0; i<igraph_vector_size(&v); i++) {
    long int pos;
    if (!igraph_vector_binsearch(&v, VECTOR(v)[i], &pos)) {
      fprintf(stderr, "cannot find %i\n", (int)VECTOR(v)[i]);
      return 12;
    }
    if (pos != i) {
      return 13;
    }
    if (igraph_vector_binsearch(&v, VECTOR(v)[i]+1, &pos)) {
      return 14;
    }
  }
  igraph_vector_destroy(&v);

  /* igraph_vector_init_real */
  igraph_vector_init_real(&v, 10, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_init_int */
  igraph_vector_init_int(&v, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_init_real */
  igraph_vector_init_real_end(&v, -1, 1.0, 2.0, 3.0, 4.0, 5.0, 
		       6.0, 7.0, 8.0, 9.0, 10.0, -1.0);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_init_int */
  igraph_vector_init_int_end(&v, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  /* igraph_vector_permdelete */
  /* igraph_vector_remove_negidx */

  /* order2 */
  igraph_vector_init_int_end(&v, -1, 10,9,8,7,6,7,8,9,10, -1);
  igraph_vector_order2(&v);
  print_vector(&v, stdout);
  igraph_vector_destroy(&v);

  return 0;
}
  

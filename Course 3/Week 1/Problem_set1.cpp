#include <stdio.h> 
#include <stdlib.h>
  struct weight {
    int w;
    int l;
    int w_l;
    int C;
  };
typedef struct weight weight;
long int compute(weight job[], int jobs) {
  int i, j, p, C = 0;
  long int result = 0;
  weight arr;
  for (i = 0; i < jobs - 1; i++) {
    p = i;
    for (j = i + 1; j < jobs; j++) {
      if (job[j].w_l > job[p].w_l)
        p = j;
      else if ((job[j].w_l == job[p].w_l) && (job[j].w > job[p].w))
        p = j;
    }
    arr.w = job[i].w;
    arr.l = job[i].l;
    arr.w_l = job[i].w_l;
    job[i].w = job[p].w;
    job[i].l = job[p].l;
    job[i].w_l = job[p].w_l;
    job[p].w = arr.w;
    job[p].l = arr.l;
    job[p].w_l = arr.w_l;
  }
  for (i = 0; i < jobs; i++) {
    C += job[i].l;
    job[i].C = C;
    result += job[i].w * job[i].C;
  }
  return result;
}
int main(int argc, char **argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  int jobs, i, jw, jl;
  long int result = 0;
  fscanf(fp, "%d", &jobs);
  weight job[jobs];
  for (i = 0; i < jobs; i++) {
    fscanf(fp, "%d %d", &jw, &jl);
    job[i].w = jw;
    job[i].l = jl;
    job[i].w_l = jw - jl;
    job[i].C = 0;
  }
  result = compute(job, jobs);
  printf("%ld\n", result);
  return 0;
}

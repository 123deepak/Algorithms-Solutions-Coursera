#include<stdio.h>
#include<stdlib.h>
struct weight {
    int w;
    int l;
    float w_l;
    int C;
};
typedef struct weight weight;
long int compute(weight job[],int jobs) {
    int i,j,pos,C=0;
    long int total=0;
    weight arr;
    for(i=0; i<jobs-1; i++) {
        pos=i;
        for(j=i+1; j<jobs; j++) {
            if(job[j].w_l>job[pos].w_l)
                pos=j;
            else if((job[j].w_l==job[pos].w_l)&&(job[j].w>job[pos].w))
                pos=j;
        }
        arr.w=job[i].w;
        arr.l=job[i].l;
        arr.w_l=job[i].w_l;
        job[i].w=job[pos].w;
        job[i].l=job[pos].l;
        job[i].w_l=job[pos].w_l;
        job[pos].w=arr.w;
        job[pos].l=arr.l;
        job[pos].w_l=arr.w_l;
    }
    for(i=0; i<jobs; i++) {
        C+=job[i].l;
        job[i].C=C;
        total+=job[i].w*job[i].C;
    }
    return total;
}
int main(int argc,char **argv[]) {
    FILE *fp;
    fp=fopen(argv[1],"r");
    int jobs,i,jw,jl;
    long int total=0;
    fscanf(fp,"%d",&jobs);
    weight job[jobs];
    for(i=0; i<jobs; i++) {
        fscanf(fp,"%d %d",&jw,&jl);
        job[i].w=jw;
        job[i].l=jl;
        job[i].w_l=(float)jw/jl;
        job[i].C=0;
    }
    total=compute(job,jobs);
    printf("%ld\n",total);
    return 0;
}

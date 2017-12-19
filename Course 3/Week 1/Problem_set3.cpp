#include<stdlib.h>
#include<stdio.h>
struct prim {
    int v1;
    int v2;
    int e;
    int status;
};
typedef struct prim prim;
void sort(prim edge[],int e) {
    int i,j,v1,v2,ec,p;
    for(i=0; i<e-1; i++) {
        p=i;
        for(j=i+1; j<e; j++) {
            if(edge[j].e<=edge[p].e) {
                p=j;
            }
        }
        v1=edge[i].v1;
        v2=edge[i].v2;
        ec=edge[i].e;
        edge[i].v1=edge[p].v1;
        edge[i].v2=edge[p].v2;
        edge[i].e=edge[p].e;
        edge[p].v1=v1;
        edge[p].v2=v2;
        edge[p].e=ec;
    }
}
int main(int argc,char **argv[]) {
    FILE *fp;
    int i,j,u,v,e,v1,v2,ec;
    fp=fopen(argv[1],"r");
    if(!fp)
        exit(0);
    fscanf(fp,"%d %d",&v,&e);
    prim edge[e];
    int X[v],x=1,x_t=1,p,ctr=0;
    long int T=0;
    X[0]=1;
    for(i=0; i<e; i++) {
        fscanf(fp,"%d %d %d",&v1,&v2,&ec);
        edge[i].v1=v1;
        edge[i].v2=v2;
        edge[i].e=ec;
        edge[i].status=1;
    }
    sort(edge,e);
    while(x!=v) {
        ec=32766;
        ctr=0;
        for(j=0; j<x_t; j++) {
            u=X[j];
            for(i=0; i<e; i++) {
                if(edge[i].status==0)
                    break;
                else if(u==edge[i].v1) {
                    if(edge[i].e<ec) {
                        p=i;
                        ec=edge[i].e;
                        v=edge[i].v2;
                        ctr++;
                    }
                    break;
                }
                else if(u==edge[i].v2) {
                    if(edge[i].e<ec) {
                        p=i;
                        ec=edge[i].e;
                        v=edge[i].v1;
                        ctr++;
                    }
                    break;
                }
            }
        }
        if(ctr) {
            T+=ec;
            x++;
            X[x-1]=v;
            edge[p].status=0;
            x_t=x;
        }
    }
    printf("%ld\n",T);
    return 0;
}

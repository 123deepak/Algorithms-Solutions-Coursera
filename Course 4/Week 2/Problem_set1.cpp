#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<float.h>
#include<stdbool.h>
#define C(x1,y1,x2,y2) sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) )
int n;
struct City
{
    double x,y;
}*city;

void showcity()
{
    printf("Cities:\n");
    int i;
    for(i=0;i<n;i++)
        printf("City %2d: %lf %lf\n",i+1,city[i].x,city[i].y);
}
struct Subset
{
    long value;
    struct Subset *next;
}**arr2;
int *arr1;
void InitialInsert(int index,long value)
{
    struct Subset *subset=malloc(sizeof(struct Subset));
    subset->value=value;
    subset->next=arr2[index];
    arr2[index]=subset;

    arr1[index]++;
}
void display_arr2()
{
    printf("Power Set of Length %d:\n",n);

    int i;
    for(i=1;i<=n;i++)
    {
        printf("Subsets of Size %d\n",i);
        struct Subset *subset;
        for(subset=arr2[i-1];subset!=NULL;subset=subset->next)
            printf("%ld ",subset->value);
        printf("\n");
    }
}
void hashtable_insert(int,int);
void insert_arr2_into_hashtable()
{
    int i;
    for(i=0;i<n;i++)
    {
        struct Subset *subset;
        int index;
        for(index=0,subset=arr2[i];subset!=NULL;index++,subset=subset->next)
            hashtable_insert(subset->value,index);
    }
}
int NumberOfSetBits(int i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
void calculate_result()
{
    int i;
    int power_set_size=pow(2,n-1);
    for(i=0;i<power_set_size;i++)
    {
        InitialInsert(NumberOfSetBits(i),i*2+1);
    }
}
double **A_predecessor;
double **A_current;
int *subset_label_predecessor;
int *subset_label_current;
#define HASH_TABLE_SIZE 33554432
struct hashTable
{
    int key;
    int index;
    struct hashTable *next;
}*hash_table[HASH_TABLE_SIZE];
int h(int x)
{
    return ((long long)x * 33350693) % HASH_TABLE_SIZE;
}
void hashtable_insert(int x,int i)
{
    int hx=h(x);

    struct hashTable *new_elem = malloc(sizeof(struct hashTable));
    new_elem->key=x;
    new_elem->index=i;
    new_elem->next=hash_table[hx];
    hash_table[hx]=new_elem;
}

#define NOT_AN_INDEX -1
int lookup(int x)
{
    int hx=h(x);

    struct hashTable *ptr;
    for(ptr=hash_table[hx];ptr!=NULL;ptr=ptr->next)
    {
        if(ptr->key==x)
            return ptr->index;
    }

    return NOT_AN_INDEX;
}
int main()
{
    FILE *fin=fopen("Inputfiles\\tsp.txt","r");
    if(!fin)
    {
        printf("Unable to Read from File");
        exit(0);
    }
    fscanf(fin,"%d",&n);
    city=malloc(n*sizeof(struct City));
    int i;
    for(i=0;i<n;i++)
        fscanf(fin,"%lf%lf",&city[i].x,&city[i].y);
    fclose(fin);
    arr2=calloc(n,sizeof(struct Subset *));
    arr1=calloc(n,sizeof(int));
    calculate_result();
    insert_arr2_into_hashtable();
    int max_set = pow(2,n)-1;
    bool is_n_even = n%2==0;
	int last_m = n/2;
    struct Subset *subset;
	subset_label_predecessor = malloc(arr1[0]*sizeof(int));
    for(subset=arr2[0],i=0;subset!=NULL;subset=subset->next,i++)
        subset_label_predecessor[i]=subset->value;
	A_predecessor=malloc(arr1[0]*sizeof(double *));
    for(i=0;i<arr1[0];i++)
    {
        A_predecessor[i]=malloc(n*sizeof(double));
        int p;
        for(p=0;p<n;p++)
            A_predecessor[i][p]=DBL_MAX;
    }
	A_predecessor[0][0]=0;
	int m;
    int s;
    int j;
    int value_j;
    int s_minus_j,s_minus_j_index;
    int k;
    int value_k;

    printf("Dynamic Programming Loop Begins\n");
    for(m=1;m<=last_m;m++)
    {
        printf("%.2f%% Complete\n",(float)2*m/(n-1)*100);
	    subset_label_current = malloc(arr1[m]*sizeof(int));
        for(subset=arr2[m],i=0;subset!=NULL;subset=subset->next,i++)
            subset_label_current[i]=subset->value;
	    A_current=malloc(arr1[m]*sizeof(double *));
        for(i=0;i<arr1[m];i++)
        {
            A_current[i]=malloc(n*sizeof(double));
            int p;
            for(p=0;p<n;p++)
                A_current[i][p]=DBL_MAX;
        }
      for(s=0;s<arr1[m];s++)
        {
            for(j=1,value_j=2;j<n;j++,value_j=value_j<<1)
            {
                if(subset_label_current[s] & value_j)
                {
                    s_minus_j = subset_label_current[s] & (~value_j);
                    s_minus_j_index = lookup(s_minus_j);
                    for(k=0,value_k=1;k<n;k++,value_k=value_k<<1)
                    {
                        if((k!=j) && (subset_label_current[s] & value_k))
                        {
                            double Ckj = C(city[k].x,city[k].y,city[j].x,city[j].y);
                            if((A_predecessor[s_minus_j_index][k]!=DBL_MAX) && (A_predecessor[s_minus_j_index][k] + Ckj < A_current[s][j]))
                                A_current[s][j] = A_predecessor[s_minus_j_index][k] + Ckj;
                        }
                    }
                }
            }
        }
        if(is_n_even && m==last_m)
            break;
        for(i=0;i<arr1[m-1];i++)
            free(A_predecessor[i]);
        free(A_predecessor);

        A_predecessor=A_current;

        free(subset_label_predecessor);

        subset_label_predecessor=subset_label_current;

    }

    double min_tour_cost=DBL_MAX;

    int s1,s2;
    int j1,value1,j2,value2;
    int cost_of_tour;

    if(!is_n_even)
        printf("%d\n",arr1[last_m],last_m);
    else
        printf("%d, %d, and %d, %d\n",arr1[last_m],last_m,arr1[last_m-1],last_m-1);
    if(!is_n_even)
    {
    for(s1=0;s1<arr1[last_m];s1++)
    {
        int complement_set = (max_set ^ subset_label_current[s1]) + 1;
        s2 = lookup(complement_set);
        if(s2!=NOT_AN_INDEX)
        {
            for(j1=1,value1=2;j1<n;j1++,value1<<=1)
            {
                if(subset_label_current[s1] & value1)
                {
                    for(j2=1,value2=2;j2<n;j2++,value2<<=1)
                    {
                        if(subset_label_current[s2] & value2)
                        {
                            cost_of_tour = A_current[s1][j1] + C(city[j1].x,city[j1].y,city[j2].x,city[j2].y) + A_current[s2][j2];
                            if(cost_of_tour < min_tour_cost)
                                min_tour_cost = cost_of_tour;
                        }
                    }
                }
            }
        }
    }
    }
  else
    {
    for(s1=0;s1<arr1[last_m];s1++)
    {
		int complement_set = (max_set ^ subset_label_current[s1]) + 1;
        s2 = lookup(complement_set);
		if(s2!=NOT_AN_INDEX)
        {
            for(j1=1,value1=2;j1<n;j1++,value1<<=1)
            {
                if(subset_label_current[s1] & value1)
                {
                    for(j2=1,value2=2;j2<n;j2++,value2<<=1)
                    {
                        if(subset_label_predecessor[s2] & value2)
                        {
                            cost_of_tour = A_current[s1][j1] + C(city[j1].x,city[j1].y,city[j2].x,city[j2].y) + A_predecessor[s2][j2];
                            if(cost_of_tour < min_tour_cost)
                                min_tour_cost = cost_of_tour;
                        }
                    }
                }
            }
        }
    }
    }
    printf("Cost of an Optimal Tour: %d\n",(int)min_tour_cost);

    return 0;
}

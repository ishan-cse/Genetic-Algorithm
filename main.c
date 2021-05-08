#include <stdio.h>

int population=30,pattern_size=8,r=0;
int a[9][9],generation=0;

int genetic_algorithm_agent();
void fitness_finder(int p);
int number_of_attack(int row, int col);
void lowest_population_remover();
void crossover();
void mutation();

struct CHROMOSOME
{
    int fitness;
    int pattern[9];
}chromosome[31];

struct temporary
{
    int temp_pattern[9];
}temp[31];

int main()
{

   int i,j;

   for(i=1;i<=population;i++)
   {
     for(j=1;j<=pattern_size;j++)
     {
         int num;

         num = rand() % pattern_size + 1;

         chromosome[i].pattern[j]=num;
     }
   }

// call function

   genetic_algorithm_agent();


   printf("\n\n\n result founded \n\n");

   printf(" generation : %d \n",generation);

    return 0;
}

int genetic_algorithm_agent()
{
  if(r==0)
  {
        generation=generation+1;

        printf("\n\n #generation no : %d \n\n",generation);

    for(int k=1;k<=population;k++)
    {
        chromosome[k].fitness=0;
    }

    for(int p=1;p<=population;p++)
    {

      fitness_finder(p);

      if(r==1)
    {
        break;
    }

    }

    if(r==0)
    {

     lowest_population_remover();

     crossover();

     mutation();

     genetic_algorithm_agent();

    }
  }
}

void fitness_finder(int p)
{

    int count=0;

    for(int i=1;i<=pattern_size;i++)
    {
        for(int j=1;j<=pattern_size;j++)
        {
            a[i][j]=0;
        }
    }

  printf("\n\n # chromosome no : %d \n",p);

    for(int k=1;k<=pattern_size;k++)
    {
        a[chromosome[p].pattern[k]][k] = 1;
    }

//print patterns

    printf("\n pattern : ");

     for(int j=1;j<=pattern_size;j++)
     {
       printf(" %d", chromosome[p].pattern[j]);
     }

// print queen position in board

   printf("\n\n");

    for(int i=1;i<=pattern_size;i++)
    {
        for(int j=1;j<=pattern_size;j++)
        {
            printf(" %d",a[i][j]);
        }
        printf("\n");
    }

//check non_attack

    for(int i=1;i<=pattern_size;i++)
    {
        for(int j=1;j<=pattern_size;j++)
        {
            if(a[i][j]==1)
            {
                int y=number_of_attack( i, j);

                int l= (8 - y - j);

                count = count + l;
            }
        }
    }

    if(count==28)
    {
        r=r+1;
    }

     chromosome[p].fitness=count;

   printf("\n--> fitness = %d\n",chromosome[p].fitness);

}

int number_of_attack(int row, int col)
{
    int i, j,c=0;

// row on the right

    i = col + 1;

    while(i <= pattern_size)
    {
       if (a[row][i]==1)
        {
            c=c+1;
            break;
        }

         i++;
    }

// top diagonal on the right

      i = row-1;
      j = col+1;

      while(i >= 1 && j <= pattern_size)
      {
          if (a[i][j]==1)
          {
              c=c+1;
              break;
          }

            i--;
            j++;
      }

// down diagonal on the right

       i = row+1;
       j = col+1;

       while(j <=pattern_size && i <= pattern_size)
       {
           if (a[i][j]==1)
            {
                c=c+1;
                break;
            }

              i++;
              j++;
       }

    return c;
}

void lowest_population_remover()
{
      int i,j,min=99999,second_min=999999;
      int low_first,low_second;

// find lowest first

     for(i=1;i<=population;i++)
      {
          if(chromosome[i].fitness<min)
            {
                  min=chromosome[i].fitness;
                  low_first=i;
            }
      }

// find lowest second

      for(i=1;i<=population;i++)
          {
           if((chromosome[i].fitness<second_min)&&(chromosome[i].fitness>min))
              {
                   second_min=chromosome[i].fitness;
                   low_second=i;
              }
          }

//print

     printf("\n\n # The lowest two population which will be removed from population : \n\n");

     for(i=1;i<=pattern_size;i++)
     {
         printf(" %d",chromosome[low_first].pattern[i]);
     }

     printf("\n");

     for(i=1;i<=pattern_size;i++)
     {
         printf(" %d",chromosome[low_second].pattern[i]);
     }

      printf("\n");

// remove lowest first

    for(i=low_first;i<=population;i++)
     {
       for(j=1;j<=pattern_size;j++)
        {
          chromosome[i].pattern[j]=chromosome[i+1].pattern[j];
        }
     }

// remove lowest second

    for(i=low_second;i<=population;i++)
     {
       for(j=1;j<=pattern_size;j++)
        {
          chromosome[i].pattern[j]=chromosome[i+1].pattern[j];
        }
     }

}

void crossover()
{
    int c1=1,c2=2,i;

    for(i=1;i<=(population/2);i++)
    {
        int num1,num2,devider;
        int temp1[9],temp2[9];

// random pair selection for crossover

        num1 = rand() % (population-2) + 1;
        num2 = rand() % (population-2) + 1;

        devider = rand() % pattern_size + 1;

// print

        printf("\n\n # selected random pair for crossover : \n");

        for(int x=1;x<=pattern_size;x++)
        {
          printf(" %d",chromosome[num1].pattern[x]);
        }

        printf("\n");

        for(int y=1;y<=pattern_size;y++)
        {
          printf(" %d",chromosome[num2].pattern[y]);
        }

        printf("\n\n random crossover point \n %d",devider);

// give value chromosome sturct from temp

        for(int m=1;m<=pattern_size;m++)
        {
          temp1[m]=chromosome[num1].pattern[m];
          temp2[m]=chromosome[num2].pattern[m];
        }

// pair's crossover

       for(int j=devider;j<=pattern_size;j++)
       {
         temp1[j]=chromosome[num2].pattern[j];
         temp2[j]=chromosome[num1].pattern[j];
       }

// print

     printf("\n\n after crossover : \n");

       int l;
        
       for(l=1;l<=pattern_size;l++)
       {
         printf(" %d",temp1[l]);
       }

       printf("\n");

        for(l=1;l<=pattern_size;l++)
       {
         printf(" %d",temp2[l]);
       }

// set the value to temp struct

       for(int k=1;k<=pattern_size;k++)
       {
         temp[c1].temp_pattern[k]=temp1[k];
         temp[c2].temp_pattern[k]=temp2[k];
       }

       c1=c1+2;
       c2=c2+2;
    }

// set the value to chromosome struct from the temp sturct

       for(int p=1;p<=population;p++)
        {
           for(int pt=1;pt<=pattern_size;pt++)
           {
               chromosome[p].pattern[pt] = temp[p].temp_pattern[pt];
           }
        }
}

void mutation()
{
    for(int i=1;i<=population;i++)
    {
        int mutation_index,mutation_value;

        mutation_index = rand() % pattern_size + 0;
        mutation_value = rand() % pattern_size + 1;

        chromosome[i].pattern[mutation_index] = mutation_value;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int poblar (int *red, float p, int dim);
int contornos(int *red, int dim);
int flipeo(int *red, int dim, int Be);
int imprimir(int *red,int dim);


//Función principal:
int main(int argc,char*argv[])
{ float p, Be=0.5;
  int dim, i, it=1;
  int *red;

  sscanf(argv[1],"%d",& dim);           //Busca el primero de los argumentos y lo usa como dim.
  sscanf(argv[2],"%f",& p);             //Busca el segundo de los argumentos y lo usa como p.

  dim = dim + 2;

  red = malloc(dim*dim*sizeof(int));    //Reserva el espacio necesario para la red.

  poblar(red, p, dim);
  contornos(red,dim);
  imprimir(red,dim);
  for (i=0; i<it;i++)
    { flipeo(red, dim, Be);
      contornos(red,dim);
      printf("\n");
      imprimir(red,dim);
    }


  free(red);

  return 0;
}

//Funciones secundarias:
int poblar(int *red, float p, int dim)
{ float random;
  int i, j;

  srand(1);

  for (i=1;i<dim-1;i++)
    { for (j=1;j<dim-1;j++)
      { *(red+i*dim+j)=0;                           //Asigna por defecto el valor <vacio>.
      random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
      if (random<p)
        {*(red+i*dim+j)=1;                          //Asigna spin pos. si el valor aleatorio es menor.
        }
      else
        {*(red+i*dim+j)=-1;                         //Asigna spin neg. si el valor aleatorio es mayor.
        }
      }
    }

  return 0;
}

int contornos(int *red, int dim)
  { int i;

    for (i=1;i<dim-1;i++)
      { *(red+i) = *(red+(dim-2)*dim+i);        //Contorno Sup.
        *(red+(dim-1)*dim+i) = *(red+dim+i);    //Contorno Inf.
        *(red+i*dim) = *(red+(i+1)*dim-2);      //Contorno Izq.
        *(red+(i+1)*dim-1) = *(red+i*dim+1);    //Contorno Der.
      }

    return 0;
  }

int flipeo(int *red, int dim, int Be)
  { float r;//, delta=2.8, x_n, x_v=-0.5
    float *P_ind;
    int i, j;

    srand(time(NULL));

    P_ind = malloc(2*sizeof(float));

    *(P_ind) = 0.37;//1.0/exp(2*Be);
    *(P_ind+1) = 7;//exp(2*Be);         //No me dan las exponenciales!!

    //x_n = x_v + ((float)rand())/((float)RAND_MAX) * (2.0*delta) - delta;    //x nuevo dentro del intervalo.

    for (i=1;i<dim-1;i++)
      { for (j=1;j<dim-1;j++)
        { //if(exp(((x_v*x_v)-(x_n*x_n))/2.0) > r)
          r = ((float)rand())/((float)RAND_MAX);

          if(*(P_ind+((*(red+i*dim+j) + 1)/2))>r) //Tal vez esto no sea así.
            { *(red+i*dim+j) = - *(red+i*dim+j);
              printf(" r=%f y P_ind=%f en %i |",r,*(P_ind+((*(red+i*dim+j) + 1)/2)),i*dim+j);
              //x_v = x_n;
              //x_n = x_v + ((float)rand())/((float)RAND_MAX) * (2.0*delta) - delta;
            }
          /*else
            { x_v = x_n;
              x_n = x_v + ((float)rand())/((float)RAND_MAX) * (2.0*delta) - delta;
            }*/
          }
        }
    return 0;
  }

int imprimir(int *red, int dim)         //Imprime una fila debajo de la otra.
{ int i,j;

  for (i=0;i<dim;i++)
    {for (j=0;j<dim;j++)
      {
      printf("%02d ", *(red+dim*i+j));
      }
    printf("\n");
    }

  return 0;
}

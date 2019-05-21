#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int poblar (int *red, float p, int dim);
int contornos(int *red, int dim);
int imprimir(int *red,int dim);


//Función principal:
int main(int argc,char*argv[])
{ float p;
  int dim;
  int *red;

  sscanf(argv[1],"%d",& dim);           //Busca el primero de los argumentos y lo usa como dim.
  sscanf(argv[2],"%f",& p);             //Busca el segundo de los argumentos y lo usa como p.

  dim = dim + 2;

  red = malloc(dim*dim*sizeof(int));    //Reserva el espacio necesario para la red.

  poblar(red, p, dim);
  imprimir(red,dim);
  contornos(red,dim);
  printf("\n");
  imprimir(red,dim);

  free(red);

  return 0;
}

//Funciones secundarias:
int poblar(int *red, float p, int dim)
{ float random;
  int i, j;

  srand(1);

  for (i=1;i<dim-1;i++)
    { for (j=1;j<dim-1;j++)//Toma como rango máximo la cantidad de celdas totales.
      { *(red+i*dim+j)=0;                       //Asigna por defecto el valor <vacio>
      random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
      if (random<p)
        {*(red+i*dim+j)=1;
        }
      else
        {*(red+i*dim+j)=-1;
        }//Asigna como <lleno> si el valor aleatorio es menor.
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

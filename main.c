/**este programa te permite subir registros con libros, podes anotar de manera muy facil
en que pagina de quedaste en un libro pdf**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define ARCHIVO "guardados.dat"

/*para menu modificar registro*/
#define FIL 6
#define COL 50


typedef struct
{
    char titulo[50];
    char autor[50];
    char tematica[50];
    int pagTotales;
    int pagAleer;
} stLibro;

const int DIM = sizeof(stLibro);

void CargarLibrosArchivo();
stLibro CargarUnLibro();
void MostrarLibrosArchivo();
void MostrarUnLibro(stLibro target);
void ModificarRegistro(int numReg);
int AsignarMenu(int fil, int col, char p[fil][col]);
void MostrarMenu(int fil, int col, char p[fil][col], int v);
int AsignarMenuPrincipal(int fil,int col, char p[fil][col]);
void MostrarMenuPrincipal(int fil, int col, char p[fil][col],int v);

int main()
{
    SetConsoleTitle("L23 Reader v.1.0");
    system("color 1F");
    int opcionRegistro = 0; /**es numero de registro que quiera modificar*/
    int seleccion = 0;
    char control = 0;

    char menu[FIL][COL];
    int validosMenu = AsignarMenuPrincipal(FIL,COL,menu);

    do
    {

        MostrarMenuPrincipal(FIL,COL,menu,validosMenu);

        scanf("%i",&seleccion);

        switch(seleccion)
        {
        case 1:

            CargarLibrosArchivo();
            break;

        case 2:

            printf("\nLibros Cargados:\n");
            MostrarLibrosArchivo();
            break;

        case 3:

            printf("Que registro desea modificar?\n");
            scanf("%i",&opcionRegistro);
            ModificarRegistro(opcionRegistro);
            break;

        case 4:

            printf("\n\nNos vemos viejita\n");
            control = 'n';
            break;

        default:

            printf("Tecla invalida...\n");
            break;

        }

        if(seleccion != 4)
        {
            printf("\nRealizar otra accion? s/n\n");
            scanf("\n%c",&control);
        }

    }
    while( tolower(control) == 's' );

    return 0;
}

void CargarLibrosArchivo()
{
    FILE* pfile = NULL;
    stLibro aCargar;
    int cerrarArchivo = 0;
    int escribirArchivo = 0;
    pfile = fopen(ARCHIVO,"wb");

    if(pfile)
    {
        aCargar = CargarUnLibro();

        escribirArchivo = fwrite(&aCargar,DIM,1,pfile);

        if(escribirArchivo < 1)

            printf("NO SE PUDO ESCRIBIR EN EL ARCHIVO EN CargarLibros.\n");

        cerrarArchivo = fclose(pfile);

        if(cerrarArchivo!=0)

            printf("NO SE PUEDE CERRAR EL ARCHIVO EN CargarLibros.\n");
    }
    else
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO EN CargarLibros.\n");
    }
}

stLibro CargarUnLibro()
{
    stLibro aux;

    printf("%66s","-Carga de Datos-\n");

    printf("Titulo del libro:\n");
    fflush(stdin);
    gets(aux.titulo);

    printf("Autor del libro:\n");
    fflush(stdin);
    gets(aux.autor);

    printf("Tematica:\n");
    fflush(stdin);
    gets(aux.tematica);

    printf("Cantidad de paginas del libro:\n");
    scanf("%i",&aux.pagTotales);

    printf("Pagina a retomar lectura:\n");
    scanf("%i",&aux.pagAleer);

    return aux;
}

void MostrarLibrosArchivo()
{
    FILE* pfile = NULL;
    pfile = fopen(ARCHIVO,"rb");
    stLibro aLeer;
    int i = 1; /**Muestra un contador de registros*/
    int cerrarArchivo = 0;
    int leerArchivo = 0;

    if(pfile)
    {

        while( (fread(&aLeer,DIM,1,pfile)) > 0 )
        {
            printf("%i:\n",i);
            MostrarUnLibro(aLeer);
            i++;
        }

        cerrarArchivo = fclose(pfile);

        if(cerrarArchivo!=0)

            printf("NO SE PUDO CERRAR EL ARCHIVO EN MostrarLibros.\n");

    }
    else
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO EN MostrarLibros.\n");
    }
}

void MostrarUnLibro(stLibro target)
{
    printf("***************************************************************\n");
    printf("Titulo: %s\n",target.titulo);
    printf("Autor: %s\n",target.autor);
    printf("Tematica: %s\n",target.tematica);
    printf("Paginas totales: %i\n",target.pagTotales);
    printf("Pagina a retormar: %i\n",target.pagAleer);
    printf("***************************************************************\n\n");
}

void ModificarRegistro(int numReg)
{
    FILE* pfile = fopen(ARCHIVO,"r+b");
    stLibro aux;
    int cerrarArchivo = 0; /**verifica cierre del archivo*/
    int punteroSeek = 0; /**verifica los limites del archivo*/
    char opcion = 0;
    int escribirArchivo = 0; /**verifica escritura en archivo**/

    if(pfile)
    {

        punteroSeek = fseek(pfile,DIM*(numReg - 1),SEEK_SET);

        if(punteroSeek!=0)

            printf("SE HA SOBREPASADO LOS LIMITES DEL ARCHIVO.\n");

        fread(&aux,DIM,1,pfile);

        MostrarUnLibro(aux);

        printf("Desea modificar este registro? s/n\n");
        scanf("\n%c",&opcion);

        if(opcion == 's')
        {
            char menu[FIL][COL]; /**contiene el menu**/

            int validosMenu = AsignarMenu(FIL,COL,menu);

            int seleccionCaso = 0;

            char control = 0;

            do
            {

                MostrarMenu(FIL,COL,menu,validosMenu);

                scanf("%i",&seleccionCaso);

                switch(seleccionCaso)
                {

                case 1:

                    printf("Actual: %s\n",aux.titulo);
                    printf("Ingrese nuevo titulo:\n");
                    fflush(stdin);
                    gets(aux.titulo);
                    break;

                case 2:

                    printf("Actual: %s\n",aux.autor);
                    printf("Ingrese nuevo autor:\n");
                    fflush(stdin);
                    gets(aux.autor);
                    break;

                case 3:

                    printf("Actual: %s\n",aux.tematica);
                    printf("Ingrese nueva tematica:\n");
                    fflush(stdin);
                    gets(aux.tematica);
                    break;

                case 4:

                    printf("Actual: %i\n",aux.pagTotales);
                    printf("Ingrese nuevo numero de paginas totales:\n");
                    scanf("%i",&aux.pagTotales);
                    break;

                case 5:

                    printf("Ultima pagina a retormar: %i\n",aux.pagAleer);
                    printf("Ingrese la nueva pagina a retomar:\n");
                    scanf("%i",&aux.pagAleer);
                    break;

                default:

                    printf("Tecla invalida.\n");
                    getchar();
                    break;
                }

                printf("Modificar algo mas? s/n\n");
                scanf("\n%c",&control);

            }
            while(tolower(control) == 's');

            punteroSeek = fseek(pfile,DIM*(-1),SEEK_CUR);

            if(punteroSeek!=0)
            {
                printf("ERROR EN EL PUNTERO DEL ARCHIVO.\n");
            }

            escribirArchivo = fwrite(&aux,DIM,1,pfile);

            if(escribirArchivo < 1)
            {
                printf("ERROR AL ESCRIBIR EN EL ARCHIVO.\n");
            }
            else
            {
                printf("\nSe han guardado tus cambios!\n");
            }

        }

        cerrarArchivo = fclose(pfile);

        if(cerrarArchivo != 0)
        {
            printf("NO SE PUDO CERRAR EL ARCHIVO EN ModificarRegistro.\n");
        }

    }
    else
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO EN ModificarRegistro.\n");
    }
}

int AsignarMenu(int fil,int col, char p[fil][col])
{
    strcpy(p[0],"\nSelecciona el campo a modificar:\n");
    strcpy(p[1],"1-----------Titulo\n");
    strcpy(p[2],"2-----------Autor\n");
    strcpy(p[3],"3-----------Tematica\n");
    strcpy(p[4],"4-----------Paginas totales\n");
    strcpy(p[5],"5-----------Pagina a retomar\n");

    return 6;
}

void MostrarMenu(int fil, int col, char p[fil][col],int v)
{
    int i = 0;

    while ( i < v)
    {
        puts(p[i]);
        i++;
    }
}

int AsignarMenuPrincipal(int fil, int col, char p[fil][col])
{
    strcpy(p[0],"\nBienvenido a L23 Reader, selecciona tu accion!\n\n");
    strcpy(p[1],"1-----------------------Cargar un libro.\n");
    strcpy(p[2],"2-----------------------Mostrar libros.\n");
    strcpy(p[3],"3-----------------------Modificar un libro.\n");
    strcpy(p[4],"4-----------------------Salir.\n");

    return 5;
}

void MostrarMenuPrincipal(int fil,int col, char p[fil][col],int v)
{
    int i = 0;

    while ( i < v)
    {
        puts(p[i]);
        i++;
    }
}

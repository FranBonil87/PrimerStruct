
    
#include <iostream>
#include <string.h>
#include <time.h>
#include <fstream>

/*
Las siguientes líneas son para poder hacer el borrado de pantalla, es multiplataforma.
*/

#ifdef __cplusplus__
  #include <cstdlib>
  #define CLEAR "cls"
#else
  #include <stdlib.h>
  #define CLEAR "clear"
#endif


using namespace std;

/*
Procedimiento para crear el tablero vacio, que iremos rellenando conforme acierte el usuario.
*/

void CrearTableroAciertos(string **m, int f, int c)
{

    for (int i=0; i<f; i++)
    {
        for (int j=0; j<c; j++)
        {
             m[i][j]=" ";     // De inicio, rellenamos esta matriz de espacios, y la iremos....
        }                     // ...rellenando despues con los caracteres que el jugador acierte.
    }

}

/*
Procedimiento para crear el tablero booleano con el que validaremos datos.
*/

void CrearTableroReferencia(bool **m, int f, int c)
{

    for (int i=0; i<f; i++)
    {
        for (int j=0; j<c; j++)
        {
             m[i][j]=false;
        }
    }

}

/*
Procedimiento para crear la matriz vacía que representa la memoria de la IA
*/

void CrearMemoriaIA(string **m, int f, int c)
{

    for (int i=0; i<f; i++)
    {
        for (int j=0; j<c; j++)
        {
             m[i][j]=" ";     // De inicio, rellenamos esta matriz de espacios, y la iremos....
        }                     // ...rellenando despues con las casillas que levante la IA.
    }

}

/*
Procedimiento para crear el tablero con parejas de caracteres al azar, es el tablero solución.
*/

void CrearTableroSolucion(string **m, int f, int c)
{
    srand(time(NULL));

    string cadena="@!?-*/%&$#~|=abcdefghijklmnopqrstuvxyz><:;¿.+^Ç€wº";  // Estos son los caracteres para rellenar la matriz.

    string CadenaParejas="";                // Esta es la cadena donde vamos a duplicar los caracteres...
                                            // .... para formar las parejas
    int azar= -578;
    int casillas=f*c;                       // Casillas es igual a multiplicar las filas por las columnas.
    int NumParejas=casillas/2;              // El número de parejas es igual al total de casillas entre dos.

    for(int k=0; k<NumParejas; k++)
    {
        CadenaParejas=CadenaParejas+cadena[k]+cadena[k];  // duplicamos cada caracter en esta cadena.
    }

    for (int i=0; i<f; i++)
    {
        for (int j=0; j<c; j++)
        {
             azar=rand()%CadenaParejas.length();    // seleccionamos al azar una posición de la cadena y la metemos en una variable.

             m[i][j]=CadenaParejas[azar];           // asignamos el valor de la casilla de la matriz al de la variable.

             CadenaParejas.erase(azar,1);           // borramos el carácter para asegurarnos que no repita más de dos veces.
        }
    }

}

/*
Procedimiento para mostrar por pantalla los tableros.
*/

void MostrarTablero(string **m, int f, int c, int z)
{
    string referenciaTableroFilas="0123456789";
    string referenciaTableroColumnas=" 0123456789";
    int k=0;
    int h=0;
    int r=0;

    if(z==1)
    {
        while(k<=c)   // Aquí lo que hago es imprimir una linea antes de mi bucle principal.
            {             // Va a ser el indice de las columnas.
                cout <<"_"<<referenciaTableroColumnas[k]<<"_"<<"|";

                k++;
            }
            cout << endl;

            for (int i=0; i<f; i++)
            {
                cout << "_"<<referenciaTableroFilas[i]<<"_"<<"|";  // Indice de las filas del tablero.

                for (int j=0; j<c; j++)
                {
                    cout <<"_" << m[i][j]<<"_"<<"|";
                }
                cout << endl;

            }

    }

    if(z>1)
    {
        for (int i=0; i<f; i++)
            {

                while(r<z)
                {

                   for (int j=0; j<c; j++)
                     {
                        cout <<" "<<" ";

                        h=0;

                        while(h<z)
                        {
                            cout<<m[i][j];

                            h++;

                        }
                        cout<<" "<<" "<<"|";

                      }
                       cout<<endl;

                       r++;
                     }

                     r=0;

                }


    }


}



/*
Procedimiento para los tiempos.
*/

void sleepcp(int milliseconds) // Portable, multiplataforma.
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

/*
Este es mi programa principal
*/

int main(void)
{
    srand (time(NULL));
    string **tableroSolucion;                    // Este tablero va a contener la solucion.
    string **tableroAciertos;                    // Este tablero se va a ir rellenando con los aciertos, se inicializa vacío.
    bool **tableroReferencia;                    // Matriz de booleanos para validar datos.
    string **memoriaIA;                          // Matriz memoria de la IA
    int filas, cols, casillas;                   // Variables para construir los tableros.
    int filaUsuarioUno, colUsuarioUno;           // Aquí almaceno la primera coordenada elegida.
    int filaUsuarioDos, colUsuarioDos;           // Aquí almaceno la segunda coordenada.
    int filaIAUno, colIAUno;                     // La primera coordenada que elige la IA.
    int filaIADos, colIADos;                     // La segunda coordenada que elige la IA.
    int numAciertos, aciertosUsuario, aciertosIA;// Variables para los aciertos.
    int maxIntentos;                             // El número máximo de intentos del que dispondremos, y los intentos que nos quedan.
    int dificultad;                              // La dificultad del juego.
    int tiempoVerCasillas;                       // El tiempo que vamos a mostrar el tablero solucion si el usuario falla.
    int modoJuego;                               // Para seleccionar solitario o contra la IA.
    int turno;                                   // Variable para controlar los turnos.
    bool primeraCasilla, segundaCasilla;         // Variables de control del tablero referencia.
    float tiempoDeJuego=0;                       // Variable para mostrar el tiempo de juego.
    string nick;                                 // el nick del jugador.
    bool LoTengoEnMemoria=false;                 // variable centilena de la memoria de la IA.
    bool SeleccionAnticipadaIA=false;            // otra variable centinela de la IA.
    int FilaAnticipadaIA=0;                      // si coordenada dos contiene algo que ya tiene en memoria la IA.....
    int ColAnticipadaIA=0;                       // si coordenada dos contiene algo que ya tiene en memoria la IA.....
    int FilaAnticipadaIA2=0;
    int ColAnticipadaIA2=0;
    int filaLotiene=0;
    int colLotiene=0;
    int zoom=0;

    filas=0;
    cols=0;
    casillas=0;
    filaUsuarioUno=0;
    colUsuarioUno=0;
    filaUsuarioDos=0;
    colUsuarioDos=0;
    filaIAUno=0;
    colIAUno=0;
    filaIADos=0;
    colIADos=0;
    numAciertos=0;
    aciertosUsuario=0;
    aciertosIA=0;
    maxIntentos=0;
    dificultad=0;
    tiempoVerCasillas=0;
    modoJuego=0;
    turno=0;


    cout << "Bienvenid@, vamos a jugar al memorion." << endl <<endl;

    cout << "Tienes que encontrar parejas que coincidan en el tablero." << endl <<endl;

    cout << "Si fallas, se mostrara por pantalla la solucion para que memorices todo lo que puedas" << endl<<endl;

    cout << "El tiempo de ver la solucion varia en funcion de la dificultad que elijas" << endl<< endl;

    cout << "Introduce tu nick : ";

    cin >> nick;

    cout<<endl<<endl;

    cout << "Selecciona el tamanio del tablero, que sea un numero par, para que cuadren las parejas. "<< endl << endl;

     /*
       Validación de datos.
     */

    do                                      // Repetir todo esto...
    {

        cout << "Cuantas filas quieres? ";

        cin >> filas;

        cout << "Cuantas columnas quieres ? ";

        cin >> cols;

        casillas=filas*cols;

        cout << endl<<endl;

        if(filas%2!=0||cols%2!=0||filas<0||cols<0||filas>10||cols>10)  // Trato de que el usuario meta valores para generar una matriz ->
        // ->con un número de casillas par, para cuadrar todas las parejas, las filas y columnas no pueden ser mayores que 10.
        {
            cout << "Valores no validos :/" << endl<<endl;
        }


        if(casillas>100)    // El máximo de caracteres es de 50, como son parejas, 100 casillas en total.
        {
            cout << "No hay parejas para tanto tablero e_e" << endl<<endl;

            cout << "El maximo de casillas es 100" << endl<<endl;
        }

        if(filas>10||cols>10)
        {
            cout << "Las filas o las columnas no pueden ser mayores que 10" << endl<<endl;
        }

    }while(filas*cols%2!=0 || casillas>100);  //... mientras no ocurran estas condiciones.

    system(CLEAR);       // Limpieza de pantalla.


    /*
    Reservando memoria para crear el tablero con la solucion.
    */

    tableroSolucion = new string *[filas];

    for (int i=0; i < filas; i++)
    {
        tableroSolucion[i] = new string[cols];

    }

    /*
    Reservando memoria para crear el tablero vacío con el que va a jugar el usuario.
    */

    tableroAciertos = new string *[filas];

    for (int j=0; j < filas; j++)
    {
        tableroAciertos[j] = new string[cols];

    }

    /*
    Reservando memoria para crear el tablero de referencia.
    */

    tableroReferencia = new bool *[filas];

    for (int g=0; g < filas; g++)
    {
        tableroReferencia[g] = new bool[cols];

    }

    /*
    Llamamos a los procedimientos para crear las matrices.
    */


        CrearTableroSolucion(tableroSolucion,filas,cols);
        CrearTableroAciertos(tableroAciertos,filas,cols);
        CrearTableroReferencia(tableroReferencia,filas,cols);


     /*
       Validación del zoom.
     */



    do
    {
        cout<<"Selecciona el zoom del tablero, como minimo 1, como maximo 3: ";

        cin >> zoom;

    }while(zoom<=0||modoJuego>3);

    cout<<endl<<endl;


     /*
       Validación de la dificultad.
     */



    cout << "Quieres jugar sol@, o contra la IA?:" << endl<<endl;

    /*
    Validación de datos del modo de juego.
    */

    do
    {
        cout << "Escribe 1 para modo solitario u 2 para competir contra la IA: ";

        cin >> modoJuego;

    }while(modoJuego<=0||modoJuego>2);

    cout<<endl<<endl;

    /*
    MODO DE JUEGO SOLITARIO
    */

    if(modoJuego==1)
    {

    do  // Repetir
    {
        cout << "Selecciona del 1 al 3 la dificultad del juego" << endl << endl;

        cout << "Siendo 1 facil, y 3 dificil: ";

        cin >> dificultad;

        cout << endl;

    }while(dificultad<=0||dificultad>3);  // Mientras que la dificultad sea menor que cero o mayor que 3.


    /*
       En funcion de la dificultad elegida, modificamos el número de intentos del que dispone el jugador
       y el tiempo que se muestra la solucion por pantalla.
    */


    switch(dificultad)       // según la dificultad.
    {
        case 1: maxIntentos=casillas;        // En dificultad 1 (facil) hay tantos intentos como casillas
                tiempoVerCasillas=7000;      // El tiempo de mostrar las casillas es de 7 segundos
                break;

        case 2: maxIntentos=casillas/2;      // En dificultad 2 hay tantos intentos como parejas
                tiempoVerCasillas=5000;      // 5 segundos para ver las casillas
                break;

        case 3: maxIntentos=casillas/4;      // En dificultad 3 (dificil) los intentos son las casillas entre 4
                tiempoVerCasillas=3000;      // solo se muetran las casillas al fallar durante 3 segundos
                break;

    }

    system(CLEAR);    // Limpieza de pantalla.


        cout<<endl<<endl;
        MostrarTablero(tableroAciertos,filas,cols,zoom);

    /*
     Comienza el juego para el usuario.
    */


    cout << endl << endl;

    cout << "Empieza el juego" << endl<<endl;


    /*
     El siguiente bucle es el juego en sí, tratar de acertar parejas.
    */

    clock_t t;
    t = clock();                                 // Funcion de reloj para los tiempos.


    while(numAciertos<casillas)  // Mientras el número de aciertos sea menor que el de las casillas del tablero...
    {                            // Pedir coordenadas al usuario y ver si coincide con el tablero de soluciones.


         do                      // Validación de datos.
         {

             do      // Validacón de datos.
             {
                cout<< "Tienes " << maxIntentos << " intentos "<<endl<<endl;

                cout << "Elige una fila para la primera coordenada: ";

                cin >> filaUsuarioUno;

                cout << "Elige una columna para la primera coordenada: ";

                cin >> colUsuarioUno;

             }while(filaUsuarioUno<0||filaUsuarioUno>=filas||colUsuarioUno<0||colUsuarioUno>=cols||tableroReferencia[filaUsuarioUno][colUsuarioUno]==true);

             do      // Validación de datos.
             {

                cout << endl;

                cout << "Elige una fila para la segunda coordenada: ";

                cin >> filaUsuarioDos;

                cout << "Elige una columna para la segunda coordenada: ";

                cin >> colUsuarioDos;

                 /*
                    Procuramos que las coordenadas no sean iguales.
                  */

                if(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos)
                {
                    cout << "La primera coordenada y la segunda no pueden coincidir, no tiene sentido"<< endl;
                }


             }while((filaUsuarioDos<0||filaUsuarioDos>=filas)||(colUsuarioDos<0||colUsuarioDos>=cols)||tableroReferencia[filaUsuarioDos][colUsuarioDos]==true||(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos));


             primeraCasilla=tableroReferencia[filaUsuarioUno][colUsuarioUno];   // Asigno el valor de la casilla de la matriz a la variable.

             segundaCasilla=tableroReferencia[filaUsuarioDos][colUsuarioDos];   // Asigno el valor de la casilla de la matriz a la variable.



            }while(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos);


            string caracterUno=tableroSolucion[filaUsuarioUno][colUsuarioUno];  //Creo una variable para almacenar la coordenada 1.

            string caracterDos=tableroSolucion[filaUsuarioDos][colUsuarioDos];  //Creo una variable para almacenar la coordenada 2.


        if(caracterUno==caracterDos) //Si coinciden los caracteres en las coordenadas que incidamos.....
        {
                                    // ...muestro por pantalla el tablero con las parejas encontradas y pongo las mismas...
                                    // ... casillas en la tabla referencia a true.

            system(CLEAR);          // Limpieza de pantalla.

            tableroAciertos[filaUsuarioUno][colUsuarioUno]=caracterUno;

            tableroReferencia[filaUsuarioUno][colUsuarioUno]=true;

            tableroAciertos[filaUsuarioDos][colUsuarioDos]=caracterDos;

            tableroReferencia[filaUsuarioDos][colUsuarioDos]=true;

            MostrarTablero(tableroAciertos,filas,cols,zoom);

            cout << endl<<endl;

            cout << "Has acertado !!"<< endl<<endl;

            cout << endl;

            numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.


        }else
            {                // Si no acertamos.

                if(maxIntentos==0)  // si agotamos el número de fallos.
                {

                    system(CLEAR);  // Limpieza de pantalla.

                    cout <<"Has agotado el numero de intentos :/ , reinicia y vuelve a probar" << endl <<endl;

                    cout <<"Esta era la solucion :" <<endl<< endl;

                    MostrarTablero(tableroSolucion,filas,cols,zoom);  // mostramos en pantalla la solucion ....

                    cout << endl;

                    break;                                       //...Salimos del bucle y finalizamos el juego.

                }else                      // Si hemos fallado, pero nos quedan intentos, seguimos probando.
                     {
                         cout<< "Has fallado :S" << endl<< endl;


                         tableroAciertos[filaUsuarioUno][colUsuarioUno]=caracterUno;
                         tableroAciertos[filaUsuarioDos][colUsuarioDos]=caracterDos;

                         MostrarTablero(tableroAciertos,filas,cols,zoom);  // Muestro la matriz del usuario con las casillas que acaba de levantar durante un tiempo.

                         sleepcp(tiempoVerCasillas);              // Llamo a la función que detiene el programa durante X segundos.

                         system(CLEAR);                           // Limpiamos la pantalla para que no se siga mostrando el tablero solución.

                         tableroAciertos[filaUsuarioUno][colUsuarioUno]=" ";
                         tableroAciertos[filaUsuarioDos][colUsuarioDos]=" ";



                         MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                         cout << endl<< endl;

                         cout<< "Vuelve a probar =D"<< endl<<endl;

                         maxIntentos--;    // Los intentos que quedan.

                         cout<< "Te quedan " << maxIntentos << " intentos "<<endl<<endl;
                     }

            }

    } // Fin del mientras.

        t = clock() - t;

        double tiempoPasado=((float)t)/CLOCKS_PER_SEC;                          // Calcula el tiempo que ha pasado

        tiempoDeJuego=tiempoPasado;

    /*
     Si el usuario completa el tablero.
    */

    if(numAciertos==casillas)
    {
        cout << "Enhorabuena o/ has completado el tablero =D"<<endl << endl;  // Se le felicita.
    }

    }  // fin modo solitario.



    /*
    JUEGO CONTRA LA IA
    */

    if(modoJuego==2)
    {

    system(CLEAR);    // Limpieza de pantalla.

    /*
    Reservando memoria para crear LA MEMORIA DE LA IA
    */

    memoriaIA = new string *[filas];

    for (int m=0; m < filas; m++)
    {
        memoriaIA[m] = new string[cols];

    }

    do  // Repetir
    {
        cout << "Selecciona del 1 al 3 la dificultad del juego" << endl << endl;

        cout << "Siendo 1 facil, y 3 dificil: ";

        cin >> dificultad;

        cout << endl;

    }while(dificultad<=0||dificultad>3);  // Mientras que la dificultad sea menor que cero o mayor que 3.

    /*
       En funcion de la dificultad elegida, modificamos tiempo que se muestra la solucion por pantalla y lo
       inteligente (o no) que es la IA.
    */


    switch(dificultad)       // según la dificultad.
    {
        case 1: tiempoVerCasillas=7000;      // El tiempo de mostrar las casillas es de 7 segundos.
                break;

        case 2: tiempoVerCasillas=5000;      // 5 segundos para ver las casillas.
                break;

        case 3: tiempoVerCasillas=3000;      // solo se muetran las casillas al fallar durante 3 segundos.
                break;

    }


    CrearMemoriaIA(memoriaIA,filas,cols);   // Creamos la memoria de la IA mediante el procedimiento


    cout<<endl<<endl;
    MostrarTablero(tableroAciertos,filas,cols,zoom);


    /*
     COMIENZA EL JUEGO PARA EL USUARIO Y LA IA
    */


    cout << endl << endl;

    cout << "Empieza el juego" << endl<<endl;

    clock_t t;
    t = clock();                                 // Funcion de reloj para los tiempos.


    /*
     El siguiente bucle es el juego en sí, tratar de acertar más parejas que la IA.
    */

    while(numAciertos<(casillas-2))  // Mientras los aciertos totales no superen el número de casillas.
    {
        turno=1;   // Reinicio el turno cuando acaba el de la IA

        if(turno==1)  // TURNO DEL USUARIO
        {
            cout << "Tu turno"<< endl<<endl;

            cout <<"Tienes "<<aciertosUsuario<<" puntos, la IA tiene "<<aciertosIA<<" puntos"<<endl<<endl;


         do          // Validación de datos.
           {


             do      // Validacón de datos.
               {

                 cout << "Elige una fila para la primera coordenada: ";

                 cin >> filaUsuarioUno;

                 cout << "Elige una columna para la primera coordenada: ";

                 cin >> colUsuarioUno;

               }while(filaUsuarioUno<0||filaUsuarioUno>=filas||colUsuarioUno<0||colUsuarioUno>=cols||tableroReferencia[filaUsuarioUno][colUsuarioUno]==true);

             do      // Validación de datos.
                {

                   cout << endl;

                   cout << "Elige una fila para la segunda coordenada: ";

                   cin >> filaUsuarioDos;

                   cout << "Elige una columna para la segunda coordenada: ";

                   cin >> colUsuarioDos;

                  /*
                    Procuramos que las coordenadas no sean iguales.
                  */

                  if(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos)
                  {
                    cout << "La primera coordenada y la segunda no pueden coincidir, no tiene sentido"<< endl;
                  }

                }while((filaUsuarioDos<0||filaUsuarioDos>=filas)||(colUsuarioDos<0||colUsuarioDos>=cols)||tableroReferencia[filaUsuarioDos][colUsuarioDos]==true||(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos));


                primeraCasilla=tableroReferencia[filaUsuarioUno][colUsuarioUno];   // Asigno el valor de la casilla de la matriz a la variable.

                segundaCasilla=tableroReferencia[filaUsuarioDos][colUsuarioDos];   // Asigno el valor de la casilla de la matriz a la variable.




            }while(filaUsuarioUno==filaUsuarioDos&&colUsuarioUno==colUsuarioDos);


        string caracterUno=tableroSolucion[filaUsuarioUno][colUsuarioUno];  //Creo una variable para almacenar la coordenada 1.

        string caracterDos=tableroSolucion[filaUsuarioDos][colUsuarioDos];  //Creo una variable para almacenar la coordenada 2.


        if(caracterUno==caracterDos) //Si coinciden los caracteres en las coordenadas que incidamos.....
        {
                                    // ...muestro por pantalla el tablero con las parejas encontradas.

            system(CLEAR);          // Limpieza de pantalla.

            tableroAciertos[filaUsuarioUno][colUsuarioUno]=caracterUno;

            tableroReferencia[filaUsuarioUno][colUsuarioUno]=true;

            tableroAciertos[filaUsuarioDos][colUsuarioDos]=caracterDos;

            tableroReferencia[filaUsuarioDos][colUsuarioDos]=true;

            MostrarTablero(tableroAciertos,filas,cols,zoom);

            cout << endl<<endl;

            cout << "Has acertado !!"<< endl<<endl;

            cout << endl;

            numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

            aciertosUsuario+=2;     // aumentamos el contador de aciertos del usuario.


        }else
           {
                cout<< "Has fallado :S" << endl<< endl;


                tableroAciertos[filaUsuarioUno][colUsuarioUno]=caracterUno;
                tableroAciertos[filaUsuarioDos][colUsuarioDos]=caracterDos;

                MostrarTablero(tableroAciertos,filas,cols,zoom);  // Muestro la matriz del usuario con las casillas que acaba de levantar durante un tiempo.

                sleepcp(tiempoVerCasillas);              // Llamo a la función que detiene el programa durante X segundos.

                system(CLEAR);                           // Limpiamos la pantalla para que no se siga mostrando el tablero solución.

                tableroAciertos[filaUsuarioUno][colUsuarioUno]=" ";
                tableroAciertos[filaUsuarioDos][colUsuarioDos]=" ";



                MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                cout << endl<< endl;

        }
                                 // Si hemos fallado, pero nos quedan intentos, seguimos probando.


        turno++;  // el turno avanza

        } // FIN TURNO DEL USUARIO

        /*
        TURNO DE LA IA
        */

        if(turno==2)   // El turno 2 es el de la IA
        {
         switch(dificultad)       // según la dificultad.
         {
          case 1:  // dificultad fácil, la IA no tiene memoria.
            {

            if(numAciertos<(casillas-2))  // Mientras el número de aciertos sea menor que el de las casillas el juego continua.
            {
                cout << "Turno de la IA"<< endl<<endl;

                sleepcp(2000);

                do      // Mecanismo para el comportamiento de la IA
                  {
                    filaIAUno=rand()%filas;
                    colIAUno=rand()%cols;

                    filaIADos=rand()%filas;
                    colIADos=rand()%cols;


                    primeraCasilla=tableroReferencia[filaIAUno][colIAUno];   // Asigno el valor de la casilla de la matriz a la variable.

                    segundaCasilla=tableroReferencia[filaIADos][colIADos];   // Asigno el valor de la casilla de la matriz a la variable.



                  }while((filaIAUno==filaIADos&&colIAUno==colIADos)||primeraCasilla==true||segundaCasilla==true);

                   cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                   string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                   string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.


                  if(caracterIAUno==caracterIADos) //Si coinciden los caracteres en las coordenadas que incidamos.....
                  {
                                             // ...muestro por pantalla el tablero con las parejas encontradas.

                    tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                    tableroReferencia[filaIAUno][colIAUno]=true;

                    tableroAciertos[filaIADos][colIADos]=caracterIADos;

                    tableroReferencia[filaIADos][colIADos]=true;

                    MostrarTablero(tableroAciertos,filas,cols,zoom);

                    cout << endl<<endl;

                    cout << "La IA ha acertado !!"<< endl<<endl;

                    cout << endl;

                    numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                    aciertosIA+=2;          // subo el contador de aciertos de la IA

                    sleepcp(2000);


                  }else

                       {
                         cout<< "La IA ha misseao :S" << endl<< endl;

                         MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                         cout << endl<< endl;

                         sleepcp(2000);

                       }

             } // Fin del if de las casillas

            } // fin case 1

            break;

            case 2:  // dificultad media, la IA tiene un 50% de probabilidad de consultar memoria.
            {
                if(numAciertos<(casillas-2))  // Mientras el número de aciertos sea menor que el de las casillas el juego continua.
                {
                    cout << "Turno de la IA"<< endl<<endl;

                    int soylistaOno=0;

                    soylistaOno=rand()%1;

                    switch(soylistaOno)
                    {
                     case 0:  // la IA carece de memoria, salvo para las parejas que ya hayan salido.
                        {
                            sleepcp(2000);

                         do      // Mecanismo para el comportamiento de la IA
                          {
                            filaIAUno=rand()%filas;
                            colIAUno=rand()%cols;

                            filaIADos=rand()%filas;
                            colIADos=rand()%cols;


                            primeraCasilla=tableroReferencia[filaIAUno][colIAUno];   // Asigno el valor de la casilla de la matriz a la variable.

                            segundaCasilla=tableroReferencia[filaIADos][colIADos];   // Asigno el valor de la casilla de la matriz a la variable.



                          }while((filaIAUno==filaIADos&&colIAUno==colIADos)||primeraCasilla==true||segundaCasilla==true);

                           cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                           string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                           string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.


                          if(caracterIAUno==caracterIADos) //Si coinciden los caracteres en las coordenadas que incidamos.....
                          {
                                             // ...muestro por pantalla el tablero con las parejas encontradas.

                            tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                            tableroReferencia[filaIAUno][colIAUno]=true;

                            tableroAciertos[filaIADos][colIADos]=caracterIADos;

                            tableroReferencia[filaIADos][colIADos]=true;

                            MostrarTablero(tableroAciertos,filas,cols,zoom);

                            cout << endl<<endl;

                            cout << "La IA ha acertado !!"<< endl<<endl;

                            cout << endl;

                            numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                            aciertosIA+=2;          // subo el contador de aciertos de la IA

                            sleepcp(2000);


                          }else

                               {
                                  cout<< "La IA ha misseao :S" << endl<< endl;

                                  MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                                  cout << endl<< endl;

                                  sleepcp(2000);

                               }



                          } // fin case 1 con la IA sin memoria

                            break;

                     case 1:  // la IA es lista y memoriza todo
                         {

                            for(int q=0; q<filas; q++)
                            {
                              for(int s=0; s<cols; s++)
                               {
                                 if(tableroReferencia[q][s]==true)
                                   {
                                     memoriaIA[q][s]=tableroSolucion[q][s];
                                   }
                               }
                            }

                            bool tiradaNormal=true;


                         while(tiradaNormal==true)
                         {

                          if(SeleccionAnticipadaIA==true&&tableroReferencia[FilaAnticipadaIA][ColAnticipadaIA]==false&&tableroReferencia[FilaAnticipadaIA2][ColAnticipadaIA2]==false)
                          {
                              filaIAUno=FilaAnticipadaIA;
                              colIAUno=ColAnticipadaIA;

                              filaIADos=FilaAnticipadaIA2;
                              colIADos=ColAnticipadaIA2;

                              string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                              string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.

                              cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                              tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                              tableroReferencia[filaIAUno][colIAUno]=true;

                              tableroAciertos[filaIADos][colIADos]=caracterIADos;

                              tableroReferencia[filaIADos][colIADos]=true;

                              MostrarTablero(tableroAciertos,filas,cols,zoom);

                              cout << endl<<endl;

                              cout << "La IA ha acertado !!"<< endl<<endl;

                              cout << endl;

                              numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                              aciertosIA+=2;          // subo el contador de aciertos de la IA

                              SeleccionAnticipadaIA=false;

                              sleepcp(2000);

                              break;



                          }

                          else
                          {

                            do
                            {
                                filaIAUno=rand()%filas;
                                colIAUno=rand()%cols;

                            }while(tableroReferencia[filaIAUno][colIAUno]==true||memoriaIA[filaIAUno][colIAUno]!=" ");

                            memoriaIA[filaIAUno][colIAUno]=tableroSolucion[filaIAUno][colIAUno];


                            for(int r=0; r<filas; r++)
                            {
                                for(int t=0; t<cols; t++)
                                {
                                    int resul=(filaIAUno-r)-(colIAUno-t);

                                    if(memoriaIA[filaIAUno][colIAUno]==memoriaIA[r][t]&&resul!=0&&tableroReferencia[r][t]==false)
                                    {
                                        filaLotiene=r;
                                        colLotiene=t;

                                        LoTengoEnMemoria=true;

                                    }

                                }

                            }



                           if(LoTengoEnMemoria==true)
                            {
                               filaIADos=filaLotiene;
                               colIADos=colLotiene;

                               memoriaIA[filaIADos][colIADos]=tableroSolucion[filaIADos][colIADos];

                            }else{
                                 do{
                                     filaIADos=rand()%filas;
                                     colIADos=rand()%cols;

                                   }while(tableroReferencia[filaIADos][colIADos]==true||(filaIADos==filaIAUno&&colIADos==colIAUno)||memoriaIA[filaIADos][colIADos]!=" ");

                                 }

                              LoTengoEnMemoria=false;

                              memoriaIA[filaIADos][colIADos]=tableroSolucion[filaIADos][colIADos];


                              for(int m=0; m<filas; m++)
                              {

                                for(int n=0; n<cols; n++)
                                 {
                                   int resul=(filaIADos-m)-(colIADos-n);

                                   if(memoriaIA[m][n]==memoriaIA[filaIADos][colIADos]&&resul!=0&&(tableroReferencia[m][n]==false&&tableroReferencia[filaIADos][colIADos]==false))
                                   {

                                       FilaAnticipadaIA=m;
                                       ColAnticipadaIA=n;

                                       FilaAnticipadaIA2=filaIADos;
                                       ColAnticipadaIA2=colIADos;

                                       SeleccionAnticipadaIA=true;

                                   }

                                }

                              }



                           }

                              cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                              string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                              string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.


                             if(caracterIAUno==caracterIADos) //Si coinciden los caracteres en las coordenadas que incidamos.....
                             {
                                             // ...muestro por pantalla el tablero con las parejas encontradas.

                               tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                               tableroReferencia[filaIAUno][colIAUno]=true;

                               tableroAciertos[filaIADos][colIADos]=caracterIADos;

                               tableroReferencia[filaIADos][colIADos]=true;

                               MostrarTablero(tableroAciertos,filas,cols,zoom);

                               cout << endl<<endl;

                               cout << "La IA ha acertado !!"<< endl<<endl;

                               cout << endl;

                               numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                               aciertosIA+=2;          // subo el contador de aciertos de la IA

                               sleepcp(2000);


                              }else

                                {

                                 cout<< "La IA ha misseao :S" << endl<< endl;

                                 MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                                 cout << endl<< endl;

                                 sleepcp(2000);

                                }

                                    tiradaNormal=false;

                                }


                              break;
                         }

                    }

                 } // fn del if de las casillas de la dificultad media

                } // fin case 2 dificultad media

                break;




            case 3:  // dificultad dificil, la IA memoriza TODO
            {

                for(int q=0; q<filas; q++)
                {
                    for(int s=0; s<cols; s++)
                    {
                        if(tableroReferencia[q][s]==true)
                        {
                            memoriaIA[q][s]=tableroSolucion[q][s];
                        }
                    }
                }



            if(numAciertos<(casillas-2))  // Mientras el número de aciertos sea menor que el de las casillas el juego continua.
            {
                cout << "Turno de la IA"<< endl<<endl;

                sleepcp(2000);

                bool tiradaNormal=true;


                while(tiradaNormal==true)
                {

                if(SeleccionAnticipadaIA==true&&tableroReferencia[FilaAnticipadaIA][ColAnticipadaIA]==false&&tableroReferencia[FilaAnticipadaIA2][ColAnticipadaIA2]==false)
                {
                    filaIAUno=FilaAnticipadaIA;
                    colIAUno=ColAnticipadaIA;

                    filaIADos=FilaAnticipadaIA2;
                    colIADos=ColAnticipadaIA2;

                    string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                    string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.

                    cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                    tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                    tableroReferencia[filaIAUno][colIAUno]=true;

                    tableroAciertos[filaIADos][colIADos]=caracterIADos;

                    tableroReferencia[filaIADos][colIADos]=true;

                    MostrarTablero(tableroAciertos,filas,cols,zoom);

                    cout << endl<<endl;

                    cout << "La IA ha acertado !!"<< endl<<endl;

                    cout << endl;

                    numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                    aciertosIA+=2;          // subo el contador de aciertos de la IA

                    SeleccionAnticipadaIA=false;

                    sleepcp(2000);

                    break;



                }

                else
                {

                  do
                  {
                      filaIAUno=rand()%filas;
                      colIAUno=rand()%cols;

                  }while(tableroReferencia[filaIAUno][colIAUno]==true||memoriaIA[filaIAUno][colIAUno]!=" ");

                  memoriaIA[filaIAUno][colIAUno]=tableroSolucion[filaIAUno][colIAUno];


                  for(int r=0; r<filas; r++)
                  {
                      for(int t=0; t<cols; t++)
                      {
                          int resul=(filaIAUno-r)-(colIAUno-t);

                          if(memoriaIA[filaIAUno][colIAUno]==memoriaIA[r][t]&&resul!=0&&tableroReferencia[r][t]==false)
                          {
                              filaLotiene=r;
                              colLotiene=t;

                              LoTengoEnMemoria=true;

                          }

                      }
                  }



                    if(LoTengoEnMemoria==true)
                      {
                          filaIADos=filaLotiene;
                          colIADos=colLotiene;

                          memoriaIA[filaIADos][colIADos]=tableroSolucion[filaIADos][colIADos];

                      }else{
                            do{
                                filaIADos=rand()%filas;
                                colIADos=rand()%cols;

                              }while(tableroReferencia[filaIADos][colIADos]==true||(filaIADos==filaIAUno&&colIADos==colIAUno)||memoriaIA[filaIADos][colIADos]!=" ");

                           }

                    LoTengoEnMemoria=false;

                    memoriaIA[filaIADos][colIADos]=tableroSolucion[filaIADos][colIADos];


                    for(int m=0; m<filas; m++)
                    {
                        for(int n=0; n<cols; n++)

                        {
                            int resul=(filaIADos-m)-(colIADos-n);

                            if(memoriaIA[m][n]==memoriaIA[filaIADos][colIADos]&&resul!=0&&(tableroReferencia[m][n]==false&&tableroReferencia[filaIADos][colIADos]==false))
                            {

                                FilaAnticipadaIA=m;
                                ColAnticipadaIA=n;

                                FilaAnticipadaIA2=filaIADos;
                                ColAnticipadaIA2=colIADos;

                               SeleccionAnticipadaIA=true;

                            }

                        }
                    }



                }

                   cout << "La IA ha elegido las casillas "<<filaIAUno<<" "<<colIAUno<<"  y  "<<filaIADos<<" "<<colIADos<<endl<<endl;

                   string caracterIAUno=tableroSolucion[filaIAUno][colIAUno];  //Creo una variable para almacenar la coordenada 1.

                   string caracterIADos=tableroSolucion[filaIADos][colIADos];  //Creo una variable para almacenar la coordenada 2.


                  if(caracterIAUno==caracterIADos) //Si coinciden los caracteres en las coordenadas que incidamos.....
                  {
                                             // ...muestro por pantalla el tablero con las parejas encontradas.

                    tableroAciertos[filaIAUno][colIAUno]=caracterIAUno;

                    tableroReferencia[filaIAUno][colIAUno]=true;

                    tableroAciertos[filaIADos][colIADos]=caracterIADos;

                    tableroReferencia[filaIADos][colIADos]=true;

                    MostrarTablero(tableroAciertos,filas,cols,zoom);

                    cout << endl<<endl;

                    cout << "La IA ha acertado !!"<< endl<<endl;

                    cout << endl;

                    numAciertos+=2;         // aumentamos el contador de aciertos en dos, porque son dos casillas las que acertamos.

                    aciertosIA+=2;          // subo el contador de aciertos de la IA

                    sleepcp(2000);


                  }else

                       {

                         cout<< "La IA ha misseao :S" << endl<< endl;

                         MostrarTablero(tableroAciertos,filas,cols,zoom);   // Vuelvo a imprimir el tablero del usuario.

                         cout << endl<< endl;

                         sleepcp(2000);

                       }

                tiradaNormal=false;

                }


              } //Fin del "SI.." de las casillas

             } // fin case 3

            break;


         } // Fin del switch de la dificultad de la IA

        } // FIN TURNO IA


    }  // FIN BUCLE PRINCIPAL DEL JUEGO CONTRA LA IA


        t = clock() - t;

        double tiempoPasado=((float)t)/CLOCKS_PER_SEC;                          // Calcula el tiempo que ha pasado

        tiempoDeJuego=tiempoPasado;

    cout<<endl;

    MostrarTablero(tableroSolucion, filas, cols,zoom);

    cout << endl<<endl;

    cout << "La IA ha conseguido "<<aciertosIA<< " puntos"<< endl << endl;                    // Puntuación de la IA.

    cout << "Tu puntuacion es la siguiente:  "<< aciertosUsuario<< " puntos"<< endl << endl;   // Puntuación del usuario.


    cout<<endl<<endl;



    if(aciertosIA==aciertosUsuario)
    {
        cout << "La IA y tu habeis empatado" << endl << endl;

    }else
         if(aciertosIA>aciertosUsuario)
         {
             cout << "La IA te ha ganado e_e"<<endl<<endl;

         }else
             {
                 cout << "Enhorabuena, has ganado a la IA ^_^ !! "<< endl<<endl;
             }

         /*
          Borramos la matriz "memoria de la ia"
         */


        for(int i = 0; i < filas; i++)
           {
            delete (memoriaIA[i]);
           }

        delete memoriaIA;


    }  // FIN MODO JUEGO CONTRA LA IA

    cout <<endl;

    if(modoJuego==1)
    {
        system(CLEAR);

        MostrarTablero(tableroSolucion, filas, cols,zoom);

    }

    cout<<endl;


    cout << "Han pasado "<< tiempoDeJuego << " segundos. "<< endl << endl;   // Muestro el tiempo que ha pasado.

    string lin;                    // variable para meter cada linea del fichero

    ofstream fichOut( "records.txt" ); //  escritura en un fichero
                                 // si ya existe, lo machaca, cuidado

    if (fichOut.is_open())
    {
        fichOut << nick << " , Estas son tus estdisticas de juego.  "<<"Tiempo : "<<tiempoDeJuego<<" Numero de casillas: "<<casillas<<" Dificultad: "<<dificultad<<endl;

    }

    ifstream fichIn("records.txt");      // apertura del fichero, que esté en la carpeta raiz


    if(fichIn.is_open())
    {
        getline(fichIn, lin);           // leemos la primera linea
        while(!fichIn.eof())            // mientras no llegue al final
        {
            cout << lin << endl;      // mostramos la anterior
            getline(fichIn,lin);        // y leemos la siguiente
        }
    }

    cout<<endl<<endl;


    cout << "El juego ha finalizado, gracias por jugar :D" << endl;


    /*
     Borramos las matrices de la memoria.
    */


    for(int v = 0; v < filas; v++)
    {
        delete (tableroSolucion[v]);
        delete (tableroAciertos[v]);
        delete (tableroReferencia[v]);
        delete (memoriaIA[v]);

    }

    delete tableroSolucion;
    delete tableroAciertos;
    delete tableroReferencia;
    delete memoriaIA;

    return 0;
}

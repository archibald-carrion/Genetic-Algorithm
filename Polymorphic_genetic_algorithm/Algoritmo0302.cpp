#include "Algoritmo0302.h"
#include "Poblacion.h"
#include <stdlib.h> // biblioteca random
#include <time.h>

/**
 *  @brief El metodo crearPoblacionInicial permite crear una poblacion inicial de 50 individuos random dados por el ambiente
 *  @return El metodo devuelve un puntero hacia una instencia de Poblacion, la cual es la poblacion que acaba de crear
 **/
Poblacion *Algoritmo0302::crearPoblacionInicial()
{
    Poblacion *poblacionInicial = new Poblacion();
    srand(time(NULL));
    for (int counter = 0; counter < 50; ++counter)
    {
        Criatura *criatura = (*ambiente).getCriatura();
        (*poblacionInicial).add(criatura); // la poblacion inicial es de 50 individuos randoms
        // poblacion[counter] = criatura;
    }
    (*poblacionInicial).add(0);
    return poblacionInicial;
}

/**
 *  @brief El metodo evolucionar es el metodo principal de la clase, permite hacer evolucionar una poblacion de Criaturas
 *  @param unaPoblacion unaPoblacion es el unico parametro del metodo, es la poblacion inicial con la cual se debe evolucionar
 *  @return El metodo devuelve una Poblacion, la cual es la poblacion "final" del algortimo una vez que se termino la evolucion
 **/
Poblacion *Algoritmo0302::evolucionar(Poblacion *unaPoblacion)
{
    Criatura **poblacion;
    unaPoblacion->begin();
    Criatura *criatura = unaPoblacion->next();
    int counter = 0;

    while (criatura != 0)
    {
        poblacion[counter] = criatura->clonar(); // se llena la poblacion con clones de la poblacionInicial
        ++counter;
        criatura = unaPoblacion->next();
    }
    poblacion[counter] = 0;

    /*  dejamos de evolucionar la poblacion cuando haya pasado 100 generaciones o cuando 25% de la poblacion tiene un fitness igual a superior al mejor fitness de la
    primera generación para eso hay que encontrar el mejor fitness de la generacion inicial y guardarlo en fitnessLimite    */

    counter = 0;
    double fitnessLimite;
    criatura = poblacion[counter];
    fitnessLimite = ambiente->fitness(criatura);
    while (criatura != 0)
    {
        if (ambiente->fitness(criatura) > fitnessLimite)
        {
            fitnessLimite = ambiente->fitness(criatura);
        }
        ++counter;
        criatura = poblacion[counter];
    }

    int cantidadMaximaGeneracion = 100; // pasado esta cantidad de generacion no se evoluciona mas
    int condicion25 = 0;
    condicion25 = verificarCondicion25(poblacion, fitnessLimite);

    //#####################################################
    //-----------------WHILE-GENERACION--------------------
    //#####################################################
    while (condicion25 == 0 && cantidadMaximaGeneracion != 0)
    {
        for (int i = 0; i < poblacionSize(poblacion); ++i)
        {
            delete poblacion[i]; // para no tener fugas de memoria
        }

        Criatura **poblacionHija = nuevaGeneracion(poblacion);

        for (int i = 0; i < poblacionSize(poblacionHija); ++i)
        {
            poblacion[i] = poblacionHija[i]; // se llena la poblacion con los elementos de la nueva generacion
            delete poblacionHija[i];
        }
        delete poblacionHija;

        --cantidadMaximaGeneracion;
        condicion25 = verificarCondicion25(poblacion, fitnessLimite);
    }
    
    Poblacion *poblacionFinal = new Poblacion();
    for (int i = 0; i < poblacionSize(poblacion); ++i)
    {
        poblacionFinal->add(poblacion[i]);
    }
    poblacionFinal->add(0);

   // Poblacion *poblacionInicial = new Poblacion();
   // srand(time(NULL));
    //for (int counter = 0; counter < 50; ++counter)
    //{
        //Criatura *criatura = (*ambiente).getCriatura();
        //(*poblacionInicial).add(criatura); // la poblacion inicial es de 50 individuos randoms
        // poblacion[counter] = criatura;
    //}
   // (*poblacionInicial).add(0);
    return poblacionFinal;
    
    // hay que crear una Poblacion con el contenido de poblacion
}

/**
 *  @brief El metodo verificarCondicion25 verifica si la poblacion dada cumple con la condicion de tener por lo menos  25% de la poblacion con un fitness superior o igual al fitnessLimite
 *  @param poblacionEstudiada poblacionEstudiada es un parametro de tipo Criatura** que representa la poblacion que se debe estudiar
 *  @param fitness fitness es un double que representa el fitnessLimite al cual se debe comparar el fitness de cada elemento de la poblacion
 *  @return El metodo devuelve un int, 0 si la poblacion no cumple con la condición, 1 si la poblacion cumple con la condición
 **/
int Algoritmo0302::verificarCondicion25(Criatura **poblacionEstudiada, double fitness)
{
    int poblacionSize = 0;
    int counter = 0;
    int cantidadCriaturasValidas = 0;
    int condicionValida = 0;
    Criatura *unaCriatura = poblacionEstudiada[0];
    while (unaCriatura != 0)
    {
        ++poblacionSize;
        unaCriatura = poblacionEstudiada[counter];
        ++counter;
        if (this->ambiente->fitness(unaCriatura) >= fitness)
        {
            ++cantidadCriaturasValidas;
        }
    }
    int proporcion25 = (25 * poblacionSize) / 100; // para saber cual el 25% de la poblacion
    if (cantidadCriaturasValidas >= proporcion25)
    {
        condicionValida = 1;
    }
    return condicionValida;
}


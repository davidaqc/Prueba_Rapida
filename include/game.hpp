#ifndef GAME_H
#define GAME_H

#include <mutex>

using namespace std;

/**
 * @note Mensajes utilizados por los distintos threads y las llaves para accesarlos.
 */
/**
  * Variable utilizada para verificar si se envían correctamente los datos
  */
static mutex access_send;


#endif
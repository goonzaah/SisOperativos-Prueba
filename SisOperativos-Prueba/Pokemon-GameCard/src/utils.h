/*
 * conexiones.h
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

typedef enum
{
	NEW_POKEMON = 1,
	CATCH_POKEMON = 2,
	APPEREAD_POKEMON = 3
}op_code;

typedef struct { 
    uint32_t id;
    uint32_t nombre_length;
	char* nombre;
    uint32_t posicion[2];
    uint32_t cantidad;    
} t_new_pokemon;

typedef struct {
    uint32_t id;
    uint32_t nombre_length;
	char* nombre;
    uint32_t posicion[2];
} t_catch_pokemon;



typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

//Generals
int crear_conexion(char* ip, char* puerto);
void recibir_mensaje(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);
void liberar_conexion(int socket_cliente);

//NEW_POKEMON
t_buffer* crear_buffer_new_pokemon(t_new_pokemon* pokemon);
t_new_pokemon* deserializar_new_pokemon(t_buffer* buffer);
void enviar_new_pokemon(t_new_pokemon* pokemon, int socket_cliente);

//CATCH_POKEMON
/*
t_buffer* crear_buffer_catch_pokemon(t_catch_pokemon* pokemon);
t_catch_pokemon* deserializar_new_pokemon(t_buffer* buffer);
void enviar_new_pokemon(t_catch_pokemon* pokemon, int socket_cliente);
*/


#endif /* UTILS_H_ */

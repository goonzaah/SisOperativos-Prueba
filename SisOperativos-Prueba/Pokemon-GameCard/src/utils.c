/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"



/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
*/

//TODO: esto es inchequeable lo traje de la estructura del tp 0
int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

void* serializar_paquete(t_paquete* paquete, int *bytes)
{
	int size_serializado = paquete->buffer->size + sizeof(op_code);

	void *buffer = malloc(size_serializado);

	int offset = 0;

	memcpy(buffer + offset, &(paquete->codigo_operacion), sizeof(paquete->codigo_operacion));
	offset += sizeof(paquete->codigo_operacion);

	memcpy(buffer + offset, &(paquete->buffer->size), sizeof(paquete->buffer->size));
	offset += sizeof(uint32_t);

	memcpy(buffer + offset, paquete->buffer->stream, paquete->buffer->size);

	(*bytes) = size_serializado;

	return buffer;
}

// start: new_pokemon
t_buffer* crear_buffer_new_pokemon(t_new_pokemon* pokemon)
{
	t_buffer* buffer;
	buffer = malloc(sizeof(t_buffer));

	buffer->size = strlen(pokemon->nombre) + 1; // La longitud del string nombre. Le sumamos 1 para enviar tambien el caracter centinela '\0'. Esto se podría obviar, pero entonces deberíamos agregar el centinela en el receptor.

	void* stream = malloc(buffer->size);
	int offset = 0; // Desplazamiento

	memcpy(stream + offset, (&pokemon->id), sizeof(pokemon->id));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, (&pokemon->nombre_length), sizeof(pokemon->nombre_length));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, (&pokemon->nombre), strlen(pokemon->nombre) + 1);
	offset += (sizeof(pokemon->nombre));

	memcpy(stream + offset, (&pokemon->posicion[0]), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, (&pokemon->posicion[1]), sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, (&pokemon->cantidad), sizeof(pokemon->cantidad));


	buffer->stream = stream;

	// Si usamos memoria dinámica para el nombre, y no la precisamos más, ya podemos liberarla:
	//free(pokemon);
	return buffer;
}

t_new_pokemon* deserializar_new_pokemon(t_buffer* buffer){
	t_new_pokemon* pokemon = malloc(sizeof(pokemon));
	void* stream = buffer->stream;
	memcpy(&(pokemon->id),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->nombre_length),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&(pokemon->nombre),stream, sizeof(pokemon->nombre_length));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->posicion[0]),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->posicion[1]),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->cantidad),stream, sizeof(uint32_t));

	return pokemon;
}

void enviar_new_pokemon(t_new_pokemon* pokemon, int socket_cliente)
{
	t_buffer* buffer = crear_buffer_new_pokemon(pokemon);

	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = NEW_POKEMON;
	paquete->buffer = buffer;

	int size_a_enviar;

	void* a_enviar = serializar_paquete(paquete, &size_a_enviar);

	send(socket_cliente, a_enviar, size_a_enviar, 0);


	//free(paquete->buffer->stream);
	//free(paquete->buffer);
	//free(paquete);

}
// finally: new_pokemon

// start: catch_pokemon
t_buffer* crear_buffer_catch_pokemon(t_new_pokemon* pokemon)
{
	t_buffer* buffer;
	buffer = malloc(sizeof(t_buffer));

	buffer->size = strlen(pokemon->nombre) + 1; // La longitud del string nombre. Le sumamos 1 para enviar tambien el caracter centinela '\0'. Esto se podría obviar, pero entonces deberíamos agregar el centinela en el receptor.

	void* stream = malloc(buffer->size);
	int offset = 0; // Desplazamiento

	memcpy(stream + offset, (&pokemon->id), sizeof(pokemon->id));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, (&pokemon->nombre_length), sizeof(pokemon->nombre_length));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, (&pokemon->nombre), strlen(pokemon->nombre) + 1);
	offset += (sizeof(pokemon->nombre));

	memcpy(stream + offset, (&pokemon->posicion[0]), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, (&pokemon->posicion[1]), sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, (&pokemon->cantidad), sizeof(pokemon->cantidad));


	buffer->stream = stream;

	// Si usamos memoria dinámica para el nombre, y no la precisamos más, ya podemos liberarla:
	//free(pokemon);
	return buffer;
}

t_catch_pokemon* deserializar_catch_pokemon(t_buffer* buffer){
	t_catch_pokemon* pokemon = malloc(sizeof(pokemon));
	void* stream = buffer->stream;
	memcpy(&(pokemon->id),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->nombre_length),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&(pokemon->nombre),stream, sizeof(pokemon->nombre_length));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->posicion[0]),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(pokemon->posicion[1]),stream, sizeof(uint32_t));


	return pokemon;
}

void enviar_catch_pokemon(t_catch_pokemon* pokemon, int socket_cliente)
{
	t_buffer* buffer = crear_buffer_new_pokemon(pokemon);

	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = NEW_POKEMON;
	paquete->buffer = buffer;

	int size_a_enviar;

	void* a_enviar = serializar_paquete(paquete, &size_a_enviar);

	send(socket_cliente, a_enviar, size_a_enviar, 0);
/*
	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
	*/
}
// finally: catch_pokemon

void* recibir_pokemon(int socket_cliente)
{

	op_code codigo_operacion;
	recv(socket_cliente, &codigo_operacion, sizeof(codigo_operacion), 0);
	uint32_t buffer_size;
	recv(socket_cliente, &buffer_size, sizeof(buffer_size), 0);
	t_buffer* buffer = malloc(buffer_size);
	recv(socket_cliente, &buffer, sizeof(buffer), 0);


	void* pokemon = deserializar_new_pokemon(buffer);
	return pokemon;
/*
	switch(paquete->codigo_operacion){
		case NEW_POKEMON:


			free(pokemon);
			break;
		default:
			break;
		}
*/
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

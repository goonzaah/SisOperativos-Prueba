/*
 * conexiones.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<pthread.h>

#define IP "127.0.0.1"
#define PUERTO "4444"

typedef enum
{
	NEW_POKEMON=1,
	CATCH_POKEMON=2
}op_code;

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

pthread_t thread;

void* recibir_buffer(int*, int);

void iniciar_servidor(void);
void esperar_cliente(int);
void* recibir_mensaje(int socket_cliente, int* size);
int recibir_operacion(int);
void process_request(int cod_op, int cliente_fd);
void serve_client(int *socket);
void* serializar_paquete(t_paquete* paquete, int bytes);
void devolver_new_pokemon(void* payload, int size, int socket_cliente);


#endif /* CONEXIONES_H_ */

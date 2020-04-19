/*
 ============================================================================
 Name        : GameCard.c
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "gameCard.h"


int main(void) {
	int conexion;
	char* ip;
	char* puerto;

	//t_log* logger;
	//t_config* config;

	//logger = iniciar_logger();
	//Loggear "soy un log"

	//config = leer_config();


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	//ip = config_get_string_value(config, "IP");
	//puerto = config_get_string_value(config, "PUERTO");
	conexion = crear_conexion("127.0.0.1", "4444");

	char* nombre_pokemon = "pickachu";
	uint32_t posicion[2] = {1,2};

	t_new_pokemon pokemon;
	pokemon.id = 123;
	pokemon.cantidad = 2;
	pokemon.nombre = &nombre_pokemon;
	pokemon.nombre_length = sizeof(nombre_pokemon);
	pokemon.posicion[0] = posicion[0];
	pokemon.posicion[1] = posicion[1];

	//enviar mensaje
	enviar_new_pokemon(&pokemon,conexion);
	//recibir mensaje
	t_new_pokemon* pokemonR = recibir_pokemon(conexion);
	puts(pokemonR->nombre);
	//loguear mensaje recibido



	/*
	//TODO
	t_log* iniciar_logger(void)
	{
	//return log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);
	}

	//TODO

	t_config* leer_config(void)
	{
	t_config* config = config_create("/home/utnso/Game-watch-client/tp0.config");
	return config;
	}
*/
	//TODO
	void terminar_programa(int conexion, t_log* logger, t_config* config)
	{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	}
}

//
//  Servidor.c
//  ServidorSpace
//
//  Created by Edgar Chaves on 4/3/19.
//  Copyright © 2019 Edgar Chaves. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "Servidor.h"


// Para ejecutar:
// Dar run en Xcode, abrir terminal y escribir: telnet [mi dirección ip] [puerto que se esté usando].




int main(int argc, const char * argv[]) {
    //Enlazarnos a un puerto (Bind):
    
        //*Numero del Puerto:
    const int PUERTO = 7200;
    //char *mensaje[] = {"Hola como está."};
    char *mensaje[] = {};
    
    char mensaje1[2000];
    
    int listener = socket_Abierto();
    
    int read_size;
    
    int conn;
    
    int condicion = 0;
    
    if(listener == -1){ // Verifica el estado del listener!
        printf("Ha habido un error en el listener.\n");
        return 0;
    }
    
    enlace_al_Puerto(listener, PUERTO);
    
    if (listen(listener, 1) == -1){
        printf("No es posible escuchar en este puerto. \n");
        return 0;
    }else{
        printf("Se ha logrado enlazar el puerto. \n");
    }
    struct sockaddr_storage cliente;
    unsigned int tamano_direccion = sizeof(cliente);
    printf("Esperando una conexion...\n");
    int conexion = accept(listener,(struct sockaddr*) &cliente, &tamano_direccion);
    
    if (conexion == -1){
        printf("No se puede conectar el socket. \n");
    
    }
    
    //while(1){
    while(1){
        //struct sockaddr_storage cliente;
        //unsigned int tamano_direccion = sizeof(cliente);
        //printf("Esperando una conexion...\n");
        //int conexion = accept(listener,(struct sockaddr*) &cliente, &tamano_direccion);
        
        //if (conexion == -1){
        //    printf("No se puede conectar el socket. \n");
        //}
        
        
        
        printf("Atendiendo al cliente...\n");
        char * msg = mensaje[0];
        //send(conexion, msg, strlen(msg), 0); // Manda a la nueva conexion el mensaje y el tamño del mensaje. Se puede usar write.(Probarlo).
        //send(conexion, "Adios", strlen("Adios"), 0);
        
        while(condicion == 0){ // WHile de prueba(creo que sirve).
            printf("Escriba un comando: \n");
            scanf("%s", mensaje1);
            
        
            send(conexion, mensaje1, strlen(mensaje1),0);
            
            
            
            //enviador(conexion, mensaje);// Funcion creada por Edgar para envio de mensajes personalizados.
            printf("Se ha enviado el mensaje. \n");
            msg = NULL;
            
            if(strcmp(mensaje1, "Terminar")){
                puts("Conexion terminada...");
                close(conexion); // Termina la conexion.
                break;
            }
            
            
        }
    }
    
    
    
     return 0;
}

// Función que implementa el socket:
//No posee entradas, pero retorna un int con el socket.

int socket_Abierto(){
    int socket_propio = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_propio == -1){
        printf("¡Ha ocurrido un error al iniciar el socket! \n");
    }else{
        printf("¡El socket se ha iniciado con éxito! \n");
    }
    
    return socket_propio;
}

//Función que hará el enlace del puerto, recibiendo un int de socket, y un puerto.

void enlace_al_Puerto(int socket, int puerto){
    struct sockaddr_in nombre; // '<-nombre' tiene toda la información necesaria del puerto, dominio(PF_INET).
    nombre.sin_family      = PF_INET;
    nombre.sin_port        = (in_port_t)htons(puerto);
    nombre.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //Para evitar el uso de otros puertos:
    int reuso = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuso, sizeof(int)) == -1){
        perror("No es posible volver a usar este socket. \n");
    }
    
    int conector = bind(socket, (struct sockaddr*)&nombre, sizeof(nombre));
    if(conector == -1){
        perror("No es posible enlazar al puerto: dirección a está en uso. \n");
    }
}

void enviador (int conexion, char *mensaje){
    send(conexion, mensaje, strlen(mensaje),0);
}


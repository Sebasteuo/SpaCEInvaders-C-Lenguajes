//
//  Cliente.c
//  ClienteSpace
//
//  Created by Edgar Chaves on 4/3/19.
//  Copyright © 2019 Edgar Chaves. All rights reserved.
//

#include "Cliente.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) {
    int sock;
    struct sockaddr_in servidor;
    char mensaje_de_Vuelta[1000], mensaje_Servidor[2000];
    char* hola = "Hola";
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        printf("No se pudo crear el socket. \n");
    }
    puts("Socket creado");
    
    servidor.sin_addr.s_addr = inet_addr("172.26.43.80");
    servidor.sin_family      = AF_INET;
    servidor.sin_port        = htons(7200);
    
    
    
    // Conectando al servidor remoto;
    
    if(connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0){
        perror("Conexión fallida \n");
        return 1;
    }
    
    
    puts("Conectado");
    
    while(1){
        //printf("Ingrese un mensaje... \n");
        //scanf("%s", mensaje_de_Vuelta);
        if(recv(sock, mensaje_Servidor, 2000, 0) < 0){
            puts("No se ha podido recibir el mensaje");
            break;
        }
        while(1){
            //if(recv(sock, mensaje_Servidor, 2000, 0) < 0){
              //  puts("No se ha podido recibir el mensaje");
                //break;
           // }
            
            
            if(comparando_Strings(mensaje_Servidor, hola) == 1){
                printf("Adios \n");
            }
            //if(strcmp (mensaje_Servidor, "Hola")){ no sirve.
                
             //   puts("Adios");
              //  break;
           // }
            
            puts(mensaje_Servidor);
            
            printf(mensaje_Servidor);
        
            
            
            
            break;
            
        }
        //printf("%s", mensaje_Servidor);
        break;
        
    }
    
    close(sock);
  return 0;
}


int comparando_Strings(char *s, char *p){
    int booleano = 0;
    p = "Hola\n";
    while(*s != '/0' && *p != '/0'){
        
        printf("Entro al while. \n");
        if (*p != *s){
            booleano = 0;
            break;
            
        }else {
            printf(p);
            s++;
            p++;
            booleano = 1;
            continue;
        }
        
    }
    printf("%i", booleano);
    
    
    return booleano;
    
}

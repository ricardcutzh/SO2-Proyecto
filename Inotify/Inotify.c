#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <time.h>
#include <limits.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN      ( 1024 * ( EVENT_SIZE + 16 ) )

void write_log(char *evento_nombre, char* accion)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char * fecha = asctime(tm);

    FILE *f;
    f = fopen("201503476_log.log", "a+");
    if(f != NULL)
    {
        fprintf(f, "Log: %s | Accion: %s | Date: %s \n", evento_nombre, accion, fecha);
    }
    fclose(f);
}

void console_log(char *evento, char* accion)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char * fecha = asctime(tm);
    printf("Log: %s | Accion: %s |Date: %s \n", event->name, accion, fecha);
}

int main() {
    int length, i = 0;
    char buffer[BUF_LEN];
    int filedescriptor = inotify_init(); // DEVUELVE UN DESCRIPTOR

    if(filedescriptor < 0)
    {
        perror("inotify_init");
    }

    // CREANDO EL MONITOR QUE QUEREMOS ESCUCHAR
    int watch_descriptor = inotify_add_watch(filedescriptor, "/", IN_MODIFY | IN_CREATE | IN_DELETE);

    length = read(filedescriptor, buffer, BUF_LEN);
    if(length < 0)
    {
        perror("lectura");
    }

    while(1)
    {
        i = 0;
        length = read(filedescriptor, buffer, BUF_LEN);
        if(length < 0)
        {   
            perror("lectura");
        }
        while(i < length)
        {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if(event->len)
            {
                if(event->mask & IN_CREATE)
                {
                    if(event->mask & IN_ISDIR)
                    {
                        console_log(event->name, "Directorio Creado");
                        write_log(event->name, "Directorio Creado");
                    }
                    else
                    {
                        console_log(event->name, "Archivo Creado");
                        write_log(event->name, "Archivo Creado");
                    }
                } else if(event->mask & IN_DELETE)
                {
                    if(event->mask & IN_ISDIR)
                    {
                        console_log(event->name, "Directorio Eliminado");
                        write_log(event->name, "Directorio Eliminado");
                    }
                    else
                    {
                        console_log(event->name, "Archivo Eliminado");
                        write_log(event->name, "Archivo Eliminado");
                    }
                } else if(event->mask & IN_MODIFY)
                {
                    if(event->mask & IN_ISDIR)
                    {
                        console_log(event->name, "Directorio Modificado");
                        write_log(event->name, "Directorio Modificado");
                    }
                    else
                    {
                        console_log(event->name, "Archivo Modificado");
                        write_log(event->name, "Archivo modificado");
                    }
                } 
                i += EVENT_SIZE + event->len;
            }
        }
    }
    inotify_rm_watch(filedescriptor, watch_descriptor);
    close(filedescriptor);
    return EXIT_SUCCESS;
}
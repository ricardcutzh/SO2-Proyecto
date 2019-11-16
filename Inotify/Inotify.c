#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN      ( 1024 * ( EVENT_SIZE + 16 ) )

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
                        printf("Directorio %s fue creado\n", event->name);
                    }
                    else
                    {
                        printf("Archivo %s fue creado\n", event->name);
                    }
                } else if(event->mask & IN_DELETE)
                {
                    if(event->mask & IN_ISDIR)
                    {
                        printf("Directorio %s fue eliminado\n", event->name);
                    }
                    else
                    {
                        printf("Archivo %s fue eliminado\n", event->name);
                    }
                } else if(event->mask & IN_MODIFY)
                {
                    if(event->mask & IN_ISDIR)
                    {
                        printf("Directorio %s fue modificado\n", event->name);
                    }
                    else
                    {
                        printf("Archivo %s fue modificado\n", event->name);
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
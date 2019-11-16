#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) + 24 )
#define BUF_LEN     ( 1024 * EVENT_SIZE )

int main() {
    char buffer[BUF_LEN];
    int filedescriptor = inotify_init(); // DEVUELVE UN DESCRIPTOR

    if(filedescriptor < 0)
    {
        perror("inotify_init");
    }

    // CREANDO EL MONITOR QUE QUEREMOS ESCUCHAR
    int watch_descriptor = inotify_add_watch(filedescriptor, "/", IN_MODIFY | IN_CREATE | IN_DELETE);

    int length = read(filedescriptor, buffer, BUF_LEN);
    if(length < 0)
    {
        perror("lectura");
    }

    int offset = 0;

    while(offset < length)
    {
        struct inotify_event *event = (struct inotify_event *) &buffer[offset];
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
                    printf("Archivo %s fue modificado", event->name);
                }
            }
            offset += sizeof(struct inotify_event) + event->len;
        }

        inotify_rm_watch(filedescriptor, watch_descriptor);
        close(filedescriptor);

        return EXIT_SUCCESS;
    }
    return 0;
}
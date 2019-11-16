#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) + 24 )
#define BUF_LEN     ( 1024 * EVENT_SIZE )

int main() {
    char buffer[BUF_LEN];
    int filedescriptor = inotify_init(); // DEVUELVE UN DESCRIPTRO
    return 0;
}
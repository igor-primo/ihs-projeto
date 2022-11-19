#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>

#define FACING_LEFT 0
#define FACING_RIGHT 1
#define FACING_UP 2
#define FACING_DOWN 3
#define CLICK 4

#define OFFSET 2

int main(int argc, char **argv)
{

    if(argc < 2)
        return 1;

    long which = strtol(argv[1], NULL, 10);

    int fd;
    struct uinput_user_dev uidev;
    struct uinput_setup usetup;
    struct input_event ev, sy;
    int dx, dy;
    int i;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_RELBIT, REL_X);
    ioctl(fd, UI_SET_RELBIT, REL_Y);

    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "mysterious device");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0x1;
    uidev.id.product = 0x1;
    uidev.id.version = 1;

    struct input_event ev_click, ev_sync;

    write(fd, &uidev, sizeof(uidev));

    ioctl(fd, UI_DEV_CREATE);

    switch(which) {
    case FACING_LEFT:
        dx = - OFFSET;
        dy = 0;
        break;
    case FACING_RIGHT:
        dx = OFFSET;
        dy = 0;
        break;
    case FACING_UP:
        dx = 0;
        dy = - OFFSET;
        break;
    case FACING_DOWN:
        dx = 0;
        dy = OFFSET;
        break;
    case CLICK:
        memset(&ev_click, 0, sizeof(ev_click));
        memset(&ev_sync, 0, sizeof(ev_sync));

        ev_click.type = EV_KEY;
        ev_click.code = BTN_LEFT;
        ev_click.value = 10;
        write(fd, &ev_click, sizeof(ev_click));
        ev_sync.type = EV_SYN;
        usleep(15000);
    }

    for(i = 0; i < 20; i++) {
        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_REL;
        ev.code = REL_X;
        ev.value = dx;
        write(fd, &ev, sizeof(struct input_event));

        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_REL;
        ev.code = REL_Y;
        ev.value = dy;
        write(fd, &ev, sizeof(struct input_event));

        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_SYN;
        ev.code = 0;
        ev.value = 0;
        write(fd, &ev, sizeof(struct input_event));

        usleep(15000);
    }

    ioctl(fd, UI_DEV_DESTROY);

    close(fd);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef EXISTS_XOSD
#include <xosd.h>
#endif
#define CTL_FILE "/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness"
#define MAX 255
#define MIN 0
#define STEP 17

int usage(char *argv[]) {
    printf("usage: %s up|down\n\n", argv[0]);
    return EXIT_FAILURE;
}

int get_current() {
    int val;
    FILE *ctl_file;

    ctl_file = fopen(CTL_FILE, "r");
    fscanf(ctl_file, "%i", &val);
    fclose(ctl_file);

    return val;
}

void set_current(int val) {
    if (val > MAX) val = MAX;
    if (val < MIN) val = MIN;

    printf("Value: %i", val);
    FILE *ctl_file;

    ctl_file = fopen(CTL_FILE, "w");
    fprintf(ctl_file, "%i", val);
    fclose(ctl_file);

    // Display OSD
#ifdef XOSD_H
    xosd *osd;

    osd = xosd_create(3);

    if (osd == NULL) return;

    int percentage = (int)(100.0 * val / MAX);

    xosd_set_pos(osd, XOSD_bottom);
    xosd_set_align(osd, XOSD_center);
    xosd_set_timeout(osd, 1);
    xosd_set_shadow_offset(osd, 1);

    xosd_display(osd, 0, XOSD_string, "Brightness");
    xosd_display(osd, 2, XOSD_percentage, percentage);

    xosd_wait_until_no_display(osd);

    xosd_destroy(osd);
#endif
}

int main(int argc, char *argv[]) {
    // Make sure we have required arg
    if (argc != 2) return usage(argv);

    // fetch the current value
    int val = get_current();

    // Increment/Decrement the current value
    if (strcmp(argv[1], "up") == 0) {
        val += STEP;
    } else if (strcmp(argv[1], "down") == 0) {
        val -= STEP;
    } else {
        return usage(argv);
    }

    // write the new value
    set_current(val);

    return EXIT_SUCCESS;
}

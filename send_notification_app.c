#include<stdio.h>
#include "send_notification.c"

int main(int argc, char **argv)
{
	if (!start_notif_service("AppName"))
	{
		printf("\n[!]Didn't work\n");
		exit(1);
	}
	if (!notif_sender("Summary", "Body", 2, 1, NULL, NULL)) // fifth argument can be path to icon file(image file).
	// sixth argument can be path to a media file that will be played as a notification bell.
	{
		printf("\n[!]Didn't work\n");
		exit(1);
	}
	stop_notif_service();
	printf("\n[+]It worked :)\n");
	return 0;
}

// Compile this file using :: `gcc -I /usr/include/glib-2.0/ -I /usr/include/gdk-pixbuf-2.0/ -I /usr/lib64/glib-2.0/include/ -o send_notification_app send_notification_app.c -lvlc -lnotify`

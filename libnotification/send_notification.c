#include <stdlib.h>
#include <unistd.h>
#include <libnotify/notify.h>
#include "play_sound.h"

/*
    Checks existence of file path, returns 1 on success and 0 on failure.
*/
int does_file_exist(char *file){
    return (access(file, F_OK)==0);
}

// libnotify and libnotify-devel needs to be installed. You need glib2 and glib2-devel too.
// Try installing them using your os native package manager like apt or dnf or zypper.
// We need gdk-pixbuf2 and gdk-pixbuf2-devel, for showing notification. Make sure you install all of them.

int start_notif_service(char *app_name) //initializes notification service
{
	if (!app_name)
		return 0;
	if (!notify_init(app_name))
		return 0;
	return 1;
}

int notif_sender(char *notif_summary, char *notif_body, int notif_expires, int notif_urgency, char *icon_2_use, char *media_file) // sends request for displaying notification
{
	if (!notif_summary || !notif_body || !(0 <= notif_urgency && notif_urgency <= 2))
		return 0;
	NotifyNotification *my_notification = NULL;
	if (!does_file_exist(icon_2_use)) // icon_file_path can have a value NULL. In that case default notification icon will be used by system.
		my_notification = notify_notification_new(notif_summary, notif_body, NULL);
	else
		my_notification = notify_notification_new(notif_summary, notif_body, icon_2_use);
	if (notif_expires < 0)
		notify_notification_set_timeout(my_notification, NOTIFY_EXPIRES_DEFAULT);
	else if (notif_expires == 0)
		notify_notification_set_timeout(my_notification, NOTIFY_EXPIRES_NEVER);
	else
		notify_notification_set_timeout(my_notification, (gint)notif_expires);
	if (notif_urgency == 0)
		notify_notification_set_urgency(my_notification, NOTIFY_URGENCY_LOW);
	else if (notif_urgency == 1)
		notify_notification_set_urgency(my_notification, NOTIFY_URGENCY_NORMAL);
	else
		notify_notification_set_urgency(my_notification, NOTIFY_URGENCY_CRITICAL);
	if (!notify_notification_show(my_notification, NULL))
	{
		notify_uninit();
		return 0;
	}
	if (does_file_exist(media_file)) // you can NULL for media_file, if you don't want any notification to be played.
	{
		if (!play_notification_sound(media_file))
		{
			notify_uninit();
			return 0;
		}
	}
	return 1;
}

void stop_notif_service() // stops notification service
{
	notify_uninit();
	return;
}

// Compile this into a shared library :: `gcc -shared -I /usr/include/glib-2.0/ -I /usr/include/gdk-pixbuf-2.0/ -I /usr/lib64/glib-2.0/include/ -Wall -fPIC -o libnotif.so send_notification.c -lvlc -lnotify`

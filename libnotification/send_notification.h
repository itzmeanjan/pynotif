int does_file_exist(char *file);

int start_notif_service(char *app_name);

int notif_sender(char *notif_summary, char *notif_body, int notif_expires, int notif_urgency, char *icon_2_use, char *media_file);

void stop_notif_service();

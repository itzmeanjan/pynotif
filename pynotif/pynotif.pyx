__version__ = '0.1.0'
__author__ = 'Anjan Roy <anjanroy@yandex.com>'

cdef extern from "send_notification.h":
    int start_notif_service(char *app_name)
    int notif_sender(char *notif_summary, char *notif_body, int notif_expires, int notif_urgency, char *icon_2_use, char *media_file)
    void stop_notif_service()

def startNotif(appName : bytes) -> int:
    '''
        Registers `appName` with notification service.

        Returns 0 / 1 to denote failure / success, respectively.
    '''
    return start_notif_service(appName)

def sendNotif(summary: bytes, body: bytes, expiry: int, urgency: int, icon: bytes, sound: bytes) -> int:
    '''
        Submits notification display request to platform notification service.

        summary - notification summary to displayed
        body - body content of notification, can also include HTML tags
        expiry - how long notification to be displayed ( in seconds )
        urgency - how urgent is notification, == 0 :: low urgency; == 1 :: normal urgency; > 1 :: critical urgency
        icon - path to icon file, may be *.svg
        sound - path to sound file to be played after notification is displayed

        Returns 0 / 1 to denote failure / success, respectively.
    '''
    return notif_sender(summary, body, expiry, urgency, icon, sound)

def stopNotif() -> None:
    '''
        Stops registered notification service for this `appName`

        Consider doing it, it won't be done explicitly for you ;)
    '''
    stop_notif_service()
    return

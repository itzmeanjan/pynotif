#!/usr/bin/python3

try:
    from os.path import join, exists, dirname, realpath
    from ctypes import CDLL, create_string_buffer, c_char_p, c_int, ArgumentError
except ImportError as e:
    print('[!]Module Unavailable : {}'.format(str(e)))
    exit(1)


def __find_file__(file):
    '''
        This function checks existence of a file path and returns either True or False.
    '''
    return exists(file)


def send(app_name, summary, body, expires, urgency, icon_name=join(dirname(realpath(__file__)), 'my_icon.png'), media_file=join(dirname(realpath(__file__)), 'button_sound.wav'), so_file=join(dirname(realpath(__file__)), 'libnotif.so')):
    '''
        This function sends native notification by using libnotify.so, C library.

        It takes app_name, summary of notification, body content of notification,
        expiry time and urgency of notificaation to be displayed, as mandatory arguments.

        icon_name, media_file and so_file arguments have some default values.

        Make sure you don't change so_file's value. It's dynamically linked shared object 
        file, which finally gets opened by ctypes.CDLL() and it's our intermediate link for calling C functions which are defined in sources of so_file.

        Finally it'll return a python list, denoting status.

        [True, `status`] -> denotes success.
        [False, `status`] -> denotes failure.
    '''
    if(not app_name or not summary or not body or not __find_file__(so_file)):
        return [False, 'Bad Arguments']
    try:
        shared_lib_obj = CDLL(so_file)
        shared_lib_obj.start_notif_service.argtypes = [c_char_p]
        shared_lib_obj.notif_sender.argtypes = [
            c_char_p, c_char_p, c_int, c_int, c_char_p, c_char_p]
        # initializes notification service
        if(not int(shared_lib_obj.start_notif_service(create_string_buffer(app_name.encode('utf-8'))))):
            return [False, 'Notification Service not started']
        if(not int(shared_lib_obj.notif_sender(create_string_buffer(summary.encode('utf-8')), create_string_buffer(body.encode('utf-8')), c_int(expires), c_int(urgency), create_string_buffer(icon_name.encode('utf-8')), create_string_buffer(media_file.encode('utf-8'))))):
            # sends request for displaying notification
            return [False, 'Displaying Notification failed']
        shared_lib_obj.stop_notif_service()  # stops notification service
        return [True, 'Displayed Notification']
    except ArgumentError as e:
        return [False, str(e)]
    except Exception as e:
        return [False, str(e)]


if __name__ == '__main__':
    print('[!]This is module is designed to be used as a backend handler :(')
    exit(0)

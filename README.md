# pynotif
A very simple to use Python API for accessing native notification service on Linux

## Example Usage ::

  #### pynotif.notification.send :
    ```
      from pynotif.notification import send
      print(send('your_app_name', 'summary_of_notification', 'body_of_notification', 2, 1)) 
      '''
        Here for expires parameter, I'm using 2. After 2 seconds it'll get removed from desktop visibility zone.
        
        Urgency of notification is set to 1, which is default urgency value.
        
        In default case, I've added a notification sound file, *.wav, in repo, which will be played after displaying notification.
        
        You can also set path to a image file, which can be used as a icon for notification.
      '''
      print(send("app", 'summary', 'body', 2, 1, media_file=''))  # sends notification where no notification sound is played.
      print(send("app", 'summary', 'body', 2, 1, icon_name=''))  # system icon gets displayed.
    ```
    
   So it's a very easy to use python API for displaying notification on your linux machine from your python script.
 
 ## How does it work ?
  
  - I've written one C program, [send_notification.c](https://github.com/itzmeanjan/pynotif/blob/master/send_notification.c), 
  which displays notification using libnotify on linux.
  
  - If you want to play a small notification sound, that will let user know something has happened, I've got you covered.
  
  - [play_sound.c](https://github.com/itzmeanjan/pynotif/blob/master/play_sound.c), lets you play notification sound by using vlc.
  
  - It's not mandatory to play a sound for displaying notification, it can be kept completely silent.
  
  - Then I compiled [send_notification.c](https://github.com/itzmeanjan/pynotif/blob/master/send_notification.c), into a dynamically linked shared library object, [libnotif.so](https://github.com/itzmeanjan/pynotif/blob/master/libnotif.so), using gcc.
    
    ```
      >> gcc -shared -I /usr/include/glib-2.0/ -I /usr/include/gdk-pixbuf-2.0/ -I /usr/lib64/glib-2.0/include/ -Wall -fPIC -o libnotif.so send_notification.c -lvlc -lnotify
    ```
   
   - And I've a python script [notification.py](https://github.com/itzmeanjan/pynotif/blob/master/notification.py), which accesses [libnotif.so](https://github.com/itzmeanjan/pynotif/blob/master/libnotif.so), using ctypes.CDLL() and calls required functions to display notification successfully.
   
   - You can just import send() from pynotif.notification, and pass required arguments, which will finally result into successful display of notification on your linux desktop.
   
   - In pynotif.notification.send(), you can pass value for expires parameter, <0 or 0 or >0. Use 2 as expires parameter value, so notification will expire after 2 seconds. That gives you enough time to read notification.
   
   - On passing value <0, 0, >0 : notification will expire after default time period, notification will expire never, notification will expire after x seconds respectively.
   
   - There's another parameter, urgency, which will take value 0 or 1 or >1, resulting into low urgency, normal urgency, critical urgency respectively.
   
   - In pynotif.notification.send(), app_name, summary and body takes string values, and are mandatory.
   
   - icon_name, media_file has got default values, which can be passed ''(blank string), to not use any custom icon_image or not play any notification sound.
   
   - You can pass, path to any other icon file, as value for icon_name parameter and path to any media file, as value for media_file, which will be played after displaying notification using vlc.
   
   - so_file, path to shared library, has default value. Don't change it if you don't understand what you're doing.
   
   
 ## How does it look like ?
  
  Within desktop display area:
 
   ![notification screenshot on fedora linux gnome desktop, view 1](https://github.com/itzmeanjan/pynotif/blob/master/notification_screenshot_on_fedora_gnome_1.png)
  
  
  After pulling notification display area down on gnome desktop:
  
   ![notification screenshot on fedora linux gnome desktop, view 2](https://github.com/itzmeanjan/pynotif/blob/master/notification_screenshot_on_fedora_gnome_2.png)
   
 
## Dependency ::

  - Make sure you've **libnotify** and **libnotify-devel** installed, for using native notification service. Installation examples on Fedora Linux provided here.
    ```
      >> dnf install libnotify.x86_64, libnotify-devel.x86_64
    ```
  
  - You need **glib2** and **glib2-devel**, which can easily be installed using OS package manager.
    ```
      >> dnf install glib2.x86_64, glib2-devel.x86_64
    ```
  - Install **gdk-pixbuf2** and **gdk-pixbuf2-devel** too.
    ```
      >> dnf install gdk-pixbuf2.x86_64, gdk-pixbuf2-devel.x86_64
    ```
  
  - And finally you need **vlc**, **vlc-core** and **vlc-devel**.
    ```
      >> dnf install vlc.x86_64, vlc-core.x86_64, vlc-devel.x86_64
    ```
  
  - If you're on Debian or Ubuntu based distros, use **apt**, for installing required packages.
  
    ```
      >> apt install vlc, libvlc-dev, libnotify4, libnotify-dev, libglib2.0-0, libglib2.0-dev, libgdk-pixbuf2.0-0, libgdk-  pixbuf2.0-dev
    ```
  
  ## Other Usages ::
    
   - You can easily include [send_notification.c](https://github.com/itzmeanjan/pynotif/blob/master/send_notification.c), in your C program and Compile it, so that you'll be able to send native notification from your C program.
   
   - I've also added [send_notification_app.c](https://github.com/itzmeanjan/pynotif/blob/master/send_notification_app.c), which shows you example usage of sending notification using C programming interface.
   
   - Compilation can be done using 
   ```
      >> gcc -I /usr/include/glib-2.0/ -I /usr/include/gdk-pixbuf-2.0/ -I /usr/lib64/glib-2.0/include/ -o send_notification_app send_notification_app.c -lvlc -lnotify
   ```
   
  - Then you can easily run [send_notification_app](https://github.com/itzmeanjan/pynotif/blob/master/send_notification_app) using
    ```
      >> ./send_notification_app
    ```
    
 ## Important Points ::
 
  - I've used **(GCC) 8.2.1**, for compiling C programs.
  - As testing platform, I've used Ubuntu, Fedora, Debian and Linux Mint with Gnome DE. And it worked well.
  - By the way, it won't work on Windows.
  - Try testing on other linux distros too, and let me know whether it's working properly or not.
  - Thanks to VLC developers, which is used for playing notification sound.
  
  
Hope it was helpful :)

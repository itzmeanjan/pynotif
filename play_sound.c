#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<vlc/vlc.h>

// you need to have vlc installed on your linux machine.
//And vlc-devel, development files i.e. header files for using vlc features from another application, needs to be installed.

int play_notification_sound(char *media_fl){ // plays a media file, denoted by a path to that file.
	libvlc_instance_t *vlc_init=libvlc_new(0,NULL);
	if(!vlc_init)
		return 0;
	libvlc_media_t *vlc_media_init=libvlc_media_new_path(vlc_init,media_fl); // try passing a valid path to media file, otherwise it might cause segmentation fault.
	if(!vlc_media_init){
		libvlc_release(vlc_init);
		return 0;
	}
	if(libvlc_media_parse_with_options(vlc_media_init,libvlc_media_parse_local,-1)){ // attempts to parse media file for determining media file length.
		libvlc_media_release(vlc_media_init);
		libvlc_release(vlc_init);
		return 0;
	}
	sleep(1); // if you face any problems with playing media file, try increasing sleep time.
	// This is the amount of time we're giving VLC, for parsing media file, so that it can determine length of media file to be played.
	if(libvlc_media_get_parsed_status(vlc_media_init)!=4){
		libvlc_media_release(vlc_media_init);
		libvlc_release(vlc_init);
		return 0;
	}
	float duration=(float)libvlc_media_get_duration(vlc_media_init); // extracts duration of media file.
	if((int)duration == -1){ // on failure, it exits. If it sleep time for parsing media file is too small, parsing might fail.
		libvlc_media_release(vlc_media_init);
		libvlc_release(vlc_init);
		return 0;
	}
	libvlc_media_player_t *vlc_media_player_init=libvlc_media_player_new(vlc_init); // creates media player instance.
	if(!vlc_media_player_init){
		libvlc_media_release(vlc_media_init);
		libvlc_release(vlc_init);
		return 0;
	}
	libvlc_media_player_set_media(vlc_media_player_init,vlc_media_init);
	libvlc_media_release(vlc_media_init);
	if(libvlc_media_player_play(vlc_media_player_init)){ // plays media file.
		libvlc_media_player_release(vlc_media_player_init);
		libvlc_release(vlc_init);
		return 0;
	}
	sleep((duration/1000)+1); // when the media file is played, main execution threads goes to sleep. Here length of media file is `duration` milisec.
	libvlc_media_player_stop(vlc_media_player_init);
	libvlc_media_player_release(vlc_media_player_init);	
	libvlc_release(vlc_init); // we release vlc instance.
	return 1;
}

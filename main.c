#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "f.h"


const int screen_width = 600;
const int screen_height = 600;

int main()
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_BITMAP *bitmap = NULL;
  
  float coeffs[3], S;       // y = ax^2 + bx + c && dx^2 + dy^2 = S
                            // [0] = a, [1] = b, [2] = c

  // initialize allegro
  if(!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
  }

  // initialize keyboard
  if(!al_install_keyboard()) {
    fprintf(stderr, "failed to initialize the keyboard!\n");
    return -1;
  }

  // test values
  coeffs[0] = 1.0;
  coeffs[1] = 0.0;
  coeffs[2] = 0.0;
  int scale = 10;
  S = 0.1;

  // set format of bitmap
  al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_BGR_888);

  // create display
  display = al_create_display(screen_width, screen_height);
  if(!display) {
    fprintf(stderr, "failed to create display!\n");
    return -1;
  }

  // add possibility to create primitive figures
  if(!al_init_primitives_addon()){
    return -1;
  }
  bitmap = al_create_bitmap(screen_width, screen_height);
  if(!bitmap) {
    fprintf(stderr, "failed to create bouncer bitmap!\n");
    al_destroy_display(display);
    return -1;
  }
  

  al_set_target_bitmap(bitmap);
  al_set_target_bitmap(al_get_backbuffer(display));

  // initialize event queue for keyboard input
  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  if(!event_queue) {
    fprintf(stderr, "failed to create event_queue!\n");
    al_destroy_bitmap(bitmap);
    al_destroy_display(display);
    return -1;
  }

  // get source for events
  al_register_event_source(event_queue, al_get_keyboard_event_source());


  ALLEGRO_EVENT event;
  ALLEGRO_LOCKED_REGION *locked;
  unsigned char *data;
  while(1){
    al_wait_for_event(event_queue, &event);

    // create bitmap
  
    
    // quit program if window close button or escape is pressed
    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) break;

    if( event.type == ALLEGRO_EVENT_KEY_DOWN){
      switch(event.keyboard.keycode){
        case ALLEGRO_KEY_DOWN: scale--;       break;
        case ALLEGRO_KEY_UP: scale++;         break;
        case ALLEGRO_KEY_1: coeffs[0] += 1.0; break;  // a
        case ALLEGRO_KEY_Q: coeffs[0] += 0.1; break;  // a
        case ALLEGRO_KEY_A: coeffs[0] -= 0.1; break;  // a
        case ALLEGRO_KEY_Z: coeffs[0] -= 1.0; break;  // a
        case ALLEGRO_KEY_2: coeffs[1] += 1.0; break;  // b
        case ALLEGRO_KEY_W: coeffs[1] += 0.1; break;  // b
        case ALLEGRO_KEY_S: coeffs[1] -= 0.1; break;  // b
        case ALLEGRO_KEY_X: coeffs[1] -= 1.0; break;  // b
        case ALLEGRO_KEY_3: coeffs[2] += 1.0; break;  // c
        case ALLEGRO_KEY_E: coeffs[2] += 0.1; break;  // c
        case ALLEGRO_KEY_D: coeffs[2] -= 0.1; break;  // c
        case ALLEGRO_KEY_C: coeffs[2] -= 1.0; break;  // c
        case ALLEGRO_KEY_4: S         += 1.0; break;  // S
        case ALLEGRO_KEY_R: S         += 0.1; break;  // S
        case ALLEGRO_KEY_F: S         -= 0.1; break;  // S
        case ALLEGRO_KEY_V: S         -= 1.0; break;  // S
      }
    }

    // draw axises
    al_clear_to_color(al_map_rgb(79,79,79));

    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(0,0,0));

    al_set_target_backbuffer(display);

    // calculate after change
    locked = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_BGR_888, ALLEGRO_LOCK_READWRITE);
    //al_clear_to_color(al_map_rgb(0,0,0));
    data = locked->data;
    int pitch = locked->pitch;
    
    printf("pitch= %d\n", pitch);
    float a = 1;
    a = f(data, screen_width, screen_height, pitch, coeffs, S, scale);
    printf("%f\n", a);

    al_unlock_bitmap(bitmap);
    al_draw_bitmap(bitmap, 0, 0, 0);

    // ox
    al_draw_line(0, screen_height/2, screen_width, screen_height/2, al_map_rgb(100,100,155), 3);
    // oy
    al_draw_line(screen_width/2, 0, screen_width/2, screen_height, al_map_rgb(100,100,155), 3);

  // scale
    for(int i = 0; i <= scale; i++){
    al_draw_line(screen_width/2 + (screen_width/(2*scale))*i, screen_height/2+6, 
              screen_width/2 + (screen_width/(2*scale))*i, screen_height/2-6, al_map_rgb(100,100,155), 3);
    al_draw_line(screen_width/2 -(screen_width/(2*scale))*i, screen_height/2+6, 
              screen_width/2 - (screen_width/(2*scale))*i, screen_height/2-6, al_map_rgb(100,100,155), 3);
    al_draw_line(screen_width/2 - 6, screen_height/2 + (screen_height/(2*scale))*i, 
              screen_width/2 + 6, screen_height/2 + (screen_height/(2*scale))*i, al_map_rgb(100,100,155), 3);
    al_draw_line(screen_width/2 - 6, screen_height/2 - (screen_height/(2*scale))*i, 
              screen_width/2 + 6, screen_height/2 - (screen_height/(2*scale))*i, al_map_rgb(100,100,155), 3);
    }
    printf("a= %f, b= %f, c= %f, s = %f\n",coeffs[0], coeffs[1], coeffs[2], S);
    al_flip_display();
    
  }
  


  
  al_rest(1.0);
  al_destroy_bitmap(bitmap);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  return 0;
} 

/*
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "f.h"

const int SCREEN_W = 512;
const int SCREEN_H = 512;
const int XYMATRIX_WIDTH = 512;
const int XYMATRIX_HEIGHT = 512;
enum ANGLES{
  SWIFT_UP, SWIFT_DOWN, SWIFT_LEFT, SWIFT_RIGHT
};

int main()
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_BITMAP *xy_matrix = NULL;
  bool redraw = true;
  int coordinates[12] = {60, 100, 50,
                        200, 200, 10,
                        100, 250, 100,
                         70, 30, 10};
  int bitmap_info[3] = {XYMATRIX_WIDTH, XYMATRIX_HEIGHT};
  char * z_buffer;
  z_buffer = malloc(sizeof(*z_buffer) * XYMATRIX_WIDTH * XYMATRIX_WIDTH);
  int angles[4] = {0, 0, 0, 0};

  if(!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
  }

  if(!al_install_keyboard()) {
    fprintf(stderr, "failed to initialize the keyboard!\n");
    return -1;
  }

  al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_BGR_888);
  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display) {
    fprintf(stderr, "failed to create display!\n");
    return -1;
  }

  xy_matrix = al_create_bitmap(XYMATRIX_WIDTH, XYMATRIX_HEIGHT);
  if(!xy_matrix) {
    fprintf(stderr, "failed to create bouncer bitmap!\n");
    al_destroy_display(display);
    return -1;
  }
  al_set_target_bitmap(xy_matrix);
  al_clear_to_color(al_map_rgb(255, 0, 255));
  al_set_target_bitmap(al_get_backbuffer(display));
  event_queue = al_create_event_queue();
  if(!event_queue) {
    fprintf(stderr, "failed to create event_queue!\n");
    al_destroy_bitmap(xy_matrix);
    al_destroy_display(display);
    return -1;
  }
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());

  int a = 0;


  do{
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
      break;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_UP:{
          angles[SWIFT_UP] = 10;
          break;
        }
        case ALLEGRO_KEY_DOWN:{
          angles[SWIFT_DOWN] = 10;
          break;
        }
        case ALLEGRO_KEY_LEFT:{
          angles[SWIFT_LEFT] = 10;
          break;
        }
        case ALLEGRO_KEY_RIGHT:{
          angles[SWIFT_RIGHT] = 10;
          break;
        }
      }
      redraw = true;
      al_unregister_event_source(event_queue, al_get_keyboard_event_source());
    }
    if(redraw){
      for(int i = 0; i < 4; ++i) printf("x[%d]=%d, y[%d]=%d, z[%d]=%d\n", i, coordinates[i*3], i, coordinates[i*3 + 1], i, coordinates[i*3 + 2]);
      ALLEGRO_LOCKED_REGION *locked;
      unsigned char *data;
      // unsigned int temp;
      double temp = 3.0;
      locked = al_lock_bitmap(xy_matrix, ALLEGRO_PIXEL_FORMAT_BGR_888, ALLEGRO_LOCK_READWRITE);
      data = locked->data;
      bitmap_info[2] = locked->pitch;
      f(data, z_buffer, bitmap_info, coordinates, angles, &temp);
      // printf("%d\n", locked->pitch);
      printf("%lf\n", temp);
      // for(int j = 0; j < 256; ++j){
      //   for(int i = 0; i < 256; ++i){
      //     data[i*3 + j*locked->pitch] = 255;
      //     data[i*3 + j*locked->pitch + 1] = 255;
      //     data[i*3 + j*locked->pitch + 2] = 255;
      //   }
      // }

      data = NULL;
      al_unlock_bitmap(xy_matrix);
      for(int i = 0; i < 4; ++i){
        angles[i] = 0;
      }
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_bitmap(xy_matrix, a, a, 0);
      a += 64;
      a %= 318;
      al_draw_line(100, 200, 300, 400, al_map_rgb(255,0,0), 3);
      al_flip_display();
      al_register_event_source(event_queue, al_get_keyboard_event_source());
    }

  }  while(1);
  // for(int i = 0; i < 256*256; ++i) printf("%c", z_buffer[i]);

  free(z_buffer);
  al_destroy_bitmap(xy_matrix);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  return 0;
}*/
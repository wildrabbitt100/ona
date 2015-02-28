#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <iostream>

using namespace std;



int wait_for_keypress(void);


int make_table();

class InitialisationClass 
{

   public:
   
      
      uint32_t version;
      int init_okay;
	  
	  InitialisationClass(void) : init_okay(0), version(0)
      {
         cout << "In default constructor for InitialisationClass\n\n";
      }
	  
	  InitialisationClass(ofstream &log)
      {
	     cout << "Calling al_install_system().\n";
         if( al_install_system(ALLEGRO_VERSION_INT, atexit) == false)
         {   
		    
			cout << "Unable to install Allegro System.\n";
		    log.write("Unable to install the allegro system.\n", 39);
            return;
         }
		 else
		 {
		    cout << "Installed Allegro System.\n";
		 }
   
         cout << "here 2.\n";
         al_init_font_addon();
         if(al_init_ttf_addon() == false)
	     {
	        log.write("Unable to install true type font addon.\n", 41);
			return;
	     }
		 
		 
		 al_install_keyboard();
		 
		 cout << "Finished initialising InitialisationClass.\n";
		 
		 init_okay = 1;
      }
	  
	  /* Constructor for when the log file couldn't be created. */
   
      InitialisationClass(int dummy)
      {
	     cout << "Calling al_install_system().\n";
         if( al_init() == false)
         {
		    cout << "here 10.";
		    return;
		 }
		 
		 cout << "Called it.\n";
		 
         al_init_font_addon();
		 
         if(al_init_ttf_addon() == false)
	     {
	        return;  
	     }
		 
		 al_install_keyboard();
		 
	     cout << "Finished initialising InitialisationClass.\n\n";
	     init_okay = 1;
      }
	  
   private:
   
   int print_version_number(void)
   {
      ;
   }

   
   
   
   
   





};
/* END OF definition of SetUpClass. */





class DisplayClass
{

   public:
   
   int init_okay;
   int x_for_next_print;
   int font_loaded;
   
   
   DisplayClass() : display(NULL), init_okay(0), x_for_next_print(0), font(NULL), font_loaded(0), buffer(NULL)
   {
   
   }
   
   DisplayClass(int dummy, ofstream &log) : buffer(NULL) 
   {
       al_set_new_display_flags(ALLEGRO_WINDOWED);
	   
       al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
   
       display = NULL;
   
       if( (display = al_create_display(1024, 768)) == NULL )
       {
          return;
       }
	   else
	   {
	      init_okay = 1;
	   }
	   
       al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA);
	   
	   
	   
	   font = al_load_ttf_font("SIRCLIVE.ttf", 16, 0);
	   if(font == NULL)
	   {
	      log.write("Unable to load font SIRCLIVE.ttf\n", 34);
		  font_loaded = 0;
	   }
	   else
	   {
	      font_loaded = 1;
	   }
	  
	   buffer = NULL;
	   buffer = al_create_bitmap(1024, 768);
	   if(buffer == NULL)
	   {
	      init_okay = 0;
		  return;
	   }
	   else
	   {
	       al_set_target_bitmap(buffer);
	       al_clear_to_color(al_map_rgba(0, 0, 0, 255));
	   }
	 
	 
   }
   
   
   void clear(void)
   {
      al_set_target_backbuffer(display);
      al_clear_to_color(al_map_rgba(0, 0, 0, 255));
      al_flip_display();
   }
   
   ALLEGRO_DISPLAY *get_display(void)
   {
      return display;
   }
   
   
   private:
   
   ALLEGRO_DISPLAY *display;
   ALLEGRO_BITMAP *buffer;
   
   ALLEGRO_FONT *font;
   
   
   
};




class ConfigManagerClass
{
   
   ALLEGRO_CONFIG *cfg;

   
   public:

   ConfigManagerClass() : cfg(NULL)
   {
      

   }
   
   int load_config_file(const char *filename)
   {
      if(cfg != NULL)
	  {
	     return 2;
	  }
	  else
	  {
         cfg = al_load_config_file(filename);
		 
		 if( cfg == NULL )
		 {
		    return 1;
		 }
         else 
		 {
		    return 0;
		 }
      }
   }
   
   unsigned int get_integer(const char *key, int *return_state)
   {
      const char *string = NULL;
	  
      string = al_get_config_value( cfg, "", "number_of_distinct_factors");
    
	  if(string == NULL)
	  {
         *return_state = 1;
         return 0;
      }
      else
	  {
	     *return_state = 0;
	  }
      
   }
   
   


};
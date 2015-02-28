#include <allegro5/allegro5.h>
#include <vector>
#include <fstream>

#include "ONA_headers/ONA_setup.h"
#include "ONA_headers/ONA_make_table.h"



using namespace std;











int main(int argc, char *argv[])
{
   InitialisationClass init_class = InitialisationClass();
   DisplayClass display_class = DisplayClass();
   //vector<int> i_variables(0);
   ofstream log;
   int log_open = 1;                 /* Set this to 1 meaning log IS open, even though it isn't. Only set it to 0 if
                                        the log file can't be created. */
   ALLEGRO_CONFIG *cfg = NULL;
   
   ConfigManagerClass config_manager;
   
   ALLEGRO_EVENT_QUEUE *queue = NULL;
   ALLEGRO_EVENT event;
   
   int quit = 0;
   int i = 0;
   
   
   int job_done = 0;
   
   //cout << "At beginning of program.\n";
   
   log.open("odd_number_analysis_program_log.txt", ios_base::out);
   if( log.fail() )
   {
      log_open = 0;
   }
   
   if(log_open)
   {
      //cout << "Opened log.\n";
   }
   else
   {
      //cout << "Couldn't open log.\n";
   }
   
   if(log_open)
   {
      //cout << "Initialising Initialisation class from if(log_open) { }.\n";
      init_class = InitialisationClass(log);
      if(init_class.init_okay == 0)
      {
	     /* Either the call to al_install_system() or al_init_ttf_addon() failed. */
	     log.close();
		 wait_for_keypress();
         return 1;
      }
   }
   else
   {
      //cout << "Initialising Initialisation class from else { }.\n";
      init_class = InitialisationClass(0);
	  if(init_class.init_okay == 0)
      {
	     /* At this point - the log couldn't be opened and something in the initialisation failed so there's no way
		    to give an error. */
	     return 0;
      }
   }
   
   /* The allegro system is installed, true_type_font_addon installed... */
   
   if(log_open)
   {
      log.write("Initialising Display.\n", 23);
   }
   else
   {
      //cout << "Initialising Display Class.\n\n";
   }
   
   display_class = DisplayClass(0, log);
   
   
   //cout << "initialised DisplayClass.\n";
   
   if(log_open)
   {
	  if(display_class.init_okay != 1)
	  {
     	  log.write("Couldn't create the display. Aborting.\n", 41);
		  log.close();
		  wait_for_keypress();
		  return 0;
	  }
	  else
	  {
	     log.write("Successfully created the Display.\n", 36);
	  }
   }
   else
   {
      if(display_class.init_okay != 1)
	  {
	     //cout << "Couldn't create the display. Aborting.\n";
		 wait_for_keypress();
		 return 0;
	  }
	  else
	  {
	     //cout << "Successfully created the Display.\n";
	  }
   }
   
   
   display_class.clear();
   
   i = config_manager.load_config_file("odd_number_analyser_config_file.cfg");
   
   if( i == 1 ) /* Loading failed. */
   {
      if(log_open)
	  {
	     log.write("Unable to load configuration file.\n", 38);
		 log.close();
	  }
	  
	  return 1;
   }
   else
   {
      log.write("Loaded the configuration file.\n", 32); 
   }
   
   
   queue = al_create_event_queue();
   if(queue == NULL)
   {
      log.write("Failed to create the event queue in main. Aborting.\n", 43);
	  return 0;
   }
   
   
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(display_class.get_display()));
   
   //cout << "going into loop.\n";
   
   while(quit == 0)
   {
      //cout << "in loop.\n";
      al_wait_for_event(queue, &event);
	  //cout << "got event\n";
	  
	  
	  switch(event.type)
	  {
	     case ALLEGRO_EVENT_DISPLAY_CLOSE:
		     quit = 1;
			 break;
		 case ALLEGRO_EVENT_KEY_DOWN:
		     break;
	  }
	  
	  
	  if(job_done == 0)
	  {
	     cout << "Calling make_table.\n";
	     if( make_table(display_class, log, config_manager) != MAKE_TABLE_SUCCESS)
		 {
		 
		    ;
		 }
		 else
		 {
		    job_done = 1;
		 }
	  
	  }
	  
	  
   }
   
   
   
   
   
   
   
   log.close();
   return 0;
}











int wait_for_keypress()
{
   ALLEGRO_EVENT_QUEUE *queue = NULL;
   ALLEGRO_EVENT event; 

   
   queue = al_create_event_queue();
   if(queue == NULL)
   {
      return 0;
   }
   
   al_register_event_source(queue, al_get_keyboard_event_source());
   
   do
   {
      al_wait_for_event(queue, &event);
      
   } while( event.type != ALLEGRO_EVENT_KEY_DOWN );
   
   
   al_destroy_event_queue(queue);
   
   return 1;
}


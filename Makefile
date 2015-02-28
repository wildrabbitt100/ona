


# Odd Number Analysis Program Makefile

SOURCE = ONA_main.cpp                   \
         ONA_setup.cpp


OBJECT_FILES =  ONA_main.o              \
				ONA_setup.o				\
				ONA_make_table.o
				
				

				
				

LINKER_FLAGS = -static-libgcc -static-libstdc++ -lallegro-5.0.10-monolith-md-debug 

USE_CONSOLE_STRING = -mwindows

CPP_FLAGS = -Wall


odd_number_analysis_program.exe : $(OBJECT_FILES) Makefile
	g++ -g -o odd_number_analysis_program.exe $(OBJECT_FILES) $(LINKER_FLAGS) $(USE_CONSOLE_STRING)





ONA_main.o : 	ONA_main.cpp                  \
				ONA_headers/ONA_main.h        \
				ONA_headers/ONA_setup.h
				g++ -c ONA_main.cpp -o $@


			 

			 
ONA_setup.o : ONA_setup.cpp                 \
              ONA_headers/ONA_setup.h
				g++ -c ONA_setup.cpp -o $@
				

ONA_make_table.o :  ONA_make_table.cpp                \
					ONA_headers/ONA_make_table.h     \
					ONA_headers/ONA_setup.h          \
					ONA_headers/ONA.h                            
						g++ -c ONA_make_table.cpp -o $@
	
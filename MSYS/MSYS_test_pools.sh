 #!/bin/bash

BGreen='\033[1;32m' 
Color_Off='\033[0m'
 
#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____        ////////\n     /      \  |  o |        ////////\n    |        |/ ___\|        ////////\n    |_________/              ////////\n    |_|_| |_|_|              ////////\n/////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

 if gcc\
  -D _WIN32\
  -I /mingw64/include\
  -L /mingw64/lib\
  ../test/test_pools.c\
  ../source/bbAIControl.c\
  ../source/bbAIControl_init.c\
  ../source/bbDrawable.c\
  ../source/bbDrawable_plot.c\
  ../source/bbDrawable_lists.c\
  ../source/bbGroundSurface.c\
  ../source/bbMessage.c\
  ../source/bbMessage_constructors.c\
  ../source/bbMessage_functions.c\
  ../source/bbMessage_passing.c\
  ../source/bbNothing.c\
  ../source/bbTerrainSquare.c\
  ../source/geometry.c\
  ../source/input.c\
  ../source/interpolation.c\
  ../source/media.c\
  ../source/move_towards_deprecated.c\
  ../source/nelder_mead_deprecated.c\
  ../source/potential_fields_deprecated.c\
  ../source/prompt.c\
  ../source/viewport.c\
  ../source/window.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -w -lm;
  then
    echo "Compile Succeeded:"
    ./a.exe
  else 
    echo "Compile Failed!"
 #   exit
  fi
  
#done

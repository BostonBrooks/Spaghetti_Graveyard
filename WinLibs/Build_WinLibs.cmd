SET PATH=C:\winlibs\mingw64\bin
CD C:\Users\bbroo\CLionProjects\Spaghetti_Graveyard\WinLibs
gcc -D SFML_STATIC^
  ../test/main.c^
  ../source/bbAIControl.c^
  ../source/bbAIControl_init.c^
  ../source/bbDrawable.c^
  ../source/bbDrawable_plot.c^
  ../source/bbDrawable_lists.c^
  ../source/bbDrawable_click.c^
  ../source/bbGroundSurface.c^
  ../source/bbMessage.c^
  ../source/bbMessage_constructors.c^
  ../source/bbMessage_functions.c^
  ../source/bbMessage_passing.c^
  ../source/bbTerrainSquare.c^
  ../source/bbSkin.c^
  ../source/geometry.c^
  ../source/input.c^
  ../source/interpolation.c^
  ../source/media.c^
  ../source/move_towards_deprecated.c^
  ../source/nelder_mead_deprecated.c^
  ../source/potential_fields_deprecated.c^
  ../source/prompt.c^
  ../source/sum_forces.c^
  ../source/viewport.c^
  ../source/window.c^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -w -lm
a.exe


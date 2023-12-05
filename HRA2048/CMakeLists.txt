# CMakeList.txt: Projekt CMake pro HRA2048, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (HRA2048 "main.cpp" "2048.h" "2048.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HRA2048 PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.

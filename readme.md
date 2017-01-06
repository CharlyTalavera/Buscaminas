## Buscaminas - GUI

La interfaz del juego está alojada en el archivo `gui.c`. Para compilarlo es necesario tener instalado `Gtk+ 3`.
  Se puede verificar que versión de Gtk+ tenemos instalado con el comando `dpkg -l libgtk* | grep -e '^i' | grep -e 'libgtk-*[0-9]'`. Más precisamente necesitamos la liberia `libgtk-3-dev`.

  En caso de no estar instalado se puede instalar con `sudo apt-get install libgtk-3-dev`.

  El juego se compila con ``` gcc -Wall -Werror `pkg-config --cflags gtk+-3.0` *.c -o buscaminas `pkg-config --libs gtk+-3.0` ```

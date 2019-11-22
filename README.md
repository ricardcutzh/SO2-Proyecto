# Proyecto de Sistemas Operativos 2

* Ricardo Antonio Cutz Hernández
* 201503476

## Explicación
* El siguiente proyecto es una aplicación en C que permite observar los cambios que se realizan en la carpeta raíz. Esta aplicación observa y notifica si en caso se crea, elimina o modifica un archivo o carpeta llevando un archivo log de salida con cada uno de los cambios.

## Uso
1. Clonar el repositorio
```
$ git clone https://github.com/ricardcutzh/SO2-Proyecto.git
```

2. Compilar la aplicacion:
```
$ gcc Inotify.c -o Inotify
```

3. Correr la aplicacion:
```
# ./Inotify
```
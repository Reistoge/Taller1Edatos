# Taller1Edatos
 
# Sistema de Gestión de Biblioteca

## Descripción

Este proyecto es un sistema de gestión de biblioteca que permite administrar usuarios y materiales (libros y revistas) en una biblioteca. El sistema ofrece funcionalidades para agregar, buscar, prestar y devolver materiales, así como para gestionar usuarios.

## Funcionalidades

* Agregar materiales (libros y revistas) al sistema
* Buscar materiales por título, autor o ID
* Prestar materiales a usuarios
* Devolver materiales prestados
* Gestionar usuarios (agregar, buscar, eliminar)
* Mostrar información de materiales y usuarios

## Instrucciones de uso

1. Compilar el proyecto `g++ -g -o main .\MaterialBibliografico.cpp .\Revista.cpp .\Libro.cpp .\Usuario.cpp .\Impresora.cpp .\Sistema.cpp .\main.cpp`
2. ejecutar el archivo `main.exe`
3. Seleccionar una opción del menú principal:
	* Agregar material (1)
	* Mostrar información de materiales (2)
	* Buscar material (3)
	* Prestar material (4)
	* Devolver material (5)
	* Gestionar usuarios (6)
4. Seguir las instrucciones para cada opción seleccionada

## Requisitos

* Compilador C++ compatible con estándar C++11 o superior
* Sistema operativo compatible con archivos de texto (para leer y escribir archivos de configuración)

## Estructura del proyecto

* `Sistema.h`: archivo de cabecera que define la clase `Sistema`
* `Sistema.cpp`: archivo de implementación de la clase `Sistema`
* `main.cpp`: archivo principal que ejecuta el sistema
* `Impresora.h` y `Impresora.cpp`: archivos de cabecera e implementación de la clase `Impresora`, que se encarga de mostrar información en pantalla
* `Usuario.h` y `Usuario.cpp`: archivos de cabecera e implementación de la clase `Usuario`, que representa a un usuario del sistema
* `MaterialBibliografico.h` y `MaterialBibliografico.cpp`: archivos de cabecera e implementación de la clase `MaterialBibliografico`, que representa a un material (libro o revista) del sistema
* `Libro.h` y `Libro.cpp`: archivos de cabecera e implementación de la clase `Libro`, que hereda de `MaterialBibliografico` y representa a un libro
* `Revista.h` y `Revista.cpp`: archivos de cabecera e implementación de la clase `Revista`, que hereda de `MaterialBibliografico` y representa a una revista
* `Materiales.txt` y `Usuarios.txt`: almacenamiento y persistencia de los datos, dentro de cada txt se encuentra el formato para cada material y usuario. 

## Notas

* El sistema utiliza archivos de texto para almacenar la configuración y los datos de los usuarios y materiales.
* El sistema no tiene autenticación ni autorización, por lo que cualquier usuario puede acceder a todas las funcionalidades.

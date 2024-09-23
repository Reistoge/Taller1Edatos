
#include "Sistema.h"

void Sistema::readUsuarios(std::string filename)
{
    /*
    Lee un archivo de texto que contiene
    información de los usuarios y los agrega
    al sistema. El archivo debe tener un
    formato específico, donde cada línea
    representa un usuario y contiene su
    ID y nombre separados por punto y
    coma (;). Por ejemplo: id;nombre.
    */
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "no se pudo abrir el archivo";
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        crearUsuario(line);
        // process the line as needed
    }

    std::cout << "Se han cargado todos los usuarios" << std::endl;
    file.close();
}
void Sistema::readMateriales(std::string filename)
{
    /*
    Lee un archivo de texto que contiene información de materiales
    (libros y revistas) y los agrega al sistema. El archivo debe
    tener un formato específico, donde cada línea representa un
    material y contiene sus atributos separados por punto y coma(;).
    Por ejemplo: tipo;titulo;autor;
    */
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "no se pudo abrir el archivo";
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        agregarMaterial(line);
        // process the line as needed
    }

    std::cout << "Se han cargado todos los Materiales" << std::endl;
    file.close();
}
void Sistema::writeUsuarios(std::string filename)
{
    /*
    Escribe la información de los usuarios en un archivo de texto.
    Cada línea del archivo contiene la información
    de un usuario en formato id;nombre.
    */
    std::ofstream file(filename);
    if (!file)
    {
        std::cout << "No se pudo abrir el archivo";
        return;
    }

    for (int i = 0; i < numeroUsuarios; i++)
    {
        file << usuarios[i]->toString() << std::endl;
    }

    file.close();
}

void Sistema::writeMateriales(std::string filename)
{
    /*
    Escribe la información de los materiales en un archivo de texto.
    Cada línea del archivo contiene la informaciónn de un material
    en formato tipo;titulo;autor.;
    */
    std::ofstream file(filename);
    if (!file)
    {
        std::cout << "No se pudo abrir el archivo";
        return;
    }

    for (int i = 0; i < numeroMateriales; i++)
    {
        file << biblioteca[i]->toString() << std::endl;
    }

    file.close();
}

bool Sistema::agregarMaterial(std::string input)
{
    /*
    Agrega un material al sistema. El parámetro input es
    una cadena que contiene la información del material
    en formato tipo;titulo;autor;...
    La función verifica si el material ya existe en el
    sistema y si el tipo de material es válido (libro o revista).
    Si todo es correcto, crea un objeto MaterialBibliografico
    correspondiente y lo agrega al sistema.
    */
    std::vector<std::string> attributes = split(input, ';');
    std::string type = attributes[0];
    std::string nombre = attributes[1];

    if ((attributes.size() < 7) && (this->numeroMateriales <= MAX_BIBLIOTECA))
    {
        std::cout << "\nInput invalido\n";
        return false;
    }
    if (existeMaterial(type, nombre))
    {
        std::cout << "\nEl material ya existe en la biblioteca\n";
        return false;
    }

    if (toLowercase(type) == "libro")
    {
        try
        {
            MaterialBibliografico *libro = new Libro(attributes[1], attributes[2], attributes[3], attributes[4], attributes[5], attributes[6]);
            if (toLowercase(attributes[4]) != "disponible")
            {
                Usuario *u = getUsuario(attributes[4]);
                if (u != nullptr)
                {
                    u->prestarMaterial(libro);
                }
                else
                {

                    return false;
                }
            }
            this->numeroLibros++;
            this->numeroMateriales++;
            this->biblioteca[this->numeroMateriales - 1] = libro;
            this->libros[this->numeroLibros - 1] = dynamic_cast<Libro *>(libro);
            return true;
        }
        catch (const std::exception &e)
        {

            return false;
        }
    }
    else if (toLowercase(type) == "revista")
    {
        try
        {
            MaterialBibliografico *revista = new Revista(attributes[1], attributes[2], attributes[3], attributes[4], std::stoi(attributes[5]), attributes[6]);
            if (toLowercase(attributes[4]) != "disponible")
            {
                Usuario *u = getUsuario(attributes[4]);
                if (u != nullptr)
                {
                    u->prestarMaterial(revista);
                }
                else
                {
                    return false;
                }
            }
            this->numeroRevistas++;
            this->numeroMateriales++;
            this->biblioteca[this->numeroMateriales - 1] = revista;
            this->revistas[this->numeroRevistas - 1] = dynamic_cast<Revista *>(revista);
            return true;
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }
    return false;
};
bool Sistema::existeMaterial(std::string tipo, std::string titulo)
{
    /*
    Verifica si un material con el título y tipo especificados
    existen en el sistema.
    */
    MaterialBibliografico *m = getMaterial(titulo);
    if (m != nullptr)
    {
        // si existe el material

        if (toLowercase(m->getTipo()) == toLowercase(tipo))
        {
            // y es del mismo tipo entonces ya existe

            return true;
        }
        else
        {
            // es distinto tipo entonces no existe

            return false;
        }
    }
    else
    {
        // si no existe entonces retorna false;
        return false;
    }
}
Sistema::Sistema()
{
    for (int i = 0; i < MAX_BIBLIOTECA; i++)
    {
        // initialize sistem;
        biblioteca[i] = nullptr;
        usuarios[i] = nullptr;
        this->numeroMateriales = 0;
        this->numeroLibros = 0;
        this->numeroRevistas = 0;
        this->numeroUsuarios = 0;
    }
}
void Sistema::mostrarInfoMateriales()
{
    /*
    Muestra la información de todos los
    materiales en el sistema, separados
    por tipo (libros y revistas).
    */
    std::cout << "REVISTAS: \n\n";
    for (int i = 0; i < this->numeroRevistas; ++i)
    {
        this->revistas[i]->mostrarInformacion();
        std::cout << "\n";
    }

    std::cout << "\nLIBROS:  \n\n";
    for (int i = 0; i < this->numeroLibros; ++i)
    {
        this->libros[i]->mostrarInformacion();
        std::cout << "\n";
    }
};
bool Sistema::buscarMaterial(std::string input)
{
    /*
    Busca un material en el sistema según un campo y valor especificados
    en la cadena input. Por ejemplo, autor;nombreAutor o titulo;tituloDelLibro.
    Si se encuentra el material, muestra su información.
    */
    std::vector<std::string> attributes = split(input, ';');
    // Split the input string into substrings separated by commas

    std::string campo = attributes[0];
    std::string valor = attributes[1];
    bool encontrado = false;
    if (campo == "autor")
    {
        for (int i = 0; i < this->numeroMateriales; i++)
        {
            if (biblioteca[i]->getAutor() == valor)
            {
                biblioteca[i]->mostrarInformacion();
                encontrado = true;
            }
        }
        return encontrado;
    }
    else if (campo == "titulo")
    {
        for (int i = 0; i < this->numeroMateriales; i++)
        {
            if (toLowercase(biblioteca[i]->getTitulo()) == toLowercase(valor))
            {
                biblioteca[i]->mostrarInformacion();
                encontrado = true;
            }
        }
        return encontrado;
    }
    else
    {

        return false;
    }
}

MaterialBibliografico *Sistema::getMaterial(std::string idMaterial)
{
    /*
    Busqueda lineal por el array biblioteca el cual coniene todos los materiales
    si uno de los materiales coincide con el titulo lo retorna.
    */
    for (int i = 0; i < numeroMateriales; i++)
    {
        if (toLowercase(biblioteca[i]->getTitulo()) == toLowercase(idMaterial))
        {

            return biblioteca[i];
        }
    }
    return nullptr;
}
Usuario *Sistema::getUsuario(std::string idUsuario)
{
    /*
    Busqueda lineal para buscar a un usuario segun id, recorre el array
    de usuarios hasta coincidir con el  id del usuario buscado si es asi retorna el puntero.

    */
    for (int i = 0; i < numeroUsuarios; i++)
    {
        if (toLowercase(usuarios[i]->getId()) == toLowercase(idUsuario))
        {
            return usuarios[i];
        }
    }
    return nullptr;
}
bool Sistema::prestarMaterial(std::string idUsuario, std::string infoMaterial)
{
    /*
    Presta un material a un usuario. Verifica si el usuario y el material existen
    en el sistema y si el usuario no tiene más de 5 materiales prestados. Si todo
    es correcto, actualiza el estado del material y del usuario.

    */
    MaterialBibliografico *material = getMaterial(infoMaterial);
    Usuario *usuario = getUsuario(idUsuario);
    if (material != nullptr && usuario != nullptr && usuario->getNumerosMaterialesEnUso() < 5 && (material->getUsuarioDelMaterial() == nullptr && material->getIsPrestado() == "disponible"))
    {
        usuario->prestarMaterial(material);
        return true;
    }
    else
    {
        return false;
    }
};

bool Sistema::devolverMaterial(std::string idUsuario, std::string infoMaterial)
{
    // se busca al usuario segun  el id y el material segun su titulo.

    // busca el material a eliminar y cambia su estado a disponible dereferenciando el atributo usuarioDelMaterial
    // asimismo deferencia el material de la lista de materialesEnUso del usuario a buscar
    // retorna true si  se pudo devolver el material, false en caso contrario.

    MaterialBibliografico *material = getMaterial(infoMaterial);
    Usuario *usuario = getUsuario(idUsuario);
    if (material != nullptr && usuario != nullptr && material->getUsuarioDelMaterial() != nullptr && material->getIsPrestado() != "disponible")
    {
        usuario->devolverMaterial(material);
        return true;
    }
    else
    {
        return false;
    }
};

bool Sistema::crearUsuario(std::string input)
{
    /*
    Crea un nuevo usuario en el sistema.
    El parámetro input es una cadena que contiene la información
    del usuario en formato id;nombre
    */

    std::vector<std::string> attributes = split(input, ';');
    // Split the input string into substrings separated by commas

    if (attributes.size() == 2 && numeroUsuarios < MAX_BIBLIOTECA && getUsuario(attributes[0]) == nullptr)
    {
        Usuario *usuario = new Usuario(attributes[0], attributes[1]);

        usuarios[numeroUsuarios] = usuario;
        numeroUsuarios++;
        return true;
    }
    else
    {
        return false;
    }
}
bool Sistema::eliminarUsuario(std::string input)
{
    // recorrer la lista de usuarios linealmente hasta encontrar
    // el usuario que coincida con el id, hacer que sus materiales
    // prestados  vuelvan a estar disponibles para despues
    // eliminarlo y ordenar la lista

    bool found = false;
    int index;
    Usuario *usuario = getUsuario(input);
    if (usuario != nullptr)
    {
        for (int i = 0; i < MAX_BIBLIOTECA; i++)
        {
            if (found == false && usuarios[i]->getId() == usuario->getId())
            {
                // if is found , set to nullptr
                numeroUsuarios--;
                usuarios[i]->devolverMateriales();
                delete usuarios[i];
                usuarios[i] = nullptr;
                found = true;
                index = i;
                continue;
            }
            if (found)
            {
                if (i == MAX_BIBLIOTECA - 1)
                { // last element
                    usuarios[i] = nullptr;
                    break;
                }
                // reorder the array;
                usuarios[i] = usuarios[i + 1];
                usuarios[i + 1] = nullptr;
            }
        }
        return true;
    }
    return false;
}
std::string Sistema::buscarUsuarioPorNombre(std::string input)
{
    // recorrer la ista de usuarios linealmente hasta encontrar
    //  los usuario con nombre que  coincida con el input e ir
    //  almacenando su info en un string para despues retornalo.

    std::string response = "";
    response += "BUSCANDO USUARIOS DE NOMBRE " + input + "\n";
    for (int i = 0; i < numeroUsuarios; i++)
    {
        if (usuarios[i]->getNombre() == input)
        {
            response += "\nUSUARIO ENCONTRADO: " + usuarios[i]->getInfo();
        }
    }
    if (response == "")
    {
        response += "NO SE HAN ENCONTRADO USUARIOS CON ESE NOMBRE.";
    }
    return response;
}
std::string Sistema::mostrarTodosUsuarios()
{
    std::string response = "";
    response += "LISTADO DE TODOS LOS USUARIOS REGISTRADOS\n";
    for (int i = 0; i < numeroUsuarios; i++)
    {
        response += "\nUSUARIO ENCONTRADO: " + usuarios[i]->getInfo();
    }
    if (response == "")
    {
        response += "NO SE HAN ENCONTRADO USUARIOS REGISTRADOS.";
    }
    return response;
}
std::string Sistema::buscarUsuarioPorID(std::string input)
{
    // recorrer la ista de usuarios linealmente hasta encontrar
    //  el usuario con id que coincida con el input e ir
    //  almacenando su info en un string para despues retornalo.
    std::string response = "";
    response += "BUSCANDO USUARIOS DE ID " + input + "\n";
    Usuario *usuario = getUsuario(input);
    if (usuario != nullptr)
    {
        response += "USUARIO ENCONTRADO: " + usuario->getInfo();
    }
    else
    {
        response += "USUARIO NO ENCONTRADO";
    }
    return response;
}
std::string Sistema::buscarUsuarioHandler(std::string input)
{
    if (!input.empty())
    {
        std::vector<std::string> attributes = split(input, ';');
        if (toLowercase(attributes[0]) == "id")
        {
            return buscarUsuarioPorID(attributes[1]);
        }
        else if (toLowercase(attributes[0]) == "nombre")
        {
            return buscarUsuarioPorNombre(attributes[1]);
        }
        return "";
    }
    return "";
}

std::vector<std::string> Sistema::split(std::string word, char key)
{

    std::vector<std::string> attributes;
    if (!word.empty())
    {
        std::string token;
        size_t pos = 0;
        while ((pos = word.find(key)) != std::string::npos)
        {

            token = word.substr(0, pos);
            token.erase(0, token.find_first_not_of(" \t")); // trim leading whitespace
            token.erase(token.find_last_not_of(" \t") + 1); // trim trailing whitespace
            attributes.push_back(token);
            word.erase(0, pos + 1);
        }
        // handle the last token (if it's not empty)
        if (!word.empty())
        {
            token = word;
            token.erase(0, token.find_first_not_of(" \t")); // trim leading whitespace
            token.erase(token.find_last_not_of(" \t") + 1); // trim trailing whitespace
            attributes.push_back(token);
        }
    }
    return attributes;
}

std::string Sistema::toLowercase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return str;
}
void Sistema::leerDatos()
{
    readUsuarios("Usuarios.txt");
    readMateriales("Materiales.txt");
}
void Sistema::guardarDatos()
{
    writeUsuarios("Usuarios.txt");
    writeMateriales("Materiales.txt");
    std::cout << "se han guardado los cambios";
}
void Sistema::start()
{
    Impresora *impr = new Impresora();
    leerDatos();

    std::string input; // input  del usuario
    std::string enter; // input vacio o temporal, no importa lo que contenga
    bool repetir = false;

    while (input != "7")
    {

        // mostramos el menu siempre que la opcion sea distinta a 7
        impr->menu();
        if (repetir == false)
        {
            // si no queremos repetir la opcion, preguntamos al usuario el input.
            getline(std::cin, input);
        }

        // "if´s de opciones"
        if (input == "1")
        {
            // opcion 1: agregar Material
            impr->showAgregarMaterial();

            getline(std::cin, input);
            try
            {
                bool inputValido = !input.empty() && agregarMaterial(input);
                if (inputValido)
                {
                    std::cout << "Material " << input << "\nfue agregado correctamente" << std::endl;
                }
                else
                {
                    std::cout << "No se puede agregar el material " << input << std::endl;
                }
            }
            catch (const std::exception &e)
            {
                // hay un bug/error cuando se intenta hacer un split de un input especifico.
                std::cout << "No se puede agregar el material " << input << std::endl;
            }

            // seccion para repetir opción.
            std::cout << "desea agregar otro material? (si / no)" << std::endl;
            std::getline(std::cin, input);
            std::cout << input << std::endl;
            if (input == "si")
            {
                repetir = true;
                input = "1";
            }
            else
            {
                repetir = false;
                input = "";
            }
        }
        else if (input == "2")
        {
            //  opcion 2: mostrar Informacion
            impr->showMostrarInformacion();
            mostrarInfoMateriales();
            std::cout << "\nPresione cualquier tecla para continuar\n";
            getline(std::cin, enter);
        }
        else if (input == "3")
        {
            // opcion 3: buscar Material
            impr->showBuscarMaterial();

            getline(std::cin, input);

            bool inputValido = input.empty() || buscarMaterial(input) == false;
            if (inputValido)
            {
                std::cout << "El material " << input << " no existe en el sistema." << std::endl;
            }

            // sección para repetir opción
            std::cout << "desea buscar otro material? (si / no)" << std::endl;
            getline(std::cin, input);
            std::cout << input << std::endl;
            if (input == "si")
            {

                repetir = true;
                input = "3";
            }
            else
            {
                repetir = false;
                input = "";
            }
        }
        else if (input == "4")
        {
            // opcion 4: prestar Material
            impr->showPrestarMaterial();
            getline(std::cin, input);
            std::vector<std::string> inputPartes = split(input, ';');
            bool inputValido = !inputPartes.empty() && inputPartes.size() == 2 && prestarMaterial(inputPartes[0], inputPartes[1]) == true;
            if (inputValido)
            {
                std::cout << " El material " << inputPartes[1] << " se presto correctamente hacia el usuario " << inputPartes[0] << std::endl;
            }
            else
            {
                std::cout << "Hubieron problemas prestando el material, introduce correctamente la informacion" << std::endl;
            }

            // sección para repetir opción
            std::cout << "desea prestar otro material? (si / no)" << std::endl;
            getline(std::cin, input);
            std::cout << input << std::endl;
            if (input == "si")
            {
                repetir = true;
                input = "4";
            }
            else
            {
                repetir = false;
                input = "";
            }
        }
        else if (input == "5")
        {
            // opcion 5:  devolver material
            impr->showDevolverMaterial();
            getline(std::cin, input);
            std::vector<std::string> inputPartes = split(input, ';');
            bool inputvalido = !inputPartes.empty() && inputPartes.size() == 2 && devolverMaterial(inputPartes[0], inputPartes[1]) == true;
            if (inputvalido)
            {
                std::cout << " El material " << inputPartes[0] << " se ha devuelto correctamente del usuario " << inputPartes[1] << std::endl;
            }
            else
            {
                std::cout << "hubieron problemas devolviendo el material, introduce correctamente la información" << std::endl;
            }

            //  sección para repetir opción
            std::cout << "desea devolver otro material? (si / no)" << std::endl;
            getline(std::cin, input);
            std::cout << input << std::endl;
            if (input == "si")
            {
                repetir = true;
                input = "5";
            }
            else
            {
                repetir = false;
                input = "";
            }
        }
        else if (input == "6")
        {
            // opcion 6:  gestor usuarios
            impr->showGestionUsuarios();
            getline(std::cin, input);
            // subOpcion 1:  crear usuario
            if (input == "1")
            {
                impr->showCrearUsuario();
                getline(std::cin, input);
                if (!input.empty() && crearUsuario(input))
                {
                    std::cout << "se ha creado exitosamente el usuario " << input << std::endl;
                }
                else
                {
                    std::cout << "Hubieron errores creando al usuario " << std::endl;
                }
            }
            // subOpcion 2:  buscar usuario
            else if (input == "2")
            {
                impr->showBuscarUsuario();
                getline(std::cin, input);
                std::string informacion = buscarUsuarioHandler(input);
                if (informacion != "")
                {
                    std::cout << informacion;
                }
                else
                {
                    std::cout << "Hubieron problemas buscando al usuario, introduce correctamente la informacion" << std::endl;
                }
            }
            // subOpcion 3:  eliminar usuario
            else if (input == "3")
            {
                impr->showEliminarUsuario();
                getline(std::cin, input);
                bool opcionValida = !input.empty() && eliminarUsuario(input);
                if (opcionValida)
                {
                    std::cout << "\nUsuario de ID: " << input << " ha sido eliminado correctamente" << std::endl;
                }
                else
                {
                    std::cout << "Hubieron problemas de formato, no se pudo eliminar al usuario" << std::endl;
                }
            }
            else if (input == "4")
            {
                std::cout<<mostrarTodosUsuarios();
            }
        }
    }

    std::cout << "\nSaliendo del programa..\n";
    std::cout << "Desea guardar los datos ?\n";
    std::cout << "   1. Si\n";
    std::cout << "   2. No\n";
    getline(std::cin, input);
    if (input == "1" || toLowercase(input) =="si")
    {
        guardarDatos();
    }
    delete impr;
}
Sistema::~Sistema()
{
    // Delete each element in the biblioteca array
    for (int i = 0; i < 100; i++)
    {
        if (biblioteca[i] != nullptr)
        {
            delete biblioteca[i];
        }
    }
    delete[] biblioteca;

    // Delete the biblioteca array

    // Delete each element in the usuarios array
    for (int i = 0; i < 100; i++)
    {
        if (usuarios[i] != nullptr)
        {
            delete usuarios[i];
        }
    }
    // Delete the usuarios array
    delete[] usuarios;
}

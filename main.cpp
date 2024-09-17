
#include "Sistema.h"
//#include "Impresora.h"

using namespace std;

int main()
{

    // se instancia el sistema con la impresora.
    Sistema *sistema = new Sistema();
    //sistema->start();
    Impresora *impr = new Impresora();
    sistema->leerDatos();

    string input; // input  del usuario
    string enter; // input vacio o temporal, no importa lo que contenga
    bool repetir = false;

    while (input != "7")
    {

        // mostramos el menu siempre que la opcion sea distinta a 7
        impr->menu();
        if (repetir == false)
        {
            // si no queremos repetir la opcion, preguntamos al usuario el input.
            getline(cin, input);
        }

        // "if´s de opciones"
        if (input == "1")
        {
            // opcion 1: agregar Material
            impr->showAgregarMaterial();

            getline(cin, input);
            try
            {
                bool inputValido = !input.empty() && sistema->agregarMaterial(input);
                if (inputValido)
                {
                    cout << "Material " << input << "\nfue agregado correctamente" << endl;
                }
                else
                {
                    cout << "No se puede agregar el material " << input << endl;
                }
            }
            catch (const std::exception &e)
            {
                // hay un bug/error cuando se intenta hacer un split de un input especifico.
                cout << "No se puede agregar el material " << input << endl;
            }

            // seccion para repetir opción.
            cout << "desea agregar otro material? (si / no)" << endl;
            getline(cin, input);
            cout << input << endl;
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
            sistema->mostrarInfoMateriales();
            std::cout << "\nPresione cualquier tecla para continuar\n";
            getline(cin, enter);
        }
        else if (input == "3")
        {
            // opcion 3: buscar Material
            impr->showBuscarMaterial();

            getline(cin, input);

            bool inputValido = input.empty() || sistema->buscarMaterial(input) == false;
            if (inputValido)
            {
                cout << "El material " << input << " no existe en el sistema." << endl;
            }

            // sección para repetir opción
            cout << "desea buscar otro material? (si / no)" << endl;
            getline(cin, input);
            cout << input << endl;
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
            getline(cin, input);
            vector<string> inputPartes = sistema->split(input, ';');
            bool inputValido = !inputPartes.empty() && inputPartes.size() == 2 && sistema->prestarMaterial(inputPartes[0], inputPartes[1]) == true;
            if (inputValido)
            {
                cout << " El material " << inputPartes[1] << " se presto correctamente hacia el usuario " << inputPartes[0] << endl;
            }
            else
            {
                cout << "Hubieron problemas prestando el material, introduce correctamente la informacion" << endl;
            }

            // sección para repetir opción
            cout << "desea prestar otro material? (si / no)" << endl;
            getline(cin, input);
            cout << input << endl;
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
            getline(cin, input);
            vector<string> inputPartes = sistema->split(input, ';');
            bool inputvalido = !inputPartes.empty() && inputPartes.size() == 2 && sistema->devolverMaterial(inputPartes[0], inputPartes[1]) == true;
            if (inputvalido)
            {
                cout << " El material " << inputPartes[0] << " se ha devuelto correctamente del usuario " << inputPartes[1] << endl;
            }
            else
            {
                cout << "hubieron problemas devolviendo el material, introduce correctamente la informacion" << endl;
            }

            //  sección para repetir opción
            cout << "desea devolver otro material? (si / no)" << endl;
            getline(cin, input);
            cout << input << endl;
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
            getline(cin, input);
            // subOpcion 1:  crear usuario
            if (input == "1")
            {
                impr->showCrearUsuario();
                getline(cin, input);
                if (!input.empty() && sistema->crearUsuario(input))
                {
                    cout << "se ha creado exitosamente el usuario " << input << endl;
                }
                else
                {
                    cout << "Hubieron errores creando al usuario " << endl;
                }
            }
            // subOpcion 2:  buscar usuario
            else if (input == "2")
            {
                impr->showBuscarUsuario();
                getline(cin, input);
                std::string informacion = sistema->buscarUsuarioHandler(input);
                if (informacion != "")
                {
                    cout << informacion;
                }
                else
                {
                    cout << "Hubieron problemas buscando al usuario, introduce correctamente la informacion" << endl;
                }
            }
            // subOpcion 3:  eliminar usuario
            else if (input == "3")
            {
                impr->showEliminarUsuario();
                getline(cin, input);
                bool opcionValida = !input.empty() && sistema->eliminarUsuario(input);
                if (opcionValida)
                {
                    cout << "\nUsuario de ID: " << input << " ha sido eliminado correctamente" << endl;
                }
                else
                {
                    cout << "Hubieron problemas de formato, no se pudo eliminar al usuario" << endl;
                }
            }
        }
    }

    cout << "\nSaliendo del programa..\n";
    cout << "Desea guardar los datos ?\n";
    cout << "   1. Si\n";
    cout << "   2. No\n";
    getline(cin, input);
    if (input == "1")
    {
        sistema->guardarDatos();
    }
    delete impr;
    delete sistema;
    return 0;
}

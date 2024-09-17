
#include "Sistema.h"
//#include "Impresora.h"

using namespace std;

int main()
{

    // se instancia el sistema con la impresora.
    Sistema *sistema = new Sistema();
    sistema->start();
     
    delete sistema;
    return 0;
}

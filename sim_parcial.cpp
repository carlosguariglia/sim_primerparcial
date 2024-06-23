/*
ENUNCIADO
Una Empresa que vende “productos de seguridad industrial NicTech” nos convoca para la realización
de una App que permita registrar los Pedidos de Artículos de los clientes.

En esta etapa del desarrollo, solo deberemos realizar el módulo “Clientes”

La misma debe permitir:

Gestionar los Clientes
Dar de alta el cliente (el código del cliente se obtiene sumando 100 al índice del Array).
Dar de Baja los clientes x código de cliente.
Modificar los clientes, ingresar el código, mostrarlo y editarlo.
Listar los Clientes.
Listar todos los Clientes.
Buscar un Clientes x código y mostrarlo (imprimir cartel de no encontrado).
.  Todo esto mediante un Menú, Modularizando en Funciones, utilizando Archivos, arreglos y estructuras.


NOTA IMPORTANTE: (personal no parte del enunciado)
    por una cuestion de simplificar el manejo de datos se usaran solo strings simples sin espacios
    ej nombre valido = Juan, no valido Juan Perez
    lo mismo que el nombre de la ciudad: valido = Mardel y no valido = Mar del plata

    el manejo de nombres con mas de una palabra se puede implementar pero hay que guardar los datos 
    al archivo de alguna manera especial para que no se pierda la informacion.
    ahora para simplificar esta guardados con una separacion de espacio entre los campos de la estructura
    ej
    codigo nombre ciudad
    123 Juan Mardel

    */

#include <iostream>                 // libreria para cin y cout
#include <fstream>                  // libreria para manejo de archivos
using namespace std;                // simplifica el uso de cout y cin para no usar std::cout y std::cin

const int MAX_CUSTOMERS = 100;  // Constante global para el maximo de clientes (se usara para el array)

struct Customer         // Estructura de Clientes (codigo, nombre, ciudad)
{
    int code;
    string name;
    string city;
};

struct Container        // Estructura de Contenedor (array de clientes y numero de clientes=tamano del array)
{
    Customer customers[MAX_CUSTOMERS];
    int numCustomers;
};

void loadFromfile(Container &ListaClientes);    // Carga los datos del archivo al contenedor (array)
void saveToFile(Container &ListaClientes);      // Guarda los datos del contenedor (array) al archivo
void addCustomer(Container &ListaClientes);     // Función para dar de alta un cliente
void removeCustomer(Container &ListaClientes);  // Función para dar de baja un cliente
void updateCustomer(Container &ListaClientes);  // Función para modificar un cliente
void listCustomers(Container const &ListaClientes);   // Función para listar todos los clientes (se le pasa como const para que no se pueda modificar)
void findCustomer(Container const &ListaClientes);    // Función para buscar un cliente por código e imprimirlo (Se le pasa como const para que no se pueda modificar)
void clearConsole();                        // Limpia la consola
void pauseConsole();                        // Pausa la consola y pide presionar ENTER para continuar

int main() 
{   
    clearConsole();                         // Limpia la consola todos lo usos de clearConsole() y pauseConsole() usados en el 
                                            //  programa son de uso opcional y estan puesto para una mejor presentación.        
    
    int menu;                               // variable usada para el menú principal
    
    Container ListaClientes;                    // variable para el contenedor (podria haber tenido cualquier otro nombre nomina, Listaclientes) 
    ListaClientes.numCustomers = 0;             // inicializo la cantidad de clientes a cero
    
    loadFromfile(ListaClientes);                // Carga los datos del archivo al contenedor ListaClientes

    do 
    {
        cout << "-------------- MENÚ --------------" << endl;
        cout << "1. Dar de alta un cliente" << endl;
        cout << "2. Dar de baja un cliente" << endl;
        cout << "3. Modificar un cliente" << endl;
        cout << "4. Listar todos los clientes" << endl;
        cout << "5. Buscar un cliente por código" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> menu;                                     // lee una opcion del menu (un entero)
        switch (menu)                                    // el SWITCH evalua el valor del entero y ejecuta el CASE correspondiente
        {
            case 1: 
            {   addCustomer(ListaClientes);              // llama a la funcion para dar de alta un cliente pasandole la variable ListaClientes
                break;
            }
            case 2: 
            {   removeCustomer(ListaClientes);          // llama a la funcion para dar de baja un cliente pasandole la variable ListaClientes
                break;
            }
            case 3: 
            {   updateCustomer(ListaClientes);          // llama a la funcion para modificar un cliente pasandole la variable ListaClientes
                break;
            }
            case 4: 
            {   listCustomers(ListaClientes);           // llama a la funcion para mostrar todos los clientes pasandole la variable ListaClientes
                break;
            }
            case 5: 
            {   findCustomer(ListaClientes);            // llama a la funcion para buscar un cliente por código e imprimirlo (Se le pasa como const para que no se pueda modificar)
                break;
            }
            case 6: 
            {   saveToFile(ListaClientes);              // Guarda los datos de la ListaClientes al archivo
                cout << "Saliendo..." << endl;          // esta operacion se realiza antes de salir del programa
                break;
            }
            default:                                    // la opcion de default es para cuando el usuario ingresa una opcion que no
            {   cout << "Opción invalida" << endl;      // corresponde a ningun CASE que hallamos definido
                pauseConsole();
                break;
            }
        }

    }while (menu != 6);                                 // mientras la variable menu no sea igual a 6, el programa se ejecuta 
    return 0;                                           // si es igual a 6 termina el bucle do-while
} 

void loadFromfile(Container &ListaClientes) 
{
    ifstream file("customers.txt");
    if (file.is_open()) 
    {
        while (!file.eof())                                 // leo los demas elementos hasta el fin del archivo (eof = end of file) 
        {
            file >> ListaClientes.customers[ListaClientes.numCustomers].code >> ListaClientes.customers[ListaClientes.numCustomers].name >> ListaClientes.customers[ListaClientes.numCustomers].city;
            ListaClientes.numCustomers++;                       // cada vez que leo un elemento, aumento el contador de clientes
        }
        file.close();
    } 
    else 
    {
        cout << "No se pudo abrir el archivo." << endl;                     // si no se pudo abrir el archivo porque no existe, crea uno nuevo
        cout << "Desea crear un nuevo archivo? (1 = si, 0 = no)" << endl;   // pregunta si se quiere crear un nuevo archivo
        int opcionNuevoArchivo;                                             // variable para guardar la respuesta
        cin >> opcionNuevoArchivo;
        if (opcionNuevoArchivo == 1)                                        // si la respuesta es 1 crea el archivo
        {       
            ofstream file("customers.txt");
            file.close();
            cout << "Archivo creado correctamente." << endl;
        } 
        else                                                                // si la respuesta es 0 termina el programa
        {
            cout << "Saliendo..." << endl;
            pauseConsole();
            exit(1);                                                        // sale del programa devolviendo un 1 marcando error
        }
        
    }
}   

void saveToFile(Container &ListaClientes)
{
    ofstream file("customers.txt");
    if (file.is_open())                         // funcion interna del fstream para abrir el archivo devuelve true si se pudo abrir
    {   
        if (ListaClientes.numCustomers != 0) // si la lista es distinta de cero entonces procedo a guardar
        {
            /* Guardo los clientes al archivo menos el ultimo, y luego 
            guardo el ultimo sin usar endl para que no agregue una fila mas al archivo*/
            for (int i = 0; i < ListaClientes.numCustomers-1; i++) 
            {
                file << ListaClientes.customers[i].code << " " << ListaClientes.customers[i].name << " " << ListaClientes.customers[i].city << endl;
            }
            /* Guardo el ultimo cliente sin endl para que no agregue una fila mas al archivo*/
            file << ListaClientes.customers[ListaClientes.numCustomers-1].code << " " << ListaClientes.customers[ListaClientes.numCustomers-1].name << " " << ListaClientes.customers[ListaClientes.numCustomers-1].city;
            file.close();
        }
        else        // si la lista es cero no hay clientes para guardar por lo que no se hace nada para evitar guardar basura
        {
            file.close();
        }
    }
    else            // si el archivo no se pudo abrir para escritura al dar file.is_open() = false
    {
        cout << "No se pudo Guardar el archivo." << endl;
        pauseConsole();
    }
}

void addCustomer(Container &ListaClientes) 
{   
    clearConsole();
    Customer newCustomer;                   // se crea un nuevo cliente

    if (ListaClientes.numCustomers == 0)    // si hay 0 clientes empieza con el 100
    {   
        newCustomer.code = 100;
    }
    else
    {
        newCustomer.code = (ListaClientes.customers[ListaClientes.numCustomers - 1].code) + 1;  // si ya hay clientes se le suma 1 al ultimo
    }
    
    if (!(ListaClientes.numCustomers >= MAX_CUSTOMERS))   // se verifica que haya lugar para el nuevo cliente
    {   
        cout << "Ingrese el nombre del cliente: ";
        cin >> newCustomer.name; 
        cout << "Ingrese la ciudad del cliente: ";
        cin >> newCustomer.city;
                
        ListaClientes.customers[ListaClientes.numCustomers] = newCustomer;        
        ListaClientes.numCustomers++;
        cout << "Cliente agregado correctamente." << endl;
        pauseConsole();
        clearConsole();
    } 
    else   // al ser la cantidad de numCustomers mayor o igual a MAX_CUSTOMERS no se puede agregar mas clientes
    {
        cout << "No se pueden agregar más clientes. Maximo alcanzado." << endl;
        pauseConsole();
        clearConsole();
    }
}

void removeCustomer(Container &ListaClientes) 
{
    int code;                                                   // variable para pedir el codigo que se quiere borrar
    cout << "Ingrese el código del cliente a dar de baja: ";    
    cin >> code;    
    clearConsole();
    for (int i = 0; i < ListaClientes.numCustomers; i++)        // busca el cliente en la lista desde 0 hasta la cantidad de clientes
    {
        if (ListaClientes.customers[i].code == code)            // si lo encuentro
        {
            for (int j = i; j < ListaClientes.numCustomers - 1; j++)     // este for recorre desde el lugar que se encontro (i) ahora asignado a j hasta la cantidad total de clientes menos 1
            {
                ListaClientes.customers[j] = ListaClientes.customers[j + 1];  // se le asigna a la posicion que se borro el valor de la posicion siguiente
            }
            ListaClientes.numCustomers--;           // se le resta uno a la cantidad de clientes
            cout << "Cliente eliminado correctamente." << endl;
            pauseConsole();
            clearConsole();
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}   

void updateCustomer(Container &ListaClientes) 
{
    int code;                                       // variable para buscar el cliente por su codigo
    cout << "Ingrese el código del cliente a modificar: ";
    cin >> code;
    clearConsole();
    for (int i = 0; i < ListaClientes.numCustomers; i++)    // se busca el cliente desde 0 hasta la cantidad de clientes 
    {
        if (ListaClientes.customers[i].code == code)    // si lo encuentra se imprime y luego se piden los datos para sobreescibirlos
        {
            cout << "El cliente a modificar es: " << endl;
            cout << endl;
            cout << "Código: " << ListaClientes.customers[i].code << endl;
            cout << "Nombre: " << ListaClientes.customers[i].name << endl;
            cout << "Ciudad: " << ListaClientes.customers[i].city << endl;
            cout << endl;

            cout << "Ingrese el nuevo nombre del cliente: ";
            cin >> ListaClientes.customers[i].name;
            cout << "Ingrese la nueva ciudad del cliente: ";
            cin >> ListaClientes.customers[i].city;
            cout << "Cliente modificado correctamente." << endl;
            pauseConsole();
            clearConsole();
            return;                             // sale de la funcion (sin retornar nada)
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

void listCustomers(Container const &ListaClientes) 
{
    clearConsole();
    if (ListaClientes.numCustomers != 0)       // revisa que haya clientes
    {
        cout << endl <<"Lista de clientes:" << endl;
        cout << "Codigo     Nombre      Ciudad" << endl;
        for (int i = 0; i < ListaClientes.numCustomers; i++)        // recorre todos los clientes imprimiendo en cada iteracion de i
        {
            cout << ListaClientes.customers[i].code << " " << ListaClientes.customers[i].name << " " << ListaClientes.customers[i].city << endl;
        }
        cout << endl;
    } 
    else                    // al no haber clientes se informa
    {
        cout << endl << "No hay clientes registrados." << endl;
        pauseConsole();
        clearConsole();
    }
}

void findCustomer(Container const &ListaClientes) 
{
    int code;                                                    // variable para buscar el código del cliente
    cout << endl << "Ingrese el código del cliente a buscar: ";
    cin >> code;
    clearConsole();
    for (int i = 0; i < ListaClientes.numCustomers; i++)         // bucle para buscar el cliente desde 0 hasta la cantidad de clientes 
    {                                                            // numcustomers es la variable que indica la cantidad de clientes   
        if (ListaClientes.customers[i].code == code) 
        {
            cout << endl << "Cliente encontrado: " << endl;
            cout << "Código: " << ListaClientes.customers[i].code << endl;
            cout << "Nombre: " << ListaClientes.customers[i].name << endl;
            cout << "Ciudad: " << ListaClientes.customers[i].city << endl << endl;
            return;                                              // sale del bucle si encuentra el cliente. este return no devuelve nada 
        }                                                        // ya que la funcion es void
    }
    cout << endl << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

void clearConsole()                                         // Función para limpiar la consola
{                                                           // Implementada por el Profesor Gabriel Ferreira
    #ifdef __unix__                                         // para funcionar en cualquier sistema operativo
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)
        system("cls");
    #endif
}

void pauseConsole()                                         // Función para pausar la consola
{
cout << "Presione Enter para continuar..." << endl;
cin.ignore();                                               // Limpia el buffer
cin.get();                                                  // espera a que el usuario presione enter
}  

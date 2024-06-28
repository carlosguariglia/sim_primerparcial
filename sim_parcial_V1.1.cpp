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
*/

#include <iostream>   // Para entrada y salida estándar
#include <fstream>    // Para manejo de archivos
#include <string>     // Para uso de la clase string

using namespace std;

const int MAX_CUSTOMERS = 100;  // Número máximo de clientes que podemos manejar
                                // debe ser del tipo constante (const) para poder usarla como tamano arreglo
// Estructura que representa a un cliente con código, nombre y ciudad
struct Customer {
    int code;
    string name;
    string city;
};

// Estructura para manejar una colección de clientes
struct Container {
    Customer customers[MAX_CUSTOMERS];  // Array de clientes
    int numCustomers;                   // Número actual de clientes en el array
};

// Prototipos de funciones
void loadFromFile(Container &clientList);   // Carga los clientes desde el archivo
void saveToFile(const Container &clientList); // Guarda los clientes en el archivo
void addCustomer(Container &clientList);   // Añade un nuevo cliente
void removeCustomer(Container &clientList); // Elimina un cliente existente
void updateCustomer(Container &clientList); // Modifica los datos de un cliente
void listCustomers(const Container &clientList); // Lista todos los clientes
void findCustomer(const Container &clientList);  // Busca un cliente por su código
void clearConsole();       // Limpia la consola
void pauseConsole();       // Pausa la consola esperando la entrada del usuario
void splitLineByComma(const string &line, Customer &customer); // Divide una línea de texto en código, nombre y ciudad

int main() {
    clearConsole();  // Limpia la consola al inicio

    int menu;  // Variable para almacenar la opción del menú seleccionada
    Container clientList;  // Variable para almacenar la lista de clientes
    clientList.numCustomers = 0;  // Inicializa el número de clientes a cero

    loadFromFile(clientList);  // Carga los datos de clientes desde el archivo

    // Bucle principal del menú
    do {
        // Despliega el menú
        cout << "-------------- MENÚ --------------" << endl;
        cout << "1. Dar de alta un cliente" << endl;
        cout << "2. Dar de baja un cliente" << endl;
        cout << "3. Modificar un cliente" << endl;
        cout << "4. Listar todos los clientes" << endl;
        cout << "5. Buscar un cliente por código" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> menu;
        cin.ignore();  // Limpia el buffer para evitar problemas con `getline` posterior

        // Maneja la opción seleccionada
        switch (menu) {
            case 1: addCustomer(clientList); break;
            case 2: removeCustomer(clientList); break;
            case 3: updateCustomer(clientList); break;
            case 4: listCustomers(clientList); break;
            case 5: findCustomer(clientList); break;
            case 6: saveToFile(clientList); 
                    cout << "Saliendo..." << endl; break;
            default:    cout << "Opción inválida" << endl; 
                        pauseConsole(); break;
        }

    } while (menu != 6);  // Continua el bucle hasta que el usuario seleccione salir (opción 6)

    return 0;
}

// Función que carga los datos de clientes desde un archivo
void loadFromFile(Container &clientList) {
    ifstream file("customers.txt");  // Abre el archivo en modo lectura
    if (file.is_open()) {  // Verifica si el archivo se abrió correctamente
        string line;
        // Lee cada línea del archivo
        while (getline(file, line)) {
            if (!line.empty()) {  // Verifica que la línea no esté vacía
                splitLineByComma(line, clientList.customers[clientList.numCustomers]); // Separa los datos y los almacena en un cliente
                clientList.numCustomers++;  // Incrementa el contador de clientes
            }
        }
        file.close();  // Cierra el archivo
    } else {
        // Si no se pudo abrir el archivo
        cout << "No se pudo abrir el archivo." << endl;
        cout << "Desea crear un nuevo archivo? (1 = si, 0 = no)" << endl;
        int option;
        cin >> option;
        cin.ignore();  // Limpia el buffer
        if (option == 1) {
            ofstream newFile("customers.txt");  // Crea un nuevo archivo
            newFile.close();
            cout << "Archivo creado correctamente." << endl;
        } else {
            cout << "Saliendo..." << endl;
            pauseConsole();
            exit(1);  // Sale del programa si no se desea crear un nuevo archivo
        }
    }
}

// Función que guarda los datos de clientes en un archivo
void saveToFile(const Container &clientList) {
    ofstream file("customers.txt");  // Abre el archivo en modo escritura
    if (file.is_open()) {  // Verifica si el archivo se abrió correctamente
        for (int i = 0; i < clientList.numCustomers; i++) {
            // Escribe cada cliente en una línea, separado por comas
            file << clientList.customers[i].code << ","
                << clientList.customers[i].name << ","
                << clientList.customers[i].city;
            if (i < clientList.numCustomers - 1) {
                file << endl;  // No añade una nueva línea después del último cliente
            }
        }
        file.close();  // Cierra el archivo
    } else {
        cout << "No se pudo guardar el archivo." << endl;
        pauseConsole();
    }
}

// Función que añade un nuevo cliente a la lista
void addCustomer(Container &clientList) {
    clearConsole();
    Customer newCustomer;

    // Asigna un código nuevo al cliente
    if (clientList.numCustomers == 0) {
        newCustomer.code = 100;  // Primer cliente empieza con código 100
    } else {
        // El nuevo código es uno más que el código del último cliente
        newCustomer.code = clientList.customers[clientList.numCustomers - 1].code + 1;
    }

    if (clientList.numCustomers < MAX_CUSTOMERS) {  // Verifica que haya espacio para un nuevo cliente
        cout << "Ingrese el nombre del cliente: ";
        getline(cin, newCustomer.name);  // Lee el nombre completo incluyendo espacios
        cout << "Ingrese la ciudad del cliente: ";
        getline(cin, newCustomer.city);  // Lee la ciudad completa incluyendo espacios

        clientList.customers[clientList.numCustomers] = newCustomer;  // Añade el nuevo cliente al array
        clientList.numCustomers++;  // Incrementa el contador de clientes
        cout << "Cliente agregado correctamente." << endl;
        pauseConsole();
        clearConsole();
    } else {
        cout << "No se pueden agregar más clientes. Máximo alcanzado." << endl;
        pauseConsole();
        clearConsole();
    }
}

// Función que elimina un cliente por su código
void removeCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a dar de baja: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    // Busca el cliente en la lista
    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code) {  // Si encuentra el cliente
            // Mueve todos los clientes siguientes un lugar hacia atrás
            for (int j = i; j < clientList.numCustomers - 1; j++) {
                clientList.customers[j] = clientList.customers[j + 1];
            }
            clientList.numCustomers--;  // Decrementa el contador de clientes
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

// Función que modifica los datos de un cliente por su código
void updateCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a modificar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    // Busca el cliente en la lista
    for (int i = 0; i < clientList.numCustomers; i++) 
    {
        if (clientList.customers[i].code == code)   // Si encuentra el cliente
        {
            // Muestra los datos actuales del cliente
            cout << "El cliente a modificar es: " << endl;
            cout << "Código: " << clientList.customers[i].code << endl;
            cout << "Nombre: " << clientList.customers[i].name << endl;
            cout << "Ciudad: " << clientList.customers[i].city << endl;

            // Pide los nuevos datos del cliente
            cout << "Ingrese el nuevo nombre del cliente: ";
            getline(cin, clientList.customers[i].name);
            cout << "Ingrese la nueva ciudad del cliente: ";
            getline(cin, clientList.customers[i].city);

            cout << "Cliente modificado correctamente." << endl;
            pauseConsole();
            clearConsole();
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

// Función que lista todos los clientes
void listCustomers(const Container &clientList) 
{
    clearConsole();
    if (clientList.numCustomers > 0) {  // Verifica que haya clientes para mostrar
        cout << "Lista de clientes:" << endl;
        cout << "Código  Nombre  Ciudad" << endl;
        for (int i = 0; i < clientList.numCustomers; i++)
        {
            // Muestra los datos de cada cliente
            cout << clientList.customers[i].code << ", "
                << clientList.customers[i].name << ", "
                << clientList.customers[i].city << endl;
        }
    } else {
        cout << "No hay clientes registrados." << endl;
    }
    cout << endl;
}

// Función que busca un cliente por su código y lo muestra
void findCustomer(const Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a buscar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    // Busca el cliente en la lista
    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code)
        {  // Si encuentra el cliente
            // Muestra los datos del cliente
            cout << "Cliente encontrado: " << endl;
            cout << "Código: " << clientList.customers[i].code << endl;
            cout << "Nombre: " << clientList.customers[i].name << endl;
            cout << "Ciudad: " << clientList.customers[i].city << endl;
            cout << endl;
            return;     //sale de la funcion (no retorna nada  
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
}

// Función que limpia la consola
void clearConsole() {
    #ifdef __unix__  // Para sistemas Unix
        system("clear");
    #elif __APPLE__  // Para sistemas Apple
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)  // Para sistemas Windows
        system("cls");
    #endif
}

// Función que pausa la consola esperando que el usuario presione Enter
void pauseConsole() {
    cout << "Presione Enter para continuar..." << endl;
    //cin.ignore();
    cin.get();
}

// Función que separa una línea de texto en código, nombre y ciudad usando coma como delimitador
void splitLineByComma(const string &line, Customer &customer) {
    size_t pos1 = line.find(',');  // Encuentra la posición de la primera coma
    size_t pos2 = line.find(',', pos1 + 1);  // Encuentra la posición de la segunda coma después de la primera

    // Verifica que ambas comas fueron encontradas
    if (pos1 != string::npos && pos2 != string::npos) {
        // Extrae y asigna el código (como entero)
        customer.code = stoi(line.substr(0, pos1));
        // Extrae y asigna el nombre (cadena entre las dos comas)
        customer.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        // Extrae y asigna la ciudad (cadena después de la segunda coma)
        customer.city = line.substr(pos2 + 1);
    }
}



/*
Función splitLineByComma
Propósito

La función splitLineByComma toma una línea de texto (line) que representa a un cliente y la divide en sus tres partes: código, nombre y ciudad. Luego, asigna estos valores a los campos correspondientes de una estructura Customer.
Firma de la Función

void splitLineByComma(const string &line, Customer &customer);

    Parámetros:
        const string &line: Una referencia constante a una cadena de texto que contiene la información del cliente en formato "codigo,nombre,ciudad".
        Customer &customer: Una referencia a una estructura Customer donde se almacenarán los valores extraídos.

    Tipo de Retorno:
        La función es void, lo que significa que no devuelve ningún valor. En su lugar, modifica el objeto customer pasado por referencia.

Implementación Detallada

void splitLineByComma(const string &line, Customer &customer) {
    size_t pos1 = line.find(',');          // Encuentra la posición de la primera coma
    size_t pos2 = line.find(',', pos1 + 1); // Encuentra la posición de la segunda coma, comenzando después de la primera coma

    if (pos1 != string::npos && pos2 != string::npos) { // Verifica que ambas comas fueron encontradas
        customer.code = stoi(line.substr(0, pos1));        // Convierte la subcadena antes de la primera coma en un entero para el código
        customer.name = line.substr(pos1 + 1, pos2 - pos1 - 1); // Extrae el nombre entre las dos comas
        customer.city = line.substr(pos2 + 1);             // Extrae la ciudad después de la segunda coma
    }
}

Desglose Paso a Paso

    Encontrar la Primera Coma:

size_t pos1 = line.find(',');

    line.find(',') busca la primera aparición de la coma en la cadena line.
    La posición de esta primera coma se guarda en pos1.
    size_t es un tipo de dato que representa una posición o tamaño y es seguro para operaciones con índices en cadenas.

Encontrar la Segunda Coma:

size_t pos2 = line.find(',', pos1 + 1);

    line.find(',', pos1 + 1) busca la próxima aparición de la coma en line, comenzando justo después de la posición de la primera coma (pos1 + 1).
    La posición de esta segunda coma se guarda en pos2.

Validar las Posiciones:

if (pos1 != string::npos && pos2 != string::npos)

    string::npos es un valor especial que indica que no se encontró la posición buscada.
    Aquí, se verifica que ambas comas fueron encontradas (pos1 y pos2 no son string::npos).

Extraer y Asignar el Código:

customer.code = stoi(line.substr(0, pos1));

    line.substr(0, pos1) extrae la subcadena desde el inicio hasta la posición justo antes de la primera coma.
    stoi convierte esta subcadena en un entero (string to integer).
    El valor resultante se asigna al campo code de la estructura Customer.

Extraer y Asignar el Nombre:

customer.name = line.substr(pos1 + 1, pos2 - pos1 - 1);

    line.substr(pos1 + 1, pos2 - pos1 - 1) extrae la subcadena entre la primera y la segunda coma.
    pos1 + 1 es la posición justo después de la primera coma.
    pos2 - pos1 - 1 es la longitud de la subcadena entre las dos comas.
    El valor resultante se asigna al campo name de la estructura Customer.

Extraer y Asignar la Ciudad:

customer.city = line.substr(pos2 + 1);

    line.substr(pos2 + 1) extrae la subcadena desde la posición justo después de la segunda coma hasta el final de la línea.
    El valor resultante se asigna al campo city de la estructura Customer.

*/
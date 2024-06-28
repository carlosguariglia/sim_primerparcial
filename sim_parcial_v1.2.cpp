#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CUSTOMERS = 100;

struct Customer {
    int code;
    string name;
    string city;
};

struct Container {
    Customer customers[MAX_CUSTOMERS];
    int numCustomers;
};

// Prototipos de funciones
void loadFromFile(Container &clientList);
void saveToFile(const Container &clientList);
void addCustomer(Container &clientList);
void removeCustomer(Container &clientList);
void updateCustomer(Container &clientList);
void listCustomers(const Container &clientList);
void findCustomer(const Container &clientList);
void clearConsole();
void pauseConsole();
void splitLineByComma(const string &line, Customer &customer); // función para separar una línea por comas
int findCustomerIndex(const Container &clientList, int code); // funcion auxiliar para buscar un cliente por su código

int main() {
    clearConsole();

    int menu;
    Container clientList;
    clientList.numCustomers = 0;

    loadFromFile(clientList);

    do {
        cout << "-------------- MENÚ --------------" << endl;
        cout << "1. Dar de alta un cliente" << endl;
        cout << "2. Dar de baja un cliente" << endl;
        cout << "3. Modificar un cliente" << endl;
        cout << "4. Listar todos los clientes" << endl;
        cout << "5. Buscar un cliente por código" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> menu;
        cin.ignore();  // Limpiar el buffer para `getline` posterior

        switch (menu) {
            case 1: addCustomer(clientList); break;
            case 2: removeCustomer(clientList); break;
            case 3: updateCustomer(clientList); break;
            case 4: listCustomers(clientList); break;
            case 5: findCustomer(clientList); break;
            case 6: saveToFile(clientList); 
                    cout << "Saliendo..." << endl; break;
            default: cout << "Opción inválida" << endl; 
                    pauseConsole(); break;
        }

    } while (menu != 6);

    return 0;
}

void loadFromFile(Container &clientList) 
{
    ifstream file("customers.txt");
    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        {
            if (!line.empty()) 
            {
                splitLineByComma(line, clientList.customers[clientList.numCustomers]);
                clientList.numCustomers++;
            }
        }
        file.close();
    } else
    {
        cout << "No se pudo abrir el archivo." << endl;
        pauseConsole();
        exit(1);
    }
}

void saveToFile(const Container &clientList) {
    ofstream file("customers.txt");
    if (file.is_open()) {
        for (int i = 0; i < clientList.numCustomers; i++) {
            file << clientList.customers[i].code << ","
                << clientList.customers[i].name << ","
                << clientList.customers[i].city;
            if (i < clientList.numCustomers - 1) {
                file << endl;
            }
        }
        file.close();
    } else {
        cout << "No se pudo guardar el archivo." << endl;
        pauseConsole();
    }
}

void addCustomer(Container &clientList) {
    clearConsole();
    Customer newCustomer;

    if (clientList.numCustomers == 0) {
        newCustomer.code = 100;
    } else {
        newCustomer.code = clientList.customers[clientList.numCustomers - 1].code + 1;
    }

    if (clientList.numCustomers < MAX_CUSTOMERS) {
        cout << "Ingrese el nombre del cliente: ";
        getline(cin, newCustomer.name);
        cout << "Ingrese la ciudad del cliente: ";
        getline(cin, newCustomer.city);

        clientList.customers[clientList.numCustomers] = newCustomer;
        clientList.numCustomers++;
        cout << "Cliente agregado correctamente." << endl;
        
    } else {
        cout << "No se pueden agregar más clientes. Máximo alcanzado." << endl;
        
    }
    pauseConsole();
    clearConsole();
}

// Función para buscar el índice de un cliente por su código
int findCustomerIndex(const Container &clientList, int code) {
    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code) {
            return i;  // Devuelve el índice del cliente encontrado
        }
    }
    return -1;  // Devuelve -1 si no se encontró el cliente
}

void removeCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a dar de baja: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    int index = findCustomerIndex(clientList, code); // Usa la nueva función auxiliar

    if (index != -1) {  // Si el cliente se encontró
        for (int i = index; i < clientList.numCustomers - 1; i++) {
            clientList.customers[i] = clientList.customers[i + 1];
        }
        clientList.numCustomers--;
        cout << "Cliente eliminado correctamente." << endl;
    } else {
        cout << "Cliente no encontrado." << endl;
    }
    pauseConsole();
    clearConsole();
}

void updateCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a modificar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    int index = findCustomerIndex(clientList, code); // Usa la nueva función auxiliar

    if (index != -1) {  // Si el cliente se encontró
        cout << "El cliente a modificar es: " << endl;
        cout << "Código: " << clientList.customers[index].code << endl;
        cout << "Nombre: " << clientList.customers[index].name << endl;
        cout << "Ciudad: " << clientList.customers[index].city << endl;

        cout << "Ingrese el nuevo nombre del cliente: ";
        getline(cin, clientList.customers[index].name);
        cout << "Ingrese la nueva ciudad del cliente: ";
        getline(cin, clientList.customers[index].city);

        cout << "Cliente modificado correctamente." << endl;
    } else {
        cout << "Cliente no encontrado." << endl;
    }
    pauseConsole();
    clearConsole();
}

void listCustomers(const Container &clientList) 
{
    clearConsole();
    if (clientList.numCustomers > 0) {
        cout << "Lista de clientes:" << endl;
        cout << "Código  Nombre  Ciudad" << endl;
        for (int i = 0; i < clientList.numCustomers; i++) {
            cout << clientList.customers[i].code << ", "
                << clientList.customers[i].name << ", "
                << clientList.customers[i].city << endl;
        }
    } else {
        cout << "No hay clientes registrados." << endl;
    }
    cout << endl;
}

void findCustomer(const Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a buscar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    int index = findCustomerIndex(clientList, code); // Usa la función auxiliar busqueda de un cliente

    if (index != -1) 
    {  // Si el cliente se encontró
        cout << "Cliente encontrado: " << endl;
        cout << "Código: " << clientList.customers[index].code << endl;
        cout << "Nombre: " << clientList.customers[index].name << endl;
        cout << "Ciudad: " << clientList.customers[index].city << endl;
    } else {
        cout << "Cliente no encontrado." << endl;
    }
    cout << endl;
    
}

void clearConsole() {
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)
        system("cls");
    #endif
}

void pauseConsole() {
    cout << "Presione Enter para continuar..." << endl;
    //cin.ignore();
    cin.get();
}

// Nueva función `splitLineByComma` que usa un enfoque simple sin librerías adicionales
void splitLineByComma(const string &line, Customer &customer)
{
    string aux = "";  // Buffer auxiliar para acumular caracteres
    int field = 0;    // Campo actual de la struct: 0 para código, 1 para nombre, 2 para ciudad

    for (size_t i = 0; i < line.size(); i++) 
    {  // Recorre la cadena `line` tiene una comauw ser del tipo size_t porque la funcion line.size() devuelve un valor tipo size_t si se cambia por int puede haber errores
        if (line[i] == ',') 
        {  // Al encontrar una coma, pasa al siguiente campo
            if (field == 0) 
            {
                // Convertir y asignar el primer campo (código)
                customer.code = stoi(aux);
            } else if (field == 1) 
            {
                // Asignar el segundo campo (nombre)
                customer.name = aux;
            }
            aux = "";  // Limpiar el buffer auxiliar para el siguiente campo
            field++;   // Pasar al siguiente campo
        } else {
            aux += line[i];  // Acumular caracteres en el buffer auxiliar
        }
    }
    // El último campo (ciudad) se asigna después de recorrer la cadena
    if (field == 2) 
    {
        customer.city = aux;
    }
}

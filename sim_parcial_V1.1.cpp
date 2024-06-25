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

void loadFromFile(Container &clientList);
void saveToFile(const Container &clientList);
void addCustomer(Container &clientList);
void removeCustomer(Container &clientList);
void updateCustomer(Container &clientList);
void listCustomers(const Container &clientList);
void findCustomer(const Container &clientList);
void clearConsole();
void pauseConsole();
void splitLineByComma(const string &line, Customer &customer);

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
            default: cout << "Opción inválida" << endl; pauseConsole(); break;
        }

    } while (menu != 6);

    return 0;
}

void loadFromFile(Container &clientList) {
    ifstream file("customers.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                splitLineByComma(line, clientList.customers[clientList.numCustomers]);
                clientList.numCustomers++;
            }
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        cout << "Desea crear un nuevo archivo? (1 = si, 0 = no)" << endl;
        int option;
        cin >> option;
        cin.ignore();  // Limpiar el buffer
        if (option == 1) {
            ofstream newFile("customers.txt");
            newFile.close();
            cout << "Archivo creado correctamente." << endl;
        } else {
            cout << "Saliendo..." << endl;
            pauseConsole();
            exit(1);
        }
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
        pauseConsole();
        clearConsole();
    } else {
        cout << "No se pueden agregar más clientes. Máximo alcanzado." << endl;
        pauseConsole();
        clearConsole();
    }
}

void removeCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a dar de baja: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code) {
            for (int j = i; j < clientList.numCustomers - 1; j++) {
                clientList.customers[j] = clientList.customers[j + 1];
            }
            clientList.numCustomers--;
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

void updateCustomer(Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a modificar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code) {
            cout << "El cliente a modificar es: " << endl;
            cout << "Código: " << clientList.customers[i].code << endl;
            cout << "Nombre: " << clientList.customers[i].name << endl;
            cout << "Ciudad: " << clientList.customers[i].city << endl;

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

void listCustomers(const Container &clientList) {
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
    //pauseConsole();
    cout << endl;
}

void findCustomer(const Container &clientList) {
    int code;
    cout << "Ingrese el código del cliente a buscar: ";
    cin >> code;
    cin.ignore();  // Limpiar el buffer
    clearConsole();

    for (int i = 0; i < clientList.numCustomers; i++) {
        if (clientList.customers[i].code == code) {
            cout << "Cliente encontrado: " << endl;
            cout << "Código: " << clientList.customers[i].code << endl;
            cout << "Nombre: " << clientList.customers[i].name << endl;
            cout << "Ciudad: " << clientList.customers[i].city << endl;
            //pauseConsole();
            cout << endl;
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
    pauseConsole();
    clearConsole();
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

void splitLineByComma(const string &line, Customer &customer) {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);

    if (pos1 != string::npos && pos2 != string::npos) {
        customer.code = stoi(line.substr(0, pos1));
        customer.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        customer.city = line.substr(pos2 + 1);
    }
}

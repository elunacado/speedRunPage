#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream> 
#include <fstream> 

using namespace std;

struct Run {
    string playerName;
    double timeInMinutes;
};

class Entry{
public:
    std::string data;
    Entry* next;

    Entry(const std::string& value) : data(value), next(nullptr){}

    ~Entry() {
        delete next;
    }
};



class History{
public:
    Entry* head;

    History() : head(nullptr){};

    ~History() { delete head; }

    void addEntry(const std::string& entry){
        Entry* newEntry = new Entry(entry);
        newEntry->next = head;
        head = newEntry;
    }

    void printHistory(){
        Entry* current = head;
        while (current)
        {
            std::cout << current->data << endl;
            current = current->next; 
        }
           
    } 

};

vector<Run> cargarRunsDesdeDB() {
   vector<Run> speedruns;
    ifstream archivo("DB.txt"); 

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Run run;
            getline(ss, run.playerName, ','); 
            ss >> run.timeInMinutes;

            speedruns.push_back(run);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de speedruns." << endl;
    }

    return speedruns;
}

void agregarRun(vector<Run>& speedruns, string username, int time) {
    Run nuevaRun;
    std::ofstream file;
    file.open("DB.txt", std::ios_base::app);
    nuevaRun.playerName = username;
    nuevaRun.timeInMinutes = time;
    speedruns.push_back(nuevaRun);
    file <<nuevaRun.playerName <<", "<<nuevaRun.timeInMinutes<< endl;
    file.close();
}

// Estudiar
void merge(std::vector<Run>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<Run> L(n1), R(n2);

    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    
    int i = 0; 
    int j = 0; 
    int k = l; 
    while (i < n1 && j < n2) {
        if (L[i].timeInMinutes <= R[j].timeInMinutes) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<Run>& arr, int l, int r) {
    if (l < r) {
       
        int m = l + (r - l) / 2;

        
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

     
        merge(arr, l, m, r);
    }
}

void mostrarLeaderboard(const std::vector<Run>& speedruns) {
    std::vector<Run> leaderboard = speedruns;

    // Llamar a la función merge_sort para ordenar el vector leaderboard
    merge_sort(leaderboard, 0, leaderboard.size() - 1);

    std::cout << "Leaderboard:" << std::endl;
    int position = 1;
    for (const Run& run : leaderboard) {
        std::cout << position << ". " << run.playerName << " - " << run.timeInMinutes << " minutos" << std::endl;
        position++;
    }
}

int buscarmeEnLeaderboard(const vector<Run>& speedruns, const string& username) {
    // Ordenar las runs por tiempo
    vector<Run> leaderboard = speedruns;
    sort(leaderboard.begin(), leaderboard.end(), [](const Run& a, const Run& b) {
        return a.timeInMinutes < b.timeInMinutes;
    });

    // Buscar la posición del usuario en la leaderboard
    int position = 1;
    for (const Run& run : leaderboard) {
        if (run.playerName == username) {
            cout << "El usuario "<<run.playerName<<" ocupa la(s) posición(es) " << position << endl;
        }
        position++;
    }
    return -1;
}



int main() {
    History mihistorial;
    vector<Run> speedruns = cargarRunsDesdeDB();
    string username;
    int time;
    int userPosition = -1;
    

    while (true) {
        cout << "Opciones:" << endl;
        cout << "1. Subir una nueva run" << endl;
        cout << "2. Ver la leaderboard" << endl;
        cout << "3. Ver su puesto mas alto en la leaderboard" << endl;
        cout << "4. Ver el historial de runs subidas" << endl;
        cout << "5. Salir" << endl;

        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del jugador: ";
                cin >> username;
                if (username == "") cout << "Ingresa un nombre válido"; break;

                cout << "Tiempo en minutos: ";
                cin >> time;
                if (time == 0) { cout << "Ingresa un nombre válido"; break;}   



                agregarRun(speedruns, username, time);
                mihistorial.addEntry("Se agrega la run de: " + username);
                break;
            case 2:
                mostrarLeaderboard(speedruns);
                break;
            case 3:
                cout << "Ingrese su nombre de usuario: ";
                cin >> username;
                userPosition = buscarmeEnLeaderboard(speedruns, username);
                if (userPosition != -1) {
                    cout << userPosition << endl;
                }
                break;
            case 4:
                cout << "Historial: " << endl;
                mihistorial.printHistory();
                cout << "El juego fue liberado" << endl;
                break;

            case 5:
                cout << "¡Hasta luego!" << endl;
                return 0;
 
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }

    return 0;
}

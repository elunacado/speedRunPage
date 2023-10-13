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

void agregarRun(vector<Run>& speedruns) {
    Run nuevaRun;
    std::ofstream file;
    file.open("DB.txt", std::ios_base::app);
    cout << "Nombre del jugador: ";
    cin >> nuevaRun.playerName;
    cout << "Tiempo en minutos: ";
    cin >> nuevaRun.timeInMinutes;
    speedruns.push_back(nuevaRun);
    file <<nuevaRun.playerName <<", "<<nuevaRun.timeInMinutes<< endl;
    file.close();
}

// Estudiar
void merge(std::vector<Run>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crear subarrays temporales
    std::vector<Run> L(n1), R(n2);

    // Copiar datos a los subarrays temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Combinar los subarrays temporales de nuevo en arr[l..r]
    int i = 0; // Índice inicial del primer subarray
    int j = 0; // Índice inicial del segundo subarray
    int k = l; // Índice inicial del subarray combinado
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

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<Run>& arr, int l, int r) {
    if (l < r) {
        // Encuentra el punto medio del array
        int m = l + (r - l) / 2;

        // Ordena las mitades izquierda y derecha
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        // Combina las mitades ordenadas
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
    vector<Run> speedruns = cargarRunsDesdeDB();
    string username;
    int userPosition = -1;

    while (true) {
        cout << "Opciones:" << endl;
        cout << "1. Subir una nueva run" << endl;
        cout << "2. Ver la leaderboard" << endl;
        cout << "3. Ver su puesto mas alto en la leaderboard" << endl;
        cout << "4. Salir" << endl;
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarRun (speedruns);
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
                cout << "¡Hasta luego!" << endl;
                return 0;
 
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }

    return 0;
}

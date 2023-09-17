#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream> 
#include <fstream> 

using namespace std;

struct Run {
    string playerName;
    string level;
    double timeInSeconds;
};

vector<Run> cargarRunsDesdeDB() {
   vector<Run> speedruns;
    ifstream archivo("DB.txt"); // Abre el archivo para lectura

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            // Parsea cada línea para obtener los datos de la run
            stringstream ss(linea);
            Run run;
            getline(ss, run.playerName, ','); // Suponiendo que los campos están separados por comas
            getline(ss, run.level, ',');
            ss >> run.timeInSeconds;

            speedruns.push_back(run);
        }
        archivo.close(); // Cierra el archivo después de leerlo
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
    cout << "De que nivel es el speedrun ";
    cin >> nuevaRun.level;
    cout << "Tiempo en segundos: ";
    cin >> nuevaRun.timeInSeconds;
    speedruns.push_back(nuevaRun);
    file << nuevaRun.playerName << ", "<<nuevaRun.level<<", "<<nuevaRun.timeInSeconds<<endl;
    file.close();
}

void mostrarLeaderboard(const vector<Run>& speedruns) {
    vector<Run> leaderboard = speedruns;
    sort(leaderboard.begin(), leaderboard.end(), [](const Run& a, const Run& b) {
        return a.timeInSeconds < b.timeInSeconds;
    });

    cout << "Leaderboard:" << endl;
    int position = 1;
    for (const Run& run : leaderboard) {
        cout << position << ". " << run.playerName << " - NIVEL: " << run.level << " - " << run.timeInSeconds << " segundos" << endl;
        position++;
    }
}

int buscarmeEnLeaderboard(const vector<Run>& speedruns, const string& username) {
    // Ordenar las runs por tiempo (ascendente)
    vector<Run> leaderboard = speedruns;
    sort(leaderboard.begin(), leaderboard.end(), [](const Run& a, const Run& b) {
        return a.timeInSeconds < b.timeInSeconds;
    });

    // Buscar la posición del usuario en la leaderboard
    int position = 1;
    for (const Run& run : leaderboard) {
        if (run.playerName == username) {
            cout << "El usuario "<<run.playerName<<" ocupa la(s) posición(es) " << position << endl;
            //return position;
        }
        position++;
    }

    // Si el usuario no se encuentra en la leaderboard
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
                /*else {
                    cout << "No se encontró su nombre de usuario en la leaderboard." << endl;
                }*/
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

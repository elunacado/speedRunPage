#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream> 
#include <fstream> 

using namespace std;

struct Run {
    string playerName;
    string percent;
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
            getline(ss, run.percent, ',');
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
    cout << "De que porcentaje ";
    cin >> nuevaRun.percent;
    cout << "Tiempo en minutos: ";
    cin >> nuevaRun.timeInMinutes;
    speedruns.push_back(nuevaRun);
    file << nuevaRun.playerName << ", "<<nuevaRun.percent<<", "<<nuevaRun.timeInMinutes<<endl;
    file.close();
}

void mostrarLeaderboard(const vector<Run>& speedruns) {
    vector<Run> leaderboard = speedruns;
    sort(leaderboard.begin(), leaderboard.end(), [](const Run& a, const Run& b) {
        return a.timeInMinutes < b.timeInMinutes;
    });

    cout << "Leaderboard:" << endl;
    int position = 1;
    for (const Run& run : leaderboard) { //por cada dato en el leaderboard imprimirlo en el siguiente formato
        cout << position << ". " << run.playerName << " - " << run.percent << "% - " << run.timeInMinutes << " minutos" << endl;
        position++;
    }
}

void highPercentLeaderboard(const vector<Run>& speedruns) {
    vector<Run> leaderboard = speedruns;
    sort(leaderboard.begin(), leaderboard.end(), [](const Run& a, const Run& b){
    if (a.percent != b.percent) {
        return a.percent > b.percent; // Ordenar porcentaje de mayor a menor
    } else if (a.timeInMinutes != b.timeInMinutes) {
        return a.timeInMinutes < b.timeInMinutes; // Si el porcentaje es igual, ordenar por tiempo
    } 
});

    cout << "Leaderboard Highest Percent:" << endl;
    int position = 1;
    for (const Run& run : leaderboard) {
        cout << position << ". " << run.playerName << " - " << run.percent << "% "<< endl;
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
        cout << "4. Ver la leaderboard de porcentajes mas altos  -- EN REPARACIONES --" << endl;
        cout << "5. Salir" << endl;
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
                cout << "Esta función estuvo presentando problemas por lo que al ser arreglada sera habilitada nuevamente" << endl;
                //highPercentLeaderboard(speedruns);
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

//librerias incluidas que permiten que el sistema academico pueda mostrar informacion en consola
#include <iostream>//cout y cin
#include <fstream>//lectura y escritura de archivos
#include <conio.h>//para ingresar contraseñs de forma oculta con getch
#include <sstream>//para leer lineas de un archivo separado por comas
#include <string>//para trabajar  con texto de forma segura y flexible
#include <direct.h>//para usar mkdir para crear carpetas en el disco
#include <cstdlib>//para usar atoi para convertir de string a int
using namespace std;
//definicion de la estructura de datos llamada alumno
struct Alumno{
	string nombre;
	string ci; 
	string contrasena;
	string curso;
	string semestre;
	string seccion; 
	string anho;
};
//variable global del tipo alumno
Alumno alumnoActual;
//estructura opcion menu gestiona las opciones de los menus interactivos
struct OpcionMenu{
	string texto;
	void (*funcion)();
};
//variables globales para almacenar y gestionar los datos academicos de las materias
const int MAX_MATERIAS = 15;
string nombresMaterias[MAX_MATERIAS];
float porcentajesFinales[MAX_MATERIAS];
int notasEscala[MAX_MATERIAS];
int cantidadMaterias = 0;
string tipoUsuario = "alumno";
const int TOTAL_SEMESTRES = 10;
//declaracion del arreglo materiasPorSemestre
const string materiasPorSemestre[TOTAL_SEMESTRES][10] = {
    { "Comunicacion Oral y Escrita", "Fisica I", "Logica de Programacion", "Matematica I", "Teoria de la Informatica" },
    { "Base de Datos I", "Datos I - Estructura", "Fisica II", "Laboratorio de Hardware", "Matematica II" },
    { "Fisica III", "Geometria Analitica", "Lenguajes Visuales I", "Programacion I", "Sistemas Operativos (Cliente-Servidor)" },
    { "Base de Datos II", "Ingles Tecnico", "Lenguajes Visuales II", "Matematica Discreta", "Programacion II" },
    { "Analisis de Sistemas", "Calculo Diferencial", "Economia y Finanzas", "Guarani", "Organizacion Empresarial", "Programacion III" },
    { "Calculo Integral", "Herramientas de Diseno", "Liderazgo y Desarrollo Emprendedor", "Probabilidad y Estadistica", "Programacion IV", "Redes de Computadoras I" },
    { "Inteligencia Artificial", "Investigacion Operativa", "Programacion V", "Redes de Computadoras II", "Seguridad Informatica" },
    { "Administracion de TI", "Auditoria de Sistemas", "Data Warehouse", "Ingenieria de Software I", "Programacion VI" },
    { "Cloud Computing", "Data Center", "Electronica Digital I", "Ingenieria de Software II", "Legislacion y Etica Profesional", "Optativa I" },
    { "Electronica Digital II", "Metodologia de la Investigacion Cientifica", "Optativa II", "Practicas Laborales", "Proyectos Informaticos", "Robotica - Criptografia" }
};
// Declaraciones de funciones
// Funciones de acceso
void registrarAlumno();
bool loginAlumno(string ci, string contrasena);
// Menus
void mostrarMenuPrincipal();
void mostrarMenuAdmin();
int mostrarMenu(OpcionMenu opciones[], int cantidad);
// Funciones academicas
void verMateriasDelSemestre();
void verAvanceCurricular();
void consultarHorarioDeClases();
void realizarEncuestaDocente();
void exportarHistorialAcademico();
void cambiarContrasena();
void cerrarSesion();
void mostrarNotasGuardadas();
bool esContrasenaValida(string pass);
string leerContrasenaOculta();
// Funciones de administrador
void mostrarTodosLosHistoriales();
void buscarHistorialPorDato(string dato);
void buscarEnContenidoHistorial(string palabra);
void cargarNotas();
bool cargarAlumnoPorCi(string ciBuscado);
void accionCargarNotas();
void accionVerHistoriales();
void accionBuscarPorNombreOCi();
void accionBuscarPorPalabra();
void guardarNotasPorSemestre();
string calcularCarpetaPorSemestre();
// definicion del menu del alumno
OpcionMenu menuAlumno[] = {
    { "Ver materias del semestre actual", verMateriasDelSemestre },
    { "Ver avance curricular", verAvanceCurricular },
    { "Consultar horario de clases", consultarHorarioDeClases },
    { "Realizar encuesta docente", realizarEncuestaDocente },
    { "Exportar historial academico", exportarHistorialAcademico },
    { "Cambiar contrasena", cambiarContrasena },
    { "Cerrar sesion", cerrarSesion }
};
// FUNCION PRINCIPAL (MAIN) acceso a registro, inicio de sesion como alumno e inicio de sesion como administrador
int main() {
    int opcion;
    do {
        cout << "\n=== BIENVENIDO AL SISTEMA ===\n";
        cout << "1. Registrar nuevo alumno\n";
        cout << "2. Iniciar sesion como alumno\n";
        cout << "3. Iniciar sesion como administrador\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                registrarAlumno();
                break;
            case 2: {
                string ciTemp, passTemp;
                cin.ignore();
                cout << "CI: ";
                getline(cin, ciTemp);
                cout << "Contrasena: ";
                //getline(cin, passTemp);
                 passTemp = leerContrasenaOculta(); 
                if (loginAlumno(ciTemp, passTemp)) {
                	mostrarMenu(menuAlumno, 7);
                }
                break;
            }
            case 3: {
                string usuario, contrasena;
                cin.ignore();
                cout << "Usuario: ";
                getline(cin, usuario);
                cout << "Contrasena: ";
                //getline(cin, contrasena);
                contrasena = leerContrasenaOculta();
                if (usuario == "admin" && contrasena == "admin123") {
                    cout << "Login exitoso como ADMINISTRADOR.\n";
                    mostrarMenuAdmin();
                } else {
                    cout << "Credenciales incorrectas.\n";
                }
                break;
            }
            case 4:
                cout << "Hasta luego!\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
    return 0;
}
//FUNCIONES
//funcion registrar alumno
void registrarAlumno() {
    Alumno nuevo;
    cin.ignore();
    cout << "Nombre completo: ";
    getline(cin, nuevo.nombre);
    cout << "CI: ";
    getline(cin, nuevo.ci);
    cout << "Contrasena: ";
     nuevo.contrasena = leerContrasenaOculta();
    cout << "Curso (1 a 5): ";
    getline(cin, nuevo.curso);
    cout << "Semestre actual (1 al 10): ";
    getline(cin, nuevo.semestre);
    cout << "Seccion (A o B): ";
    getline(cin, nuevo.seccion);
    cout << "Anho: ";
    getline(cin, nuevo.anho);
    ofstream archivo("alumnos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevo.nombre << "," << nuevo.ci << "," << nuevo.contrasena << ","
        		<< nuevo.curso << "," << nuevo.semestre << "," 
				<< nuevo.seccion << "," << nuevo.anho << "\n";
        archivo.close();
        cout << "Registro exitoso.\n";
    } else {
        cout << "Error al guardar el alumno.\n";
    }
}
//funcion login alumno
bool loginAlumno(string ci, string contrasena) {
    ifstream archivo("alumnos.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, ciArchivo, contrasenaArchivo, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ciArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        if (ci == ciArchivo && contrasena == contrasenaArchivo) {
            alumnoActual.nombre = nombre;
            alumnoActual.ci = ciArchivo;
            alumnoActual.contrasena = contrasenaArchivo;
            alumnoActual.curso = curso;
            alumnoActual.semestre = semestre;
            alumnoActual.seccion = seccion;
            alumnoActual.anho = anho;
            cout << "Login exitoso. Bienvenido/a, " << alumnoActual.nombre << ".\n";
            return true;
        }
    }
    cout << "CI o contrasena incorrectos.\n";
    return false;
}
//Funciones admin
//funcion mostrar menu admin
void mostrarMenuAdmin() {
    int opcion;
    do {
        cout << "\n===== MENU ADMINISTRADOR =====\n";
        cout << "1. Cargar notas\n";
        cout << "2. Ver todos los historiales\n";
        cout << "3. Buscar historial por nombre o CI\n";
        cout << "4. Buscar por palabra clave\n";
        cout << "5. Salir del menu admin\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1: accionCargarNotas(); break;
            case 2: accionVerHistoriales(); break;
            case 3: accionBuscarPorNombreOCi(); break;
            case 4: accionBuscarPorPalabra(); break;
            case 5: cout << "Saliendo del menu admin...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);
}
//funciones para cada opcion del admin
//funcion accionCargarNotas
void accionCargarNotas(){
	string ci;
	cout << "Ingrese el CI del alumno para cargar sus notas: ";
	getline(cin, ci);
	if(cargarAlumnoPorCi(ci)){
		cout << "Alumno encontrado: " << alumnoActual.nombre << "\n";
		cargarNotas();
		exportarHistorialAcademico();
	}else {
		cout << "Alumno no encontrado.\n";
	}
}
//funcion accionVerHistoriales
void accionVerHistoriales(){
	mostrarTodosLosHistoriales();
}
//funcion accionBuscarPorNombreOCi
void accionBuscarPorNombreOCi(){
	string dato;
	cout << "Ingrese nombre o CI para buscar: ";
	getline(cin, dato);
	buscarHistorialPorDato(dato);
}
//funcion accionBuscarPorPalabra()
void accionBuscarPorPalabra(){
	string palabra;
	cout << "Ingrese palabra clavae a buscar en los historiales: ";
	getline(cin, palabra);
	buscarEnContenidoHistorial(palabra);
}
// funcion bool cargarAlumnoPorCi(string ciBuscado)
bool cargarAlumnoPorCi(string ciBuscado) {
    ifstream archivo("alumnos.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, ciArchivo, contrasenaArchivo, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ciArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
       	getline(ss, curso, ',');
		getline(ss, semestre, ','); 
		getline(ss, seccion, ',');
		getline(ss, anho, ',');
        if (ciArchivo == ciBuscado) {
            alumnoActual.nombre = nombre;
            alumnoActual.ci = ciArchivo;
            alumnoActual.contrasena = contrasenaArchivo;
            alumnoActual.curso = curso;
            alumnoActual.semestre = semestre; 
            alumnoActual.seccion = seccion;
            alumnoActual.anho = anho;
            return true;
        }
    }
    return false;
}
//funcion mostrar todos los historiales
void mostrarTodosLosHistoriales() {
    ifstream archivoAlumnos("alumnos.txt");
    if (!archivoAlumnos.is_open()) {
        cout << "No se pudo abrir alumnos.txt\n";
        return;
    }
    string linea;
    while (getline(archivoAlumnos, linea)) {
        stringstream ss(linea);
        string nombre, ci, contrasena, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ci, ',');
        getline(ss, contrasena, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        cout << "\n======================================================\n";
        cout << "Alumno: " << nombre << " | CI: " << ci << " | Curso: " << curso << " | Seccion: " << seccion << " | Anho: " << anho << "\n";
        // Construir carpeta según curso y sección
        string carpeta = anho + "/";
        if (curso == "1") carpeta += "1er_curso_" + seccion;
        else if (curso == "2") carpeta += "2do_curso_" + seccion;
        else if (curso == "3") carpeta += "3er_curso_" + seccion;
        else if (curso == "4") carpeta += "4to_curso_" + seccion;
        else if (curso == "5") carpeta += "5to_curso_" + seccion;
        else carpeta += "otros";
        for (int s = 1; s <= TOTAL_SEMESTRES; s++) {
            stringstream ssSemestre;
            ssSemestre << s;
            string archivoNotas = carpeta + "/" + ci + "_semestre" + ssSemestre.str() + ".txt";
            ifstream archivoNotasSemestre(archivoNotas.c_str());
            if (archivoNotasSemestre.is_open()) {
                cout << "\n--- SEMESTRE " << s << " ---\n";
                cout << "+----------------------------------------------------------+\n";
                cout << "| Materia                                | % Final | Escala |\n";
                cout << "+----------------------------------------------------------+\n";
                string lineaNota;
                while (getline(archivoNotasSemestre, lineaNota)) {
                    stringstream ssNota(lineaNota);
                    string materia, porcentaje, escala;
                    getline(ssNota, materia, ',');
                    getline(ssNota, porcentaje, ',');
                    getline(ssNota, escala);
                    cout.width(40);
                    cout << left << "| " + materia;
                    cout << "|   " << porcentaje << "   ";
                    cout << "|   " << escala << "    |\n";
                }

                cout << "+----------------------------------------------------------+\n";
                archivoNotasSemestre.close();
            }
        }
    }
    archivoAlumnos.close();
}
//funcion buscar historial por dato
void buscarHistorialPorDato(string dato) {
    ifstream archivoAlumnos("alumnos.txt");
    if (!archivoAlumnos.is_open()) {
        cout << "No se pudo abrir alumnos.txt\n";
        return;
    }
    bool encontrado = false;
    string linea;
    while (getline(archivoAlumnos, linea)) {
        stringstream ss(linea);
        string nombre, ci, contrasena, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ci, ',');
        getline(ss, contrasena, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        // Convertir todo a minúscula para comparación sin importar mayúsculas
        string nombreLower = nombre, ciLower = ci, datoLower = dato;
        for (int i = 0; i < nombreLower.length(); i++) nombreLower[i] = tolower(nombreLower[i]);
        for (int i = 0; i < ciLower.length(); i++) ciLower[i] = tolower(ciLower[i]);
        for (int i = 0; i < datoLower.length(); i++) datoLower[i] = tolower(datoLower[i]);
        if (nombreLower.find(datoLower) != string::npos || ciLower.find(datoLower) != string::npos) {
            encontrado = true;
            cout << "\n======================================================\n";
            cout << "Alumno: " << nombre << " | CI: " << ci << " | Curso: " << curso << " | Seccion: " << seccion << " | Año: " << anho << "\n";
            string carpeta = anho + "/";
            if (curso == "1") carpeta += "1er_curso_" + seccion;
            else if (curso == "2") carpeta += "2do_curso_" + seccion;
            else if (curso == "3") carpeta += "3er_curso_" + seccion;
            else if (curso == "4") carpeta += "4to_curso_" + seccion;
            else if (curso == "5") carpeta += "5to_curso_" + seccion;
            else carpeta += "otros";
            for (int s = 1; s <= TOTAL_SEMESTRES; s++) {
                stringstream ssSemestre;
                ssSemestre << s;
                string archivoNotas = carpeta + "/" + ci + "_semestre" + ssSemestre.str() + ".txt";
                ifstream archivoNotasSemestre(archivoNotas.c_str());
                if (archivoNotasSemestre.is_open()) {
                    cout << "\n--- SEMESTRE " << s << " ---\n";
                    cout << "+----------------------------------------------------------+\n";
                    cout << "| Materia                                | % Final | Escala |\n";
                    cout << "+----------------------------------------------------------+\n";
                    string lineaNota;
                    while (getline(archivoNotasSemestre, lineaNota)) {
                        stringstream ssNota(lineaNota);
                        string materia, porcentaje, escala;
                        getline(ssNota, materia, ',');
                        getline(ssNota, porcentaje, ',');
                        getline(ssNota, escala);
                        cout.width(40);
                        cout << left << "| " + materia;
                        cout << "|   " << porcentaje << "   ";
                        cout << "|   " << escala << "    |\n";
                    }
                    cout << "+----------------------------------------------------------+\n";
                    archivoNotasSemestre.close();
                }
            }
        }
    }
    archivoAlumnos.close();
    if (!encontrado) {
        cout << "\nNo se encontró ningún alumno con ese nombre o CI.\n";
    }
}
//funcion buscar en contenido historial
void buscarEnContenidoHistorial(string palabra) {
    ifstream archivoAlumnos("alumnos.txt");
    if (!archivoAlumnos.is_open()) {
        cout << "No se pudo abrir alumnos.txt\n";
        return;
    }
    _mkdir("reportes"); // Crea carpeta si no existe
    ofstream reporte("reportes/resultados_busqueda.txt");
    if (!reporte.is_open()) {
        cout << "No se pudo crear el archivo de reporte\n";
        return;
    }
    string linea;
    bool encontrado = false;
    while (getline(archivoAlumnos, linea)) {
        stringstream ss(linea);
        string nombre, ci, contrasena, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ci, ',');
        getline(ss, contrasena, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        string carpeta = anho + "/";
        if (curso == "1") carpeta += "1er_curso_" + seccion;
        else if (curso == "2") carpeta += "2do_curso_" + seccion;
        else if (curso == "3") carpeta += "3er_curso_" + seccion;
        else if (curso == "4") carpeta += "4to_curso_" + seccion;
        else if (curso == "5") carpeta += "5to_curso_" + seccion;
        else carpeta += "otros";
        for (int s = 1; s <= TOTAL_SEMESTRES; s++) {
            stringstream ssSemestre;
            ssSemestre << s;
            string archivoNotas = carpeta + "/" + ci + "_semestre" + ssSemestre.str() + ".txt";
            ifstream archivo(archivoNotas.c_str());
            if (archivo.is_open()) {
                string lineaNota;
                while (getline(archivo, lineaNota)) {
                    string lineaLower = lineaNota;
                    string palabraLower = palabra;
                    for (int i = 0; i < lineaLower.length(); i++) lineaLower[i] = tolower(lineaLower[i]);
                    for (int i = 0; i < palabraLower.length(); i++) palabraLower[i] = tolower(palabraLower[i]);
                    if (lineaLower.find(palabraLower) != string::npos) {
                        encontrado = true;
                        string info =
                            "\n--- Coincidencia encontrada ---\n" +
                            string("Alumno: ") + nombre + " | CI: " + ci + "\n" +
                            "Semestre: " + ssSemestre.str() + " | Curso: " + curso + " " + seccion + " | Anho: " + anho + "\n" +
                            "Linea: " + lineaNota + "\n";
                        cout << info;
                        reporte << info;
                    }
                }
                archivo.close();
            }
        }
    }
    archivoAlumnos.close();
    reporte.close();
    if (!encontrado) {
        cout << "\nNo se encontro la palabra en ningun historial.\n";
        ofstream reporteVacio("reportes/resultados_busqueda.txt");
        reporteVacio << "No se encontro la palabra: " << palabra << "\n";
        reporteVacio.close();
    } else {
        cout << "\nSe guardo el resultado en: reportes/resultados_busqueda.txt\n";
    }
}
//funcion guardar alumno por semestre
void guardarNotasPorSemestre(int semestre) {
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    stringstream ss;
	ss << semestre;
	string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ss.str() + ".txt";
    ofstream archivo(archivoNotas.c_str());
    if (archivo.is_open()) {
        for (int i = 0; i < cantidadMaterias; i++) {
            archivo << nombresMaterias[i] << "," << porcentajesFinales[i] << "," << notasEscala[i] << "\n";
        }
        archivo.close();
    } else {
        cout << "Error al guardar las notas por semestre.\n";
    }
}
//funcion para leer notas guardadas de todos los semestres
void mostrarNotasGuardadas() {
    int semestreActual = atoi(alumnoActual.semestre.c_str());
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    cout << "\n===== CALIFICACIONES GUARDADAS =====\n";
    for (int s = 1; s <= semestreActual; s++) {
    	stringstream ssNombre;
		ssNombre << s;
		string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ssNombre.str() + ".txt"; 
        ifstream archivo(archivoNotas.c_str());
        if (archivo.is_open()) {
            cout << "\nSemestre " << s << ":\n";
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string materia, porcentaje, escala;
                getline(ss, materia, ',');
                getline(ss, porcentaje, ',');
                getline(ss, escala);
                cout << "- " << materia << " -> " << porcentaje << "% - Escala: " << escala << "\n";
            }
            archivo.close();
        }
    }
}
//funcion mostrar menu principal
int mostrarMenu(OpcionMenu opciones[], int cantidad) {
    int opcion;
    do {
        cout << "\n========== PORTAL ACADEMICO UNINORTE ==========\n";
        for (int i = 0; i < cantidad; i++) {
            cout << (i + 1) << ". " << opciones[i].texto << "\n";
        }
        cout << "===============================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion >= 1 && opcion <= cantidad) {
            opciones[opcion - 1].funcion();
        } else {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != cantidad); // la última opción es siempre "Cerrar sesión"
    return 0;
}
//funcion ver materias del semestre
void verMateriasDelSemestre(){
	int semestre;
	do {
		cout << "\nIngrese el numero de semestre (1 al 10): ";
		cin >> semestre;	
		if(semestre < 1 || semestre > TOTAL_SEMESTRES){
			cout << "Semestre invalido. Intente de nuevo. \n";
		}
	} while (semestre < 1 || semestre > TOTAL_SEMESTRES);
	cout << "\nMaterias del semestre " << semestre << ":\n";
	for(int i=0; i<10; i++){
		string materia = materiasPorSemestre [semestre -1][i];
		if(!materia.empty())
		cout << "- " << materia << "\n";
	}
}
//funcion cargar Notas
void cargarNotas() {
   int semestre;
    do {
        cout << "\nPara que semestre vas a cargar las notas? (1 al 10): ";
        cin >> semestre;
        if (semestre < 1 || semestre > TOTAL_SEMESTRES) {
            cout << "Semestre invalido. Intente de nuevo.\n";
        }
    } while (semestre < 1 || semestre > TOTAL_SEMESTRES);
    cout << "\nCargando notas para el semestre " << semestre << " del alumno: " << alumnoActual.nombre << "\n";
    cantidadMaterias = 0;
    for (int i = 0; i < 10; i++) {
        if (materiasPorSemestre[semestre - 1][i] == "") continue;
        float parcial1, maxParcial1;
        float parcial2, maxParcial2;
        float trabajoPractico, maxTP;
        float examenFinal, maxEF;
        float porcentajeTotal, notaEscala;
        nombresMaterias[i] = materiasPorSemestre[semestre - 1][i];
        cout << "\n===== Materia: " << nombresMaterias[i] << " =====\n";
        cout << "Puntaje max Parcial 1: "; cin >> maxParcial1;
        cout << "Nota Parcial 1: "; cin >> parcial1;
        cout << "Puntaje max Parcial 2: "; cin >> maxParcial2;
        cout << "Nota Parcial 2: "; cin >> parcial2;
        cout << "Puntaje max TP: "; cin >> maxTP;
        cout << "Nota Trabajo Practico: "; cin >> trabajoPractico;
        cout << "Puntaje max Final: "; cin >> maxEF;
        cout << "Nota Examen Final: "; cin >> examenFinal;
        porcentajeTotal = (parcial1 / maxParcial1) * 15 +
                          (parcial2 / maxParcial2) * 15 +
                          (trabajoPractico / maxTP) * 10 +
                          (examenFinal / maxEF) * 60;
        if (porcentajeTotal < 60) notaEscala = 1;
        else if (porcentajeTotal < 70) notaEscala = 2;
        else if (porcentajeTotal < 80) notaEscala = 3;
        else if (porcentajeTotal < 90) notaEscala = 4;
        else notaEscala = 5;
        porcentajesFinales[i] = porcentajeTotal;
        notasEscala[i] = notaEscala;
        cout << "--- Resumen ---\n";
        cout << "Porcentaje: " << porcentajeTotal << "%\n";
        cout << "Escala: " << notaEscala << "\n";
        cout << (notaEscala >= 2 ? "Estado: APROBADO\n" : "Estado: REPROBADO\n");
        cantidadMaterias++;
    }
    	guardarNotasPorSemestre(semestre);
    	exportarHistorialAcademico();
}
//funcion ver avance curricular
void verAvanceCurricular(){
	int semestreActual = atoi(alumnoActual.semestre.c_str());
	if (semestreActual < 1 || semestreActual > TOTAL_SEMESTRES) {
		cout << "El semestre del alumno es invalido.\n";
		return; 
	}
	cout << "\n===== AVANCE CURRICULAR DEL ALUMNO =====\n";
	cout << "Nombre: " << alumnoActual.nombre << "\n";
	cout << "CI: " << alumnoActual.ci << "\n";
	cout << "Semestre actual: " << semestreActual << "\n\n";
for (int i = 0; i < semestreActual; i++) {
        cout << "Semestre " << (i + 1) << ":\n";
        for (int j = 0; j < 10; j++) {
            if (materiasPorSemestre[i][j] != "")
                cout << "- " << materiasPorSemestre[i][j] << "\n";
        }
        cout << "\n";
	}
	mostrarNotasGuardadas();
    cout << "========================================\n";
}
//funcion consultarHorarioDeClases
void consultarHorarioDeClases() {
    string dias[5] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes" };
    string horarios[10][5] = {
        { "Comunicacion Oral y Escrita", "Fisica I", "Logica de Programacion", "Matematica I", "Teoria de la Informatica" },
        { "Base de Datos I", "Datos I - Estructura", "Fisica II", "Laboratorio de Hardware", "Matematica II" },
        { "Fisica III", "Geometria Analitica", "Programacion I", "Sistemas Operativos (C-S)", "Lenguajes Visuales I" },
        { "Base de Datos II", "Ingles Tecnico", "Lenguajes Visuales II", "Matematica Discreta", "Programacion II" },
        { "Analisis de Sistemas", "Calculo Diferencial", "Economia y Finanzas", "Guarani", "Organizacion Empresarial" },
        { "Calculo Integral", "Herramientas de Diseno", "Liderazgo y Desarrollo", "Probabilidad y Estadistica", "Programacion IV" },
        { "Inteligencia Artificial", "Investigacion de Operaciones", "Programacion V", "Redes de Computadoras II", "Seguridad Informatica" },
        { "Administracion de TI", "Auditoria de Sistemas", "Datawarehouse", "Ingenieria de Software I", "Programacion VI" },
        { "Cloud Computing", "Data Center", "Electronica Digital I", "Ingenieria de Software II", "Legislacion y Etica Profesional" },
        { "Electronica Digital II", "Metodologia de la Investigacion", "Optativa II", "Practicas Laborales", "Robotica - Criptografia" }
    };
    int semestre;
    cout << "\nIngrese el numero de semestre (1 al 10): ";
    cin >> semestre;
    if (semestre < 1 || semestre > 10) {
        cout << "\nSemestre no valido. Ingrese un numero del 1 al 10.\n";
        return;
    }
    cout << "\n===== Horario de Clases - Semestre " << semestre << " =====\n\n";
    cout << "--------------------------------------------\n";
    cout << "| Dia       | Materia                      |\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < 5; i++) {
        cout << "| " << dias[i];
        for (int j = dias[i].length(); j < 10; j++) cout << " "; // espacio para alinear
        cout << "| " << horarios[semestre - 1][i];
        for (int j = horarios[semestre - 1][i].length(); j < 28; j++) cout << " "; // alinear materias
        cout << "|\n";
    }
    cout << "--------------------------------------------\n";
}
//funcion realizarEncuestaDocente
void realizarEncuestaDocente() {
    // Lista fija de docentes
    string docentes[5] = {
        "TANIS CORREA, LIEZ LAURENT - FISICA III",
        "MAIDANA GIMENEZ, RICARDO - PROGRAMACION I",
        "FERNANDEZ CUENCA, LUIS - GEOMETRIA ANALITICA",
        "CONTRERA SALINAS, MARCOS - LENGUAJES VISUALES I",
        "JARA CHAPARRO, CARMELO - SISTEMAS OPERATIVOS (C-S)"
    };
    string curso, fecha;
    int respuestas[9];
    string dimensiones[9] = {
        "1.1 Dominio de contenidos",
        "1.2 Objetivos claros",
        "2.1 Relacion con la profesion",
        "2.2 Organizacion del contenido",
        "2.3 Evaluaciones coherentes",
        "2.4 Participacion en investigacion o extension",
        "3.1 Uso de tecnologia",
        "4.1 Comunicacion con el alumno",
        "4.2 Empatia con el alumno"
    };
    cout << "\n==== EVALUACION DOCENTE ====\n";
    cout << "\nSeleccione el profesor:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << docentes[i] << "\n";
    }
    int opcionDocente;
    do {
        cout << "Opcion (1-5): ";
        cin >> opcionDocente;
        if (opcionDocente < 1 || opcionDocente > 5)
            cout << "Opcion invalida. Intente de nuevo.\n";
    } while (opcionDocente < 1 || opcionDocente > 5);
    cin.ignore();
    string docente = docentes[opcionDocente - 1];
    cout << "Curso: ";
    getline(cin, curso);
    cout << "Fecha: ";
    getline(cin, fecha);
    cout << "\nEscala de evaluacion (1 a 5):\n";
    for (int i = 0; i < 9; i++) {
        do {
            cout << dimensiones[i] << ": ";
            cin >> respuestas[i];
            if (respuestas[i] < 1 || respuestas[i] > 5)
                cout << "Valor invalido. Intente de nuevo.\n";
        } while (respuestas[i] < 1 || respuestas[i] > 5);
    }
    // Crear carpeta si no existe
    _mkdir("encuestas");
    // Armar nombre de archivo limpio
    string archivoNombre = "encuestas/";
    for (int i = 0; i < docente.length(); i++) {
        if (isalnum(docente[i]) || docente[i] == '_')
            archivoNombre += docente[i];
        else if (docente[i] == ' ')
            archivoNombre += '_';
    }
    archivoNombre += ".txt";
    // Guardar encuesta
    ofstream archivo(archivoNombre.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "Docente: " << docente << "\n";
        archivo << "Curso: " << curso << "\n";
        archivo << "Fecha: " << fecha << "\n";
        for (int i = 0; i < 9; i++) {
            archivo << dimensiones[i] << ": " << respuestas[i] << "\n";
        }
        archivo << "-----\n";
        archivo.close();
        cout << "Encuesta guardada correctamente.\n";
    } else {
        cout << "Error al guardar la encuesta.\n";
    }
}
//funcion exportar Historial Academico
void exportarHistorialAcademico() {
    // Armar carpeta final con año, curso y seccion
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    // Crear carpetas si no existen
    _mkdir(alumnoActual.anho.c_str());
    _mkdir(carpeta.c_str());
    // Armar nombre del archivo
    string nombreArchivo = carpeta + "/" + alumnoActual.nombre + "_" + alumnoActual.ci + "_historial.txt";
    // Reemplazar caracteres no válidos
    for (int i = 0; i < nombreArchivo.length(); i++) {
        if (!isalnum(nombreArchivo[i]) && nombreArchivo[i] != '_' && nombreArchivo[i] != '/' && nombreArchivo[i] != '.') {
            nombreArchivo[i] = '_';
        }
    }
    // Crear y escribir archivo
    ofstream archivo(nombreArchivo.c_str());
    if (archivo.is_open()) {
        archivo << "===== HISTORIAL ACADEMICO =====\n";
        archivo << "Nombre: " << alumnoActual.nombre << "\n";
        archivo << "CI: " << alumnoActual.ci << "\n";
        archivo << "Curso: " << alumnoActual.curso << " " << alumnoActual.seccion << " - " << alumnoActual.anho << "\n\n";
        archivo << "--- Materias ---\n";
        int semestreActual = atoi(alumnoActual.semestre.c_str());
        for (int s = 1; s <= semestreActual; s++) {
            stringstream ss;
            ss << s;
            string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ss.str() + ".txt";
            ifstream notas(archivoNotas.c_str());
            if (notas.is_open()) {
                string linea;
                while (getline(notas, linea)) {
                    stringstream ssLinea(linea);
                    string materia, porcentaje, escala;
                    getline(ssLinea, materia, ',');
                    getline(ssLinea, porcentaje, ',');
                    getline(ssLinea, escala);
                    archivo << materia << " - " << porcentaje << "% - Escala: " << escala << "\n";
                }
                notas.close();
            }
        }
        archivo.close();
        cout << "Historial guardado en: " << nombreArchivo << "\n";
    } else {
        cout << "Error al crear el archivo.\n";
    }
}
//funcion cambiar contrasena
void cambiarContrasena() {
    string contrasenaActual, nuevaContrasena, confirmarContrasena;
    int intentos = 0;
    cout << "\n===== CAMBIO DE CONTRASENA =====\n";
    cout << "Ingrese su contrasena actual: ";
    contrasenaActual = leerContrasenaOculta();
    if (contrasenaActual != alumnoActual.contrasena) {
        cout << "Contrasena incorrecta. Operacion cancelada.\n";
        return;
    }
    while (intentos < 3) {
        cout << "Ingrese nueva contrasena (letras + numeros, minimo 6 caracteres): ";
        nuevaContrasena = leerContrasenaOculta();
        if (!esContrasenaValida(nuevaContrasena)) {
            cout << "Contrasena insegura o invalida. Intente otra.\n";
            intentos++;
            continue;
        }
        cout << "Confirme la nueva contrasena: ";
        confirmarContrasena = leerContrasenaOculta();
        if (nuevaContrasena != confirmarContrasena) {
            cout << "Las contrasenas no coinciden. Intente de nuevo.\n";
            intentos++;
        } else {
            break;
        }
    }
    if (intentos == 3) {
        cout << "Demasiados intentos fallidos. Operacion cancelada.\n";
        return;
    }
	ifstream archivoEntrada("alumnos.txt");
    ofstream archivoTemporal("temp_alumnos.txt");
    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string nombre, ci, contrasena, curso, semestre, seccion, anho;
        getline(ss, nombre, ',');
        getline(ss, ci, ',');
        getline(ss, contrasena, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        if (ci == alumnoActual.ci) {
            archivoTemporal << nombre << "," << ci << "," << nuevaContrasena << ","
                            << curso << "," << semestre << "," << seccion << "," << anho << "\n";
            alumnoActual.contrasena = nuevaContrasena;
        } else {
            archivoTemporal << linea << "\n";
        }
    }
    archivoEntrada.close();
    archivoTemporal.close();
    remove("alumnos.txt");
    rename("temp_alumnos.txt", "alumnos.txt");
    cout << "Contrasena actualizada correctamente.\n";
}
//funcion para leer contrasena con asteriscos
string leerContrasenaOculta() {
    string contrasena;
    char ch;
    while ((ch = getch()) != '\r') { // Enter
        if (ch == '\b') { 
            if (!contrasena.empty()) {
                cout << "\b \b";
				contrasena = contrasena.substr(0, contrasena.length() - 1);
            }
        } else {
            contrasena += ch;
            cout << "*";
        }
    }
    cout << endl;
    return contrasena;
}
//funcion para validar la contrasena
bool esContrasenaValida(string pass) {
    if (pass.length() < 6) return false;
    bool tieneLetra = false, tieneNumero = false;
    for (int i = 0; i < pass.length(); i++) {
    if (isalpha(pass[i])) tieneLetra = true;
    if (isdigit(pass[i])) tieneNumero = true;
}
    string comunes[] = { "123456", "password", "abc123", "12345678", "qwerty", "111111" };
    for (int i = 0; i < 6; i++) {
    if (pass == comunes[i]) return false;
}
    return tieneLetra && tieneNumero;
}
//funcion cerrar sesion
void cerrarSesion(){	
	  cout << "\nCerrando sesion...\n";
}

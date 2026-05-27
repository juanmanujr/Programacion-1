//librerias incluidas que permiten que el sistema academico pueda mostrar informacion en consola
#include <iostream>//cout y cin
#include <fstream>//lectura y escritura de archivos
#include <conio.h>//para ingresar contraseñs de forma oculta con getch
#include <sstream>//para leer lineas de un archivo separado por comas
#include <string>//para trabajar  con texto de forma segura y flexible
#include <direct.h>//para usar mkdir para crear carpetas en el disco
#include <cstdlib>//para usar atoi para convertir de string a int
#include <vector>


using namespace std;
//definicion de la estructura de datos llamada alumno
struct Alumno {
	string nombre;
	string ci;
	string contrasena;
	string curso;
	string semestre;
	string seccion;
	string anho;
	string preguntaSeguridad;
	string respuestaSeguridad;
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

struct Docente {
    string nombre;
    string usuario;
    string contrasena;
    string materia;
    string anho;
    string curso;
    string seccion;
};

Docente docenteActual;

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

//funciones nuevas implementadas

void recuperarContrasena();
void mostrarEstadisticasAcademicas();
bool loginDocente(string usuario, string contrasena);
void mostrarMenuDocente();
void cargarCalificacionesDocente();
void verResultadosEncuestas();
void verAsignacionesDocente();
void registrarDocente();
string obtenerNombreArchivoEncuesta(string docenteNombre, string materia);
void crearDocentesPorDefecto();
float calcularPromedioGeneralEscala();
void cargarPlanificacionDocente();
string limpiarNombreArchivo(string original);
void cargarPlanCatedra();
void registrarMarcacion();
int leerOpcionValidada(int minimo, int maximo, const string& mensaje);
string leerTextoObligatorio(const string& mensaje);
string leerSoloNumeros(const string& mensaje);
string leerSeccionValida(const string& mensaje);
bool ciYaExiste(string ciBuscado);
float convertirAFloat(string entrada);

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
    { "Ver estadisticas academicas", mostrarEstadisticasAcademicas },
    { "Cerrar sesion", cerrarSesion }
    

};
const int CANTIDAD_OPCIONES_ALUMNO = sizeof(menuAlumno) / sizeof(menuAlumno[0]);

enum TipoUsuario { ALUMNO, ADMIN, DOCENTE };
TipoUsuario usuarioActual;


// FUNCION PRINCIPAL (MAIN) acceso a registro, inicio de sesion como alumno e inicio de sesion como administrador
int main() {
    crearDocentesPorDefecto();
    int opcion;
    do {
        cout << "\n===== BIENVENIDO AL SISTEMA =====\n";
        cout << "1. Registrar nuevo alumno\n";
        cout << "2. Iniciar sesion como alumno\n";
        cout << "3. Iniciar sesion como administrador\n";
        cout << "4. Iniciar sesion como docente\n";
        cout << "5. Recuperar contrasena\n";
        cout << "6. Salir\n";
        cout << "\n==================================\n";
        opcion = leerOpcionValidada(1, 6, "Seleccione una opcion: ");
        system("cls");
     
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
                passTemp = leerContrasenaOculta();
                if (loginAlumno(ciTemp, passTemp)) {
                    mostrarMenu(menuAlumno, CANTIDAD_OPCIONES_ALUMNO);
                }
                break;
            }
            case 3: {
                string usuario, contrasena;
                cin.ignore();
                cout << "Usuario: ";
                getline(cin, usuario);
                cout << "Contrasena: ";
                contrasena = leerContrasenaOculta();
                if (usuario == "admin" && contrasena == "admin123") {
                    cout << "Login exitoso como ADMINISTRADOR.\n";
                    mostrarMenuAdmin();
                } else {
                    cout << "Credenciales incorrectas.\n";
                }
                break;
            }
            case 4: {
                string usuarioDocente, contrasenaDocente;
                cin.ignore();
                cout << "Usuario docente: ";
                getline(cin, usuarioDocente);
                cout << "Contrasena: ";
                contrasenaDocente = leerContrasenaOculta();
                if (loginDocente(usuarioDocente, contrasenaDocente)) {
                    usuarioActual = DOCENTE;
                    mostrarMenuDocente();
                } else {
                    cout << "Credenciales incorrectas.\n";
                }
                break;
            }
            case 5:
                recuperarContrasena();
                break;
            case 6:
                cout << "Hasta luego\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}

//FUNCIONES
//funcion registrar alumno
void registrarAlumno() {
    Alumno nuevo;
    cin.ignore();

    nuevo.nombre = leerTextoObligatorio("Nombre completo: ");

    do {
        nuevo.ci = leerSoloNumeros("CI: ");
        if (ciYaExiste(nuevo.ci)) {
            cout << "Este CI ya esta registrado. Intente con otro.\n";
        }
    } while (ciYaExiste(nuevo.ci));

    nuevo.contrasena = leerContrasenaOculta();

    nuevo.curso = leerSoloNumeros("Curso (1 a 5): ");
    nuevo.semestre = leerSoloNumeros("Semestre actual (1 al 10): ");
    nuevo.seccion = leerSeccionValida("Seccion (A o B): ");
    nuevo.anho = leerSoloNumeros("Anho: ");
    nuevo.preguntaSeguridad = leerTextoObligatorio("Pregunta de seguridad: ");
    nuevo.respuestaSeguridad = leerTextoObligatorio("Respuesta: ");

    ofstream archivo("alumnos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevo.nombre << "," << nuevo.ci << "," << nuevo.contrasena << ","
                << nuevo.curso << "," << nuevo.semestre << "," << nuevo.seccion << ","
                << nuevo.anho << "," << nuevo.preguntaSeguridad << "," << nuevo.respuestaSeguridad << "\n";

        archivo.close();
        cout << "\n>>> Registro exitoso.\n";
    } else {
        cout << "\n>>> Error al guardar el alumno.\n";
    }

    system("pause");
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
        cout << "5. Registrar docente\n";
        cout << "6. Salir del menu admin\n";
        opcion = leerOpcionValidada(1, 6, "Seleccione una opcion: ");
        system("cls");

        switch (opcion) {
            case 1:
                system("cls");
                accionCargarNotas();
                break;
            case 2:
                system("cls");
                accionVerHistoriales();
                break;
            case 3:
                system("cls");
                accionBuscarPorNombreOCi();
                break;
            case 4:
                system("cls");
                accionBuscarPorPalabra();
                break;
            case 5:
                system("cls");
                registrarDocente();
                break;
            case 6:
                system("cls");
                cout << "Saliendo del menu admin...\n";
                break;
            default:
                system("cls");
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 6);
}

//funciones para cada opcion del admin
//funcion accionCargarNotas
void accionCargarNotas(){
	string ci = leerSoloNumeros("Ingrese el CI del alumno para cargar sus notas: ");


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
	string palabra = leerTextoObligatorio("Ingrese palabra clave a buscar en los historiales: ");

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
        opcion = leerOpcionValidada(1, 8, "Seleccione una opcion: ");
        system("cls");
        cin.ignore();

        if (opcion >= 1 && opcion <= cantidad) {
            system("cls"); // limpiar pantalla antes de ejecutar la función
            opciones[opcion - 1].funcion();
        } else {
            system("cls"); // también limpiar si hay un error
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
	float promedioEscala = calcularPromedioGeneralEscala();
	cout << "\nPromedio general acumulado (escala 1 a 5): " << promedioEscala;
	
	
    cout << "\n\n========================================\n";
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

    string lineaDocente = docentes[opcionDocente - 1];
    int separador = lineaDocente.find(" - ");
    string docenteNombre = lineaDocente.substr(0, separador);
    string materia = lineaDocente.substr(separador + 3);
    string archivoNombre = obtenerNombreArchivoEncuesta(docenteNombre, materia);

    _mkdir("encuestas");

    // Obtener semestre actual del alumno
    string semestre = alumnoActual.semestre;

    // Verificar si ya completó encuesta en este semestre para ese docente
    ifstream archivoVerificacion(archivoNombre.c_str());
    string linea;
    bool yaRespondio = false;

    while (getline(archivoVerificacion, linea)) {
        if (linea.find("CI: " + alumnoActual.ci) != string::npos) {
            // Verificamos también el semestre
            string siguienteLinea;
            getline(archivoVerificacion, siguienteLinea);
            if (siguienteLinea.find("Semestre: " + semestre) != string::npos) {
                yaRespondio = true;
                break;
            }
        }
    }
    archivoVerificacion.close();

    if (yaRespondio) {
        cout << "\nYa has completado esta encuesta para este docente en este semestre.\n";
        return;
    }

   curso = leerTextoObligatorio("Curso: ");
   fecha = leerTextoObligatorio("Fecha: ");

    cout << "\nEscala de evaluacion (1 a 5):\n";
    for (int i = 0; i < 9; i++) {
        do {
            cout << dimensiones[i] << ": ";
            cin >> respuestas[i];
            if (respuestas[i] < 1 || respuestas[i] > 5)
                cout << "Valor invalido. Intente de nuevo.\n";
        } while (respuestas[i] < 1 || respuestas[i] > 5);
    }

    ofstream archivo(archivoNombre.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "Docente: " << docenteNombre << " - " << materia << "\n";
        archivo << "CI: " << alumnoActual.ci << "\n";
        archivo << "Semestre: " << semestre << "\n";
        archivo << "Curso: " << curso << "\n";
        archivo << "Fecha: " << fecha << "\n";
        for (int i = 0; i < 9; i++) {
            archivo << dimensiones[i] << ": " << respuestas[i] << "\n";
        }
        archivo << "-----\n";
        archivo.close();
        cout << "\nEncuesta guardada correctamente.\n";
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
///////////////////////////////
//funciones nuevas añadidas
//funcion recuperar contrasena
void recuperarContrasena() {
    string ci, respuesta, nuevaPass;
    ifstream archivo("alumnos.txt");
    ofstream temp("temp.txt");
    bool encontrado = false;
    string linea;
    cin.ignore();
	ci = leerSoloNumeros("Ingrese su CI: ");

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, ciArchivo, pass, curso, semestre, seccion, anho, pregunta, resp;
        getline(ss, nombre, ',');
        getline(ss, ciArchivo, ',');
        getline(ss, pass, ',');
        getline(ss, curso, ',');
        getline(ss, semestre, ',');
        getline(ss, seccion, ',');
        getline(ss, anho, ',');
        getline(ss, pregunta, ',');
        getline(ss, resp);  
        if (ci == ciArchivo) {
            encontrado = true;
            cout << "Pregunta de seguridad: " << pregunta << "\n";
            cout << "Respuesta: ";
            getline(cin, respuesta);
            if (respuesta == resp) {
                int intentos = 0;
                while (intentos < 3) {
                    cout << "Nueva contrasena (minimo 6 caracteres, letras y numeros): ";
                    nuevaPass = leerContrasenaOculta();
                    if (!esContrasenaValida(nuevaPass)) {
                        cout << "Contrasena insegura o invalida. Intente otra.\n";
                        intentos++;
                        continue;
                    }
                    break;
                }
                if (intentos == 3) {
                    cout << "Demasiados intentos fallidos. Operacion cancelada.\n";
                    temp << linea << "\n"; // Guarda la línea original sin cambios
                } else {
                    temp << nombre << "," << ciArchivo << "," << nuevaPass << ","
                         << curso << "," << semestre << "," << seccion << "," << anho << ","
                         << pregunta << "," << resp << "\n";
                    cout << "Contrasena actualizada correctamente.\n";
                }
            } else {
                cout << "Respuesta incorrecta. No se pudo recuperar la contraseña.\n";
                temp << linea << "\n";
            }
        } else {
            temp << linea << "\n";
        }
    }
    archivo.close();
    temp.close();
    remove("alumnos.txt");
    rename("temp.txt", "alumnos.txt");
    if (!encontrado)
        cout << "CI no encontrado.\n";
}
//funcion mostrar estadisticas academicas
void mostrarEstadisticasAcademicas() {
    int semestreActual = atoi(alumnoActual.semestre.c_str());
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    float total = 0;
    int totalMaterias = 0, aprobadas = 0, reprobadas = 0;
    for (int s = 1; s <= semestreActual; s++) {
        stringstream ss;
        ss << s;
        string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ss.str() + ".txt";
        ifstream archivo(archivoNotas.c_str());
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string materia, porcentajeStr, escalaStr;
                getline(ss, materia, ',');
                getline(ss, porcentajeStr, ',');
                getline(ss, escalaStr);
                float porcentaje = atof(porcentajeStr.c_str());
                int escala = atoi(escalaStr.c_str());
                total += porcentaje;
                totalMaterias++;
                if (escala >= 2) aprobadas++;
                else reprobadas++;
            }
            archivo.close();
        }
    }
    if (totalMaterias > 0) {
        float promedioEscala = calcularPromedioGeneralEscala();
        cout << "\n===== ESTADISTICAS ACADEMICAS =====\n";
        cout << "Materias totales: " << totalMaterias << "\n";
        cout << "Materias aprobadas: " << aprobadas << "\n";
        cout << "Materias reprobadas: " << reprobadas << "\n";
        cout << "Promedio general: " << promedioEscala << "\n";
        cout << "===================================\n";
    } else {
        cout << "No hay datos disponibles para calcular estadísticas.\n";
    }
}
//funcion mostrar menu docente
void mostrarMenuDocente() {
    int opcion;
    do {
        cout << "\n===== MENU DOCENTE =====\n";
        cout << "1. Cargar calificaciones\n";
        cout << "2. Ver resultados de encuestas\n";
        cout << "3. Ver mis asignaciones\n";
        cout << "4. Cargar planificacion\n";
        cout << "5. Cargar plan de catedra\n";
        cout << "6. Registrar marcacion\n"; 
        cout << "7. Cerrar sesion\n";
        opcion = leerOpcionValidada(1, 7, "Seleccione una opcion: ");
        system("cls");
        //cin.ignore();
        switch (opcion) {
            case 1:
                system("cls");
                cargarCalificacionesDocente();
                break;
            case 2:
                system("cls");
                verResultadosEncuestas();
                break;
            case 3:
                system("cls");
                verAsignacionesDocente();
                break;
            case 4:
                system("cls");
                cargarPlanificacionDocente();
                break;
            case 5:
                system("cls");
                cargarPlanCatedra();
                break;
            case 6:
                system("cls");
                registrarMarcacion();
                break;
            case 7:
                system("cls");
                cout << "Sesion cerrada.\n";
                break;
            default:
                system("cls");
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);
}

//funcion registrar docente, esto se hace en el menu admin
void registrarDocente() {
    Docente nuevo;
    cin.ignore();

    nuevo.nombre = leerTextoObligatorio("Nombre completo: ");
    nuevo.usuario = leerTextoObligatorio("Usuario: ");
    nuevo.contrasena = leerContrasenaOculta();
    nuevo.materia = leerTextoObligatorio("Materia que ensena (tal como figura en el sistema): ");
    nuevo.anho = leerSoloNumeros("Anho (ej: 2025): ");
    nuevo.curso = leerSoloNumeros("Curso (1-5): ");
    nuevo.seccion = leerSeccionValida("Seccion (A o B): ");

    ofstream archivo("docentes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevo.nombre << "," << nuevo.usuario << "," << nuevo.contrasena << ","
                << nuevo.materia << "," << nuevo.anho << "," << nuevo.curso << "," << nuevo.seccion << "\n";
        archivo.close();
        cout << "\nDocente registrado exitosamente.\n";
    } else {
        cout << "\nError al abrir docentes.txt\n";
    }

    system("pause");
}

//funcion verAsignacionesDocente
void verAsignacionesDocente() {
    cout << "\n===== ASIGNACION DEL DOCENTE =====\n";
    cout << "Docente: " << docenteActual.nombre << "\n";
    cout << "Materia asignada: " << docenteActual.materia << "\n";
    cout << "Curso: " << docenteActual.curso << " " << docenteActual.seccion << " - Anho " << docenteActual.anho << "\n";
    cout << "==================================\n";
}
//funcion loginDocente
bool loginDocente(string usuario, string contrasena) {
    ifstream archivo("docentes.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de docentes.\n";
        return false;
    }
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, usuarioArchivo, contrasenaArchivo, materia, anho, curso, seccion;
 	  		getline(ss, nombre, ';');
			getline(ss, usuarioArchivo, ';');
			getline(ss, contrasenaArchivo, ';');
			getline(ss, materia, ';');
			getline(ss, anho, ';');
			getline(ss, curso, ';');
		 	getline(ss, seccion, ';');
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            docenteActual.nombre = nombre;
            docenteActual.usuario = usuarioArchivo;
            docenteActual.contrasena = contrasenaArchivo;
            docenteActual.materia = materia;
            docenteActual.anho = anho;
            docenteActual.curso = curso;
            docenteActual.seccion = seccion;
            cout << "Login exitoso. Bienvenido/a, " << docenteActual.nombre << ".\n";
            return true;
        }
    }
    cout << "Usuario o contrasenha incorrectos.\n";
    return false;
}
//funcion crear docentes por defecto
void crearDocentesPorDefecto() {
    ifstream test("docentes.txt");
    if (test.is_open()) {
        test.close();
        return; // ya existe
    }
    ofstream archivo("docentes.txt");
    if (archivo.is_open()) {
        archivo << "TANIS CORREA, LIEZ LAURENT,taniscorrea,1234,FISICA III,2025,3,B\n";
        archivo << "MAIDANA GIMENEZ, RICARDO,maidanagimenez,1234,PROGRAMACION I,2025,3,B\n";
        archivo << "FERNANDEZ CUENCA, LUIS,fernandezcuenca,1234,GEOMETRIA ANALITICA,2025,3,B\n";
        archivo << "CONTRERA SALINAS, MARCOS,contrerasalinas,1234,LENGUAJES VISUALES I,2025,3,B\n";
        archivo << "JARA CHAPARRO, CARMELO,jarachaparro,1234,SISTEMAS OPERATIVOS (C-S),2025,3,B\n";
        archivo.close();
        cout << "Archivo de docentes creado por defecto.\n";
    }
}
//funcion verResultadosEncuestas
void verResultadosEncuestas() {
    string nombreArchivo = obtenerNombreArchivoEncuesta(docenteActual.nombre, docenteActual.materia);
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "No se encontraron encuestas para este docente.\n";
        return;
    }
    cout << "\n===== RESULTADOS DE ENCUESTAS =====\n";
    string linea;
    int totalSuma = 0;
    int totalRespuestas = 0;
    while (getline(archivo, linea)) {
        cout << linea << "\n";
        size_t pos = linea.find(": ");
        if (pos != string::npos) {
            string valorStr = linea.substr(pos + 2); // obtiene lo que está después de ": "         
            // limpiar posibles espacios o saltos de línea
            while (!valorStr.empty() && (valorStr[valorStr.length() - 1] == '\n' || valorStr[valorStr.length() - 1] == '\r' || valorStr[valorStr.length() - 1] == ' '))
                valorStr.erase(valorStr.length() - 1);
            while (!valorStr.empty() && valorStr[0] == ' ')
                valorStr.erase(0, 1);
            int valor = atoi(valorStr.c_str());
            if (valor >= 1 && valor <= 5) {
                totalSuma += valor;
                totalRespuestas++;
            }
        }
    }
    archivo.close();
    cout << "===================================\n";
    if (totalRespuestas > 0) {
        float promedioGeneral = (float)totalSuma / totalRespuestas;
        cout << "Cantidad total de respuestas: " << totalRespuestas << "\n";
        cout << "Promedio general de evaluacion: " << promedioGeneral <<"\n";   
    } else {
        cout << "No hay respuestas registradas para calcular promedio.\n";
    }
}
//obtenerAlumnosdelCursoDocente
vector<Alumno> obtenerAlumnosDelCursoDocente() {
    vector<Alumno> lista;
    ifstream archivo("alumnos.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Alumno a;
        getline(ss, a.nombre, ',');
        getline(ss, a.ci, ',');
        getline(ss, a.contrasena, ',');
        getline(ss, a.curso, ',');
        getline(ss, a.semestre, ',');
        getline(ss, a.seccion, ',');
        getline(ss, a.anho, ',');
        getline(ss, a.preguntaSeguridad, ',');
        getline(ss, a.respuestaSeguridad);

        if (a.anho == docenteActual.anho &&
            a.curso == docenteActual.curso &&
            a.seccion == docenteActual.seccion) {
            lista.push_back(a);
        }
    }

    return lista;
}
//funcion aMayusculas
string aMayusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}


//funcion cargarCAlificacionesDocente
void cargarCalificacionesDocente() {
    vector<Alumno> alumnosFiltrados;
    ifstream archivo("alumnos.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Alumno a;
        getline(ss, a.nombre, ',');
        getline(ss, a.ci, ',');
        getline(ss, a.contrasena, ',');
        getline(ss, a.curso, ',');
        getline(ss, a.semestre, ',');
        getline(ss, a.seccion, ',');
        getline(ss, a.anho, ',');
        getline(ss, a.preguntaSeguridad, ',');
        getline(ss, a.respuestaSeguridad);
        if (a.anho == docenteActual.anho &&
            a.curso == docenteActual.curso &&
            aMayusculas(a.seccion) == aMayusculas(docenteActual.seccion)) {
            alumnosFiltrados.push_back(a);
        }
    }
    archivo.close();
    if (alumnosFiltrados.empty()) {
        cout << "No hay alumnos registrados para este curso, anho y seccion.\n";
        return;
    }
    cout << "\n===== ALUMNOS DEL CURSO =====\n";
    for (int i = 0; i < alumnosFiltrados.size(); i++) {
        cout << i + 1 << ". " << alumnosFiltrados[i].nombre << " (CI: " << alumnosFiltrados[i].ci << ")\n";
    }
    int seleccion;
    do {
        cout << "Seleccione un alumno (1-" << alumnosFiltrados.size() << "): ";
        cin >> seleccion;
    } while (seleccion < 1 || seleccion > alumnosFiltrados.size());
    alumnoActual = alumnosFiltrados[seleccion - 1];
    int semestre;
    cout << "Semestre (1 al 10): ";
    cin >> semestre;
    // Datos para calcular nota final
    float parcial1, maxParcial1;
    float parcial2, maxParcial2;
    float trabajoPractico, maxTP;
    float examenFinal, maxEF;
    float porcentajeTotal;
    int notaEscala;
    maxParcial1 = convertirAFloat(leerSoloNumeros("Puntaje max Parcial 1: "));
	parcial1    = convertirAFloat(leerSoloNumeros("Nota Parcial 1: "));
	maxParcial2 = convertirAFloat(leerSoloNumeros("Puntaje max Parcial 2: "));
	parcial2    = convertirAFloat(leerSoloNumeros("Nota Parcial 2: "));
	maxTP       = convertirAFloat(leerSoloNumeros("Puntaje max Trabajo Practico: "));
	trabajoPractico = convertirAFloat(leerSoloNumeros("Nota Trabajo Practico: "));
	maxEF       = convertirAFloat(leerSoloNumeros("Puntaje max Examen Final: "));
	examenFinal = convertirAFloat(leerSoloNumeros("Nota Examen Final: "));
   
    porcentajeTotal = (parcial1 / maxParcial1) * 15 +
                      (parcial2 / maxParcial2) * 15 +
                      (trabajoPractico / maxTP) * 10 +
                      (examenFinal / maxEF) * 60;
    if (porcentajeTotal < 60) notaEscala = 1;
    else if (porcentajeTotal < 70) notaEscala = 2;
    else if (porcentajeTotal < 80) notaEscala = 3;
    else if (porcentajeTotal < 90) notaEscala = 4;
    else notaEscala = 5;
    // Crear carpeta
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    _mkdir(alumnoActual.anho.c_str());
    _mkdir(carpeta.c_str());
    // Archivo del semestre
    stringstream ss;
    ss << semestre;
    string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ss.str() + ".txt";
    // Leer archivo y reescribir sin duplicar materia
    ifstream archivoOriginal(archivoNotas.c_str());
    ofstream archivoTemp("temp_notas.txt");
    string lineaNota;
    bool yaExiste = false;
    while (getline(archivoOriginal, lineaNota)) {
        if (lineaNota.find(docenteActual.materia) != string::npos) {
            yaExiste = true;
        } else {
            archivoTemp << lineaNota << "\n";
        }
    }
    archivoOriginal.close();
    archivoTemp << docenteActual.materia << "," << porcentajeTotal << "," << notaEscala << "\n";
    archivoTemp.close();
    remove(archivoNotas.c_str());
    rename("temp_notas.txt", archivoNotas.c_str());
    cout << "\n--- Resumen ---\n";
    cout << "Porcentaje calculado: " << porcentajeTotal << "%\n";
    cout << "Escala: " << notaEscala << "\n";
    cout << (notaEscala >= 2 ? "Estado: APROBADO\n" : "Estado: REPROBADO\n");
    if (yaExiste)
        cout << "Nota actualizada.\n";
    else
        cout << "Nota registrada.\n";
}

//funcion obtenerNombreARchivoEncuesta
string obtenerNombreArchivoEncuesta(string docenteNombre, string materia) {
    string nombreArchivo = "encuestas/";
    string combinado = docenteNombre + " - " + materia;
    for (int i = 0; i < combinado.length(); i++) {
        char c = combinado[i];
        if (isalnum(c) || c == '_')
            nombreArchivo += c;
        else
            nombreArchivo += '_';
    }
    nombreArchivo += ".txt";
    return nombreArchivo;
}
//funcion calcularPromedioGeneralEscala
float calcularPromedioGeneralEscala() {
    int semestreActual = atoi(alumnoActual.semestre.c_str());
    string carpeta = alumnoActual.anho + "/";
    if (alumnoActual.curso == "1") carpeta += "1er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "2") carpeta += "2do_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "3") carpeta += "3er_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "4") carpeta += "4to_curso_" + alumnoActual.seccion;
    else if (alumnoActual.curso == "5") carpeta += "5to_curso_" + alumnoActual.seccion;
    else carpeta += "otros";
    int totalNotas = 0;
    int cantidadNotas = 0;
    for (int s = 1; s <= semestreActual; s++) {
        stringstream ss;
        ss << s;
        string archivoNotas = carpeta + "/" + alumnoActual.ci + "_semestre" + ss.str() + ".txt";
        ifstream archivo(archivoNotas.c_str());
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss2(linea);
                string materia, porcentajeStr, escalaStr;
                getline(ss2, materia, ',');
                getline(ss2, porcentajeStr, ',');
                getline(ss2, escalaStr);
                int escala = atoi(escalaStr.c_str());
                totalNotas += escala;
                cantidadNotas++;
            }
            archivo.close();
        }
    }
    if (cantidadNotas > 0) {
        return (float)totalNotas / cantidadNotas;
    } else {
        return 0.0;
    }
}
//funcion cargarPlanificacionDocente
void cargarPlanificacionDocente() {
    string carreraOriginal, carreraLimpia, seccion, semana, fechaDesde, contenido;
    int horasTeoricas, horasPracticas, horasTotales;
    cout << "\n===== CARGAR PLANIFICACION DOCENTE =====\n";
    carreraOriginal = leerTextoObligatorio("Carrera: ");
	carreraLimpia = limpiarNombreArchivo(carreraOriginal);

	seccion = leerSeccionValida("Seccion (A o B): ");
	horasTeoricas  = convertirAFloat(leerSoloNumeros("Horas teoricas: "));
	horasPracticas = convertirAFloat(leerSoloNumeros("Horas practicas: "));
	horasTotales = horasTeoricas + horasPracticas;

	cout << "Horas totales: " << horasTotales << "\n";

	semana = leerTextoObligatorio("Semana (ej. Semana 1): ");
	fechaDesde = leerTextoObligatorio("Fecha desde (ej. 12/08/2025): ");
	contenido = leerTextoObligatorio("Contenido a desarrollar: ");
  
    // Crear carpetas
    _mkdir("carreras");
    string carpetaCarrera = "carreras/" + carreraLimpia;
    _mkdir(carpetaCarrera.c_str());
    // Crear nombre de archivo: carreras/CARRERA/NOMBRE-MATERIA.txt
    string nombreArchivo = carpetaCarrera + "/";
    nombreArchivo += limpiarNombreArchivo(docenteActual.nombre + " - " + docenteActual.materia) + ".txt";
    // Guardar información
    ofstream archivo(nombreArchivo.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "===== CARGAR PLANIFICACION DOCENTE =====\n";
        archivo << "Carrera: " << carreraOriginal << "\n";
        archivo << "Seccion: " << seccion << "\n";
        archivo << "Horas teoricas: " << horasTeoricas << "\n";
        archivo << "Horas practicas: " << horasPracticas << "\n";
        archivo << "Horas totales: " << horasTotales << "\n";
        archivo << "Semana: " << semana << "\n";
        archivo << "Fecha desde: " << fechaDesde << "\n";
        archivo << "Contenido a desarrollar: " << contenido << "\n";
        archivo << "Planificacion guardada correctamente.\n";
        archivo << "------------------------------------------\n";
        archivo.close();
        cout << "Planificacion guardada correctamente.\n";
    } else {
        cout << "Error al guardar la planificacion.\n";
    }
}
//funcion limpiarNombreArchivo
string limpiarNombreArchivo(string original) {
    string limpio = "";
    for (int i = 0; i < original.length(); i++) {
        char c = original[i];
        if (isalnum(c) || c == '_' || c == '-') limpio += c;
        else limpio += '_';
    }
    return limpio;
}
//funcion cargarPlanCatedra
void cargarPlanCatedra() {
    string materia, semana, fechaDesde, contenidosPlan, objetivos, estrategiasPlan;
    string contenidosProfesor, recursos, estrategiasProfesor, observaciones;
    cout << "\n===== CARGAR PLAN DE CATEDRA =====\n";
    cin.ignore();
	materia = leerTextoObligatorio("Materia: ");
	semana = leerTextoObligatorio("Semana: ");
	fechaDesde = leerTextoObligatorio("Fecha desde (ej. 12/08/2025): ");
	contenidosPlan = leerTextoObligatorio("Contenidos de planificacion: ");
	objetivos = leerTextoObligatorio("Objetivos de planificacion: ");
	estrategiasPlan = leerTextoObligatorio("Estrategias de planificacion: ");
	contenidosProfesor = leerTextoObligatorio("Contenidos del profesor: ");
	recursos = leerTextoObligatorio("Recursos del profesor: ");
	estrategiasProfesor = leerTextoObligatorio("Estrategias del profesor: ");
	observaciones = leerTextoObligatorio("Observaciones: ");
    // Crear carpeta
    _mkdir("plan_de_catedra");
    // Crear nombre de archivo limpio
    string nombreArchivo = "plan_de_catedra/plancatedra_" + limpiarNombreArchivo(docenteActual.nombre) + ".txt";
    // Guardar la información
    ofstream archivo(nombreArchivo.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "===== PLAN DE CATEDRA =====\n";
        archivo << "Materia: " << materia << "\n";
        archivo << "Semana: " << semana << "\n";
        archivo << "Fecha desde: " << fechaDesde << "\n";
        archivo << "Contenidos de planificacion: " << contenidosPlan << "\n";
        archivo << "Objetivos de planificacion: " << objetivos << "\n";
        archivo << "Estrategias de planificacion: " << estrategiasPlan << "\n";
        archivo << "Contenidos del profesor: " << contenidosProfesor << "\n";
        archivo << "Recursos del profesor: " << recursos << "\n";
        archivo << "Estrategias del profesor: " << estrategiasProfesor << "\n";
        archivo << "Observaciones: " << observaciones << "\n";
        archivo << "------------------------------------------\n";
        archivo.close();
        cout << "Plan de catedra guardado correctamente.\n";
    } else {
        cout << "Error al guardar el plan de catedra.\n";
    }
}
//funcion registrarMarcacion
void registrarMarcacion() {
    string materia, tipo, fecha, hora, observacion;
    cout << "\n===== REGISTRAR MARCACION =====\n";
    cin.ignore();
	materia = leerTextoObligatorio("Materia: ");

	do {
    	tipo = leerTextoObligatorio("Tipo (Entrada/Salida): ");
    	for (int i = 0; i < tipo.length(); i++) tipo[i] = tolower(tipo[i]);
    	if (tipo != "entrada" && tipo != "salida")
        cout << "Tipo invalido. Debe ser 'Entrada' o 'Salida'.\n";
	} while (tipo != "entrada" && tipo != "salida");

	fecha = leerTextoObligatorio("Fecha (ej. 25/06/2025): ");
	hora = leerTextoObligatorio("Hora (ej. 13:45): ");
	observacion = leerTextoObligatorio("Observacion: ");
    // Crear carpeta
    _mkdir("marcaciones");
    // Crear archivo: marcaciones/marcacion_NOMBRE.txt
    string nombreArchivo = "marcaciones/marcacion_" + limpiarNombreArchivo(docenteActual.nombre) + ".txt";
    // Guardar la marcación
    ofstream archivo(nombreArchivo.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "===== MARCACION =====\n";
        archivo << "Docente: " << docenteActual.nombre << "\n";
        archivo << "Materia: " << materia << "\n";
        archivo << "Tipo: " << tipo << "\n";
        archivo << "Fecha: " << fecha << "\n";
        archivo << "Hora: " << hora << "\n";
        archivo << "Observacion: " << observacion << "\n";
        archivo << "--------------------------\n";
        archivo.close();
        cout << "Marcacion registrada correctamente.\n";
    } else {
        cout << "Error al guardar la marcacion.\n";
    }
}
//funcion leerOpcionValida
int leerOpcionValidada(int minimo, int maximo, const string& mensaje) {
    string entrada;
    int opcion;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);
        if ((ss >> opcion) && !(ss >> entrada)) {
            if (opcion >= minimo && opcion <= maximo)
                return opcion;
        }
        cout << "Entrada invalida. Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
    }
}
//funcion leertextoobligatorio
string leerTextoObligatorio(const string& mensaje) {
    string entrada;
    do {
        cout << mensaje;
        getline(cin, entrada);
        if (entrada.empty())
            cout << "Este campo es obligatorio. Intente de nuevo.\n";
    } while (entrada.empty());
    return entrada;
}
//funcionleersolonumeros
string leerSoloNumeros(const string& mensaje) {
    string entrada;
    bool esValido;
    do {
        esValido = true;
        cout << mensaje;
        getline(cin, entrada);
        if (entrada.empty()) {
            cout << "Este campo es obligatorio.\n";
            esValido = false;
        }
        for (int i = 0; i < entrada.length(); i++) {
            if (!isdigit(entrada[i])) {
                cout << "Solo se permiten numeros.\n";
                esValido = false;
                break;
            }
        }
    } while (!esValido);
    return entrada;
}
//funcionleerseccionvalida
string leerSeccionValida(const string& mensaje) {
    string seccion;
    do {
        cout << mensaje;
        getline(cin, seccion);
        if (seccion != "A" && seccion != "B") {
            cout << "Seccion invalida. Debe ser A o B.\n";
        }
    } while (seccion != "A" && seccion != "B");
    return seccion;
}
//funcion ciyaexiste
bool ciYaExiste(string ciBuscado) {
    ifstream archivo("alumnos.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, ci;
        getline(ss, nombre, ',');
        getline(ss, ci, ',');
        if (ci == ciBuscado) {
            return true;
        }
    }
    return false;
}
//funcion convertirAFloat
float convertirAFloat(string entrada) {
    stringstream ss(entrada);
    float valor;
    ss >> valor;
    return valor;
}


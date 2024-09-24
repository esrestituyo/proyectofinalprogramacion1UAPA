#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>

// Clases de motores

class Motor {
protected:
    std::string codigo;             // Código único de 12 caracteres
    std::string fechaSalida;        // Fecha de salida del área de ensamblaje
    std::string especialista;       // Nombre del especialista que realizó la certificación
    int vecesReensamblado;          // Veces que ha regresado al área de ensamblaje por defectos

public:
    // Constructor
    Motor(std::string codigo, std::string fechaSalida, std::string especialista, int vecesReensamblado)
        : codigo(codigo), fechaSalida(fechaSalida), especialista(especialista), vecesReensamblado(vecesReensamblado) {}

    // Métodos getters y setters
    std::string getCodigo() const { return codigo; }
    void setCodigo(const std::string& codigo) { this->codigo = codigo; }

    std::string getFechaSalida() const { return fechaSalida; }
    void setFechaSalida(const std::string& fechaSalida) { this->fechaSalida = fechaSalida; }

    std::string getEspecialista() const { return especialista; }
    void setEspecialista(const std::string& especialista) { this->especialista = especialista; }

    int getVecesReensamblado() const { return vecesReensamblado; }
    void setVecesReensamblado(int veces) { vecesReensamblado = veces; }

    // Método virtual para calcular el costo (será sobreescrito en las clases derivadas)
    virtual double calcularCosto() const = 0;

    // Método virtual para mostrar información del motor
    virtual void mostrarFichaTecnica() const;
};

void Motor::mostrarFichaTecnica() const {
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Fecha de salida: " << fechaSalida << std::endl;
    std::cout << "Especialista: " << especialista << std::endl;
    std::cout << "Veces reensamblado: " << vecesReensamblado << std::endl;
}

// Clases derivadas de Motor

class MotorAlta : public Motor {
private:
    double maxRPM;    // Máximas revoluciones por minuto
    double consumo;   // Consumo en km por litro

public:
    // Constructor
    MotorAlta(std::string codigo, std::string fechaSalida, std::string especialista, int vecesReensamblado,
              double maxRPM, double consumo)
        : Motor(codigo, fechaSalida, especialista, vecesReensamblado), maxRPM(maxRPM), consumo(consumo) {}

    // Métodos getters y setters
    double getMaxRPM() const { return maxRPM; }
    void setMaxRPM(double rpm) { maxRPM = rpm; }

    double getConsumo() const { return consumo; }
    void setConsumo(double consumo) { this->consumo = consumo; }

    // Sobrescribir el método para calcular el costo
    double calcularCosto() const override {
        return (maxRPM * 1.5 + consumo) - 100 * vecesReensamblado;
    }

    // Sobrescribir el método para mostrar información
    void mostrarFichaTecnica() const override;
};

void MotorAlta::mostrarFichaTecnica() const {
    Motor::mostrarFichaTecnica();
    std::cout << "Máximas RPM: " << maxRPM << std::endl;
    std::cout << "Consumo (km/l): " << consumo << std::endl;
    std::cout << "Costo: " << calcularCosto() << std::endl;
}

class MotorFuerza : public Motor {
private:
    int caballosFuerza;    // Caballos de fuerza (entre 80 y 4000)

public:
    // Constructor
    MotorFuerza(std::string codigo, std::string fechaSalida, std::string especialista, int vecesReensamblado,
                int caballosFuerza)
        : Motor(codigo, fechaSalida, especialista, vecesReensamblado), caballosFuerza(caballosFuerza) {}

    // Métodos getters y setters
    int getCaballosFuerza() const { return caballosFuerza; }
    void setCaballosFuerza(int caballos) { caballosFuerza = caballos; }

    // Sobrescribir el método para calcular el costo
    double calcularCosto() const override {
        return (caballosFuerza) * (5 - 100 * vecesReensamblado);
    }

    // Sobrescribir el método para mostrar información
    void mostrarFichaTecnica() const override;
};

void MotorFuerza::mostrarFichaTecnica() const {
    Motor::mostrarFichaTecnica();
    std::cout << "Caballos de fuerza: " << caballosFuerza << std::endl;
    std::cout << "Costo: " << calcularCosto() << std::endl;
}

class MotorTrabajo : public Motor {
private:
    bool artesanal;    // Indica si es artesanal (true) o no (false)

public:
    // Constructor
    MotorTrabajo(std::string codigo, std::string fechaSalida, std::string especialista, int vecesReensamblado,
                 bool artesanal)
        : Motor(codigo, fechaSalida, especialista, vecesReensamblado), artesanal(artesanal) {}

    // Métodos getters y setters
    bool esArtesanal() const { return artesanal; }
    void setArtesanal(bool artesanal) { this->artesanal = artesanal; }

    // Sobrescribir el método para calcular el costo
    double calcularCosto() const override {
        double costo = 1000 - (100 * vecesReensamblado);
        if (artesanal) {
            costo *= 10;    // Aumenta su costo 10 veces si es artesanal
        }
        return costo;
    }

    // Sobrescribir el método para mostrar información
    void mostrarFichaTecnica() const override;
};

void MotorTrabajo::mostrarFichaTecnica() const {
    Motor::mostrarFichaTecnica();
    std::cout << "Artesanal: " << (artesanal ? "Sí" : "No") << std::endl;
    std::cout << "Costo: " << calcularCosto() << std::endl;
}

// Clases de carros

class Carro {
protected:
    Motor* motor;                  // Motor incorporado
    int cantidadPlazas;            // Cantidad de plazas
    double velocidad;              // Velocidad del vehículo en km/h
    std::string fechaSalida;       // Fecha de salida de la planta

public:
    // Constructor
    Carro(Motor* motor, int cantidadPlazas, double velocidad, std::string fechaSalida)
        : motor(motor), cantidadPlazas(cantidadPlazas), velocidad(velocidad), fechaSalida(fechaSalida) {}

    // Métodos getters y setters
    Motor* getMotor() const { return motor; }
    void setMotor(Motor* motor) { this->motor = motor; }

    int getCantidadPlazas() const { return cantidadPlazas; }
    void setCantidadPlazas(int plazas) { cantidadPlazas = plazas; }

    double getVelocidad() const { return velocidad; }
    void setVelocidad(double velocidad) { this->velocidad = velocidad; }

    std::string getFechaSalida() const { return fechaSalida; }
    void setFechaSalida(const std::string& fecha) { fechaSalida = fecha; }

    // Método virtual para calcular el precio de venta
    virtual double calcularPrecioVenta() const = 0;

    // Método virtual para mostrar la ficha técnica
    virtual void mostrarFichaTecnica() const;
};

void Carro::mostrarFichaTecnica() const {
    std::cout << "Fecha de salida: " << fechaSalida << std::endl;
    std::cout << "Cantidad de plazas: " << cantidadPlazas << std::endl;
    std::cout << "Velocidad: " << velocidad << " km/h" << std::endl;
    std::cout << "--- Ficha técnica del motor ---" << std::endl;
    motor->mostrarFichaTecnica();
}

class Formula1 : public Carro {
private:
    double pesoCarroceria;    // Peso de la carrocería

public:
    // Constructor
    Formula1(MotorAlta* motor, double velocidad, std::string fechaSalida, double pesoCarroceria)
        : Carro(motor, 1, velocidad, fechaSalida), pesoCarroceria(pesoCarroceria) {}

    // Métodos getters y setters
    double getPesoCarroceria() const { return pesoCarroceria; }
    void setPesoCarroceria(double peso) { pesoCarroceria = peso; }

    // Sobrescribir el método para calcular el precio de venta
    double calcularPrecioVenta() const override {
        return velocidad * 5 + 1 / pesoCarroceria + motor->calcularCosto();
    }

    // Sobrescribir el método para mostrar la ficha técnica
    void mostrarFichaTecnica() const override;
};

void Formula1::mostrarFichaTecnica() const {
    std::cout << "--- Ficha técnica del Formula1 ---" << std::endl;
    Carro::mostrarFichaTecnica();
    std::cout << "Peso de la carrocería: " << pesoCarroceria << " kg" << std::endl;
    std::cout << "Precio de venta: " << calcularPrecioVenta() << std::endl;
}

class Omnibus : public Carro {
private:
    int cantidadPuertas;    // Cantidad de puertas

public:
    // Constructor
    Omnibus(MotorFuerza* motor, double velocidad, std::string fechaSalida, int cantidadPuertas)
        : Carro(motor, 0, velocidad, fechaSalida), cantidadPuertas(cantidadPuertas) {
        calcularCapacidad();
    }

    // Métodos getters y setters
    int getCantidadPuertas() const { return cantidadPuertas; }
    void setCantidadPuertas(int puertas) { cantidadPuertas = puertas; }

    // Método para calcular la capacidad en función de los caballos de fuerza del motor
    void calcularCapacidad() {
        MotorFuerza* motorFuerza = dynamic_cast<MotorFuerza*>(motor);
        if (motorFuerza) {
            int caballos = motorFuerza->getCaballosFuerza();
            cantidadPlazas = caballos / 10;    // Por cada 10 caballos de fuerza, 1 persona
        }
    }

    // Sobrescribir el método para calcular el precio de venta
    double calcularPrecioVenta() const override {
        return (cantidadPuertas * 1.5 + motor->calcularCosto()) * 3;
    }

    // Sobrescribir el método para mostrar la ficha técnica
    void mostrarFichaTecnica() const override;
};

void Omnibus::mostrarFichaTecnica() const {
    std::cout << "--- Ficha técnica del Ómnibus ---" << std::endl;
    Carro::mostrarFichaTecnica();
    std::cout << "Cantidad de puertas: " << cantidadPuertas << std::endl;
    std::cout << "Precio de venta: " << calcularPrecioVenta() << std::endl;
}

class Sport : public Carro {
private:
    int cantidadVelocidades;    // Cantidad de velocidades de la caja
    bool cambioUniversal;       // Indicador de si es de cambio universal

public:
    // Constructor
    Sport(MotorTrabajo* motor, int cantidadPlazas, double velocidad, std::string fechaSalida,
          int cantidadVelocidades, bool cambioUniversal)
        : Carro(motor, cantidadPlazas, velocidad, fechaSalida),
          cantidadVelocidades(cantidadVelocidades), cambioUniversal(cambioUniversal) {}

    // Métodos getters y setters
    int getCantidadVelocidades() const { return cantidadVelocidades; }
    void setCantidadVelocidades(int velocidades) { cantidadVelocidades = velocidades; }

    bool esCambioUniversal() const { return cambioUniversal; }
    void setCambioUniversal(bool cambio) { cambioUniversal = cambio; }

    // Sobrescribir el método para calcular el precio de venta
    double calcularPrecioVenta() const override {
        double precio = cantidadVelocidades * 2 + motor->calcularCosto();
        if (cambioUniversal) {
            precio += 1000;
        }
        return precio;
    }

    // Sobrescribir el método para mostrar la ficha técnica
    void mostrarFichaTecnica() const override;
};

void Sport::mostrarFichaTecnica() const {
    std::cout << "--- Ficha técnica del Sport ---" << std::endl;
    Carro::mostrarFichaTecnica();
    std::cout << "Cantidad de velocidades: " << cantidadVelocidades << std::endl;
    std::cout << "Cambio universal: " << (cambioUniversal ? "Sí" : "No") << std::endl;
    std::cout << "Precio de venta: " << calcularPrecioVenta() << std::endl;
}

class DeLujo : public Carro {
private:
    double costoTapiceria;    // Costo de la tapicería

public:
    // Constructor
    DeLujo(MotorTrabajo* motor, int cantidadPlazas, double velocidad, std::string fechaSalida,
           double costoTapiceria)
        : Carro(motor, cantidadPlazas, velocidad, fechaSalida), costoTapiceria(costoTapiceria) {}

    // Métodos getters y setters
    double getCostoTapiceria() const { return costoTapiceria; }
    void setCostoTapiceria(double costo) { costoTapiceria = costo; }

    // Sobrescribir el método para calcular el precio de venta
    double calcularPrecioVenta() const override {
        return (costoTapiceria + motor->calcularCosto()) * 10;
    }

    // Sobrescribir el método para mostrar la ficha técnica
    void mostrarFichaTecnica() const override;
};

void DeLujo::mostrarFichaTecnica() const {
    std::cout << "--- Ficha técnica del Carro de Lujo ---" << std::endl;
    Carro::mostrarFichaTecnica();
    std::cout << "Costo de la tapicería: " << costoTapiceria << std::endl;
    std::cout << "Precio de venta: " << calcularPrecioVenta() << std::endl;
}

// Variables y contenedores globales

// Plan de producción anual
int planMotoresAnual = 1000;
int planCarrosAnual = 500;

// Contadores de producción
int motoresProducidos = 0;
int carrosProducidos = 0;

// Inventarios
std::vector<MotorAlta*> motoresAltaDisponibles;
std::vector<MotorFuerza*> motoresFuerzaDisponibles;
std::vector<MotorTrabajo*> motoresTrabajoDisponibles;

std::vector<Carro*> carrosEnsamblados;

// Funciones de gestión e interacción

void agregarMotor();
void ensamblarCarro();
void mostrarMotoresDisponibles();
void mostrarCarrosAltaVelocidad();
void mostrarOmnibusMayorCapacidad();
void mostrarFichasTecnicasCarros();
void darDeBajaCarro();
void mostrarCarrosConMotoresReensamblados();
void mostrarCumplimientoPlan();
void mostrarGananciaTotal();
void menuPrincipal();

int main() {
    menuPrincipal();
    return 0;
}

void agregarMotor() {
    int tipoMotor;
    std::cout << "Seleccione el tipo de motor a agregar:" << std::endl;
    std::cout << "1. Motor de Alta" << std::endl;
    std::cout << "2. Motor de Fuerza" << std::endl;
    std::cout << "3. Motor de Trabajo" << std::endl;
    std::cin >> tipoMotor;

    std::string codigo, fechaSalida, especialista;
    int vecesReensamblado;

    std::cout << "Ingrese el código (12 caracteres): ";
    std::cin >> codigo;
    std::cout << "Ingrese la fecha de salida (DD/MM/AAAA): ";
    std::cin >> fechaSalida;
    std::cout << "Ingrese el nombre del especialista: ";
    std::cin >> especialista;
    std::cout << "Ingrese las veces que ha regresado al área de ensamblaje por defectos: ";
    std::cin >> vecesReensamblado;

    switch (tipoMotor) {
        case 1: {   // Motor de Alta
            double maxRPM, consumo;
            std::cout << "Ingrese las máximas RPM: ";
            std::cin >> maxRPM;
            std::cout << "Ingrese el consumo (km/l): ";
            std::cin >> consumo;

            MotorAlta* motorAlta = new MotorAlta(codigo, fechaSalida, especialista, vecesReensamblado, maxRPM, consumo);
            motoresAltaDisponibles.push_back(motorAlta);
            motoresProducidos++;
            std::cout << "Motor de Alta agregado exitosamente." << std::endl;
            break;
        }
        case 2: {   // Motor de Fuerza
            int caballosFuerza;
            std::cout << "Ingrese los caballos de fuerza (80 - 4000): ";
            std::cin >> caballosFuerza;

            if (caballosFuerza < 80 || caballosFuerza > 4000) {
                std::cout << "Caballos de fuerza fuera del rango permitido." << std::endl;
                return;
            }

            MotorFuerza* motorFuerza = new MotorFuerza(codigo, fechaSalida, especialista, vecesReensamblado, caballosFuerza);
            motoresFuerzaDisponibles.push_back(motorFuerza);
            motoresProducidos++;
            std::cout << "Motor de Fuerza agregado exitosamente." << std::endl;
            break;
        }
        case 3: {   // Motor de Trabajo
            bool artesanal;
            std::cout << "¿Es artesanal? (1 = Sí, 0 = No): ";
            std::cin >> artesanal;

            MotorTrabajo* motorTrabajo = new MotorTrabajo(codigo, fechaSalida, especialista, vecesReensamblado, artesanal);
            motoresTrabajoDisponibles.push_back(motorTrabajo);
            motoresProducidos++;
            std::cout << "Motor de Trabajo agregado exitosamente." << std::endl;
            break;
        }
        default:
            std::cout << "Tipo de motor inválido." << std::endl;
            break;
    }
}

void ensamblarCarro() {
    int tipoCarro;
    std::cout << "Seleccione el tipo de carro a ensamblar:" << std::endl;
    std::cout << "1. Formula1" << std::endl;
    std::cout << "2. Ómnibus" << std::endl;
    std::cout << "3. Sport" << std::endl;
    std::cout << "4. De Lujo" << std::endl;
    std::cin >> tipoCarro;

    // Variables comunes
    std::string fechaSalida;
    double velocidad;

    std::cout << "Ingrese la fecha de salida (DD/MM/AAAA): ";
    std::cin >> fechaSalida;
    std::cout << "Ingrese la velocidad del vehículo (km/h): ";
    std::cin >> velocidad;

    switch (tipoCarro) {
        case 1: {   // Formula1
            if (motoresAltaDisponibles.empty()) {
                std::cout << "No hay motores de alta disponibles." << std::endl;
                return;
            }
            MotorAlta* motor = motoresAltaDisponibles.back();
            motoresAltaDisponibles.pop_back();

            double pesoCarroceria;
            std::cout << "Ingrese el peso de la carrocería (kg): ";
            std::cin >> pesoCarroceria;

            Formula1* formula1 = new Formula1(motor, velocidad, fechaSalida, pesoCarroceria);
            carrosEnsamblados.push_back(formula1);
            carrosProducidos++;
            std::cout << "Formula1 ensamblado exitosamente." << std::endl;
            break;
        }
        case 2: {   // Ómnibus
            if (motoresFuerzaDisponibles.empty()) {
                std::cout << "No hay motores de fuerza disponibles." << std::endl;
                return;
            }
            MotorFuerza* motor = motoresFuerzaDisponibles.back();
            motoresFuerzaDisponibles.pop_back();

            int cantidadPuertas;
            std::cout << "Ingrese la cantidad de puertas: ";
            std::cin >> cantidadPuertas;

            Omnibus* omnibus = new Omnibus(motor, velocidad, fechaSalida, cantidadPuertas);
            carrosEnsamblados.push_back(omnibus);
            carrosProducidos++;
            std::cout << "Ómnibus ensamblado exitosamente." << std::endl;
            break;
        }
        case 3: {   // Sport
            if (motoresTrabajoDisponibles.empty()) {
                std::cout << "No hay motores de trabajo disponibles." << std::endl;
                return;
            }
            MotorTrabajo* motor = motoresTrabajoDisponibles.back();
            motoresTrabajoDisponibles.pop_back();

            int cantidadPlazas;
            std::cout << "Ingrese la cantidad de plazas (entre 2 y 4): ";
            std::cin >> cantidadPlazas;

            if (cantidadPlazas < 2 || cantidadPlazas > 4) {
                std::cout << "Cantidad de plazas inválida." << std::endl;
                return;
            }

            int cantidadVelocidades;
            std::cout << "Ingrese la cantidad de velocidades de la caja: ";
            std::cin >> cantidadVelocidades;

            bool cambioUniversal;
            std::cout << "¿Es de cambio universal? (1 = Sí, 0 = No): ";
            std::cin >> cambioUniversal;

            Sport* sport = new Sport(motor, cantidadPlazas, velocidad, fechaSalida, cantidadVelocidades, cambioUniversal);
            carrosEnsamblados.push_back(sport);
            carrosProducidos++;
            std::cout << "Sport ensamblado exitosamente." << std::endl;
            break;
        }
        case 4: {   // De Lujo
            if (motoresTrabajoDisponibles.empty()) {
                std::cout << "No hay motores de trabajo disponibles." << std::endl;
                return;
            }

            // Buscar un motor artesanal
            MotorTrabajo* motor = nullptr;
            for (auto it = motoresTrabajoDisponibles.begin(); it != motoresTrabajoDisponibles.end(); ++it) {
                if ((*it)->esArtesanal()) {
                    motor = *it;
                    motoresTrabajoDisponibles.erase(it);
                    break;
                }
            }

            if (!motor) {
                std::cout << "No hay motores artesanales disponibles." << std::endl;
                return;
            }

            int cantidadPlazas;
            std::cout << "Ingrese la cantidad de plazas (entre 2 y 4): ";
            std::cin >> cantidadPlazas;

            if (cantidadPlazas < 2 || cantidadPlazas > 4) {
                std::cout << "Cantidad de plazas inválida." << std::endl;
                return;
            }

            double costoTapiceria;
            std::cout << "Ingrese el costo de la tapicería: ";
            std::cin >> costoTapiceria;

            DeLujo* deLujo = new DeLujo(motor, cantidadPlazas, velocidad, fechaSalida, costoTapiceria);
            carrosEnsamblados.push_back(deLujo);
            carrosProducidos++;
            std::cout << "Carro de lujo ensamblado exitosamente." << std::endl;
            break;
        }
        default:
            std::cout << "Tipo de carro inválido." << std::endl;
            break;
    }
}

void mostrarMotoresDisponibles() {
    std::cout << "Motores de Alta disponibles: " << motoresAltaDisponibles.size() << std::endl;
    for (const auto& motor : motoresAltaDisponibles) {
        motor->mostrarFichaTecnica();
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "Motores de Fuerza disponibles: " << motoresFuerzaDisponibles.size() << std::endl;
    for (const auto& motor : motoresFuerzaDisponibles) {
        motor->mostrarFichaTecnica();
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "Motores de Trabajo disponibles: " << motoresTrabajoDisponibles.size() << std::endl;
    for (const auto& motor : motoresTrabajoDisponibles) {
        motor->mostrarFichaTecnica();
        std::cout << "---------------------------" << std::endl;
    }
}

void mostrarCarrosAltaVelocidad() {
    std::cout << "Carros con velocidad mayor a 150 km/h:" << std::endl;
    for (const auto& carro : carrosEnsamblados) {
        if (carro->getVelocidad() > 150) {
            carro->mostrarFichaTecnica();
            std::cout << "---------------------------" << std::endl;
        }
    }
}

void mostrarOmnibusMayorCapacidad() {
    Omnibus* omnibusMayor = nullptr;
    int mayorCapacidad = 0;

    for (const auto& carro : carrosEnsamblados) {
        Omnibus* omnibus = dynamic_cast<Omnibus*>(carro);
        if (omnibus) {
            int capacidad = omnibus->getCantidadPlazas();
            if (capacidad > mayorCapacidad) {
                mayorCapacidad = capacidad;
                omnibusMayor = omnibus;
            }
        }
    }

    if (omnibusMayor) {
        std::cout << "Ómnibus de mayor capacidad:" << std::endl;
        omnibusMayor->mostrarFichaTecnica();
    } else {
        std::cout << "No hay ómnibus en el inventario." << std::endl;
    }
}

void mostrarFichasTecnicasCarros() {
    for (const auto& carro : carrosEnsamblados) {
        carro->mostrarFichaTecnica();
        std::cout << "---------------------------" << std::endl;
    }
}

void darDeBajaCarro() {
    std::string codigoCarro;
    std::cout << "Ingrese el código del motor del carro a dar de baja: ";
    std::cin >> codigoCarro;

    for (auto it = carrosEnsamblados.begin(); it != carrosEnsamblados.end(); ++it) {
        if ((*it)->getMotor()->getCodigo() == codigoCarro) {
            // El carro no pasó la prueba, se desarma y el motor vuelve al inventario
            Motor* motor = (*it)->getMotor();
            motor->setVecesReensamblado(motor->getVecesReensamblado() + 1);

            // Si el carro era de lujo, el motor deja de ser artesanal
            DeLujo* deLujo = dynamic_cast<DeLujo*>(*it);
            if (deLujo) {
                MotorTrabajo* motorTrabajo = dynamic_cast<MotorTrabajo*>(motor);
                if (motorTrabajo) {
                    motorTrabajo->setArtesanal(false);
                }
            }

            // Devolver el motor al inventario correspondiente
            if (MotorAlta* motorAlta = dynamic_cast<MotorAlta*>(motor)) {
                motoresAltaDisponibles.push_back(motorAlta);
            } else if (MotorFuerza* motorFuerza = dynamic_cast<MotorFuerza*>(motor)) {
                motoresFuerzaDisponibles.push_back(motorFuerza);
            } else if (MotorTrabajo* motorTrabajo = dynamic_cast<MotorTrabajo*>(motor)) {
                motoresTrabajoDisponibles.push_back(motorTrabajo);
            }

            // Eliminar el carro del inventario
            delete *it;
            carrosEnsamblados.erase(it);
            std::cout << "Carro dado de baja y motor devuelto al inventario." << std::endl;
            return;
        }
    }
    std::cout << "No se encontró un carro con el código de motor proporcionado." << std::endl;
}

void mostrarCarrosConMotoresReensamblados() {
    std::cout << "Carros con motores reensamblados y disminución en el precio de venta:" << std::endl;
    for (const auto& carro : carrosEnsamblados) {
        if (carro->getMotor()->getVecesReensamblado() > 0) {
            // Aplica solo a Formula1, Sport y Ómnibus
            if (dynamic_cast<Formula1*>(carro) || dynamic_cast<Sport*>(carro) || dynamic_cast<Omnibus*>(carro)) {
                double precioOriginal = carro->calcularPrecioVenta();
                carro->getMotor()->setVecesReensamblado(carro->getMotor()->getVecesReensamblado() - 1);
                double precioAnterior = carro->calcularPrecioVenta();
                carro->getMotor()->setVecesReensamblado(carro->getMotor()->getVecesReensamblado() + 1);
                double disminucion = precioAnterior - precioOriginal;

                carro->mostrarFichaTecnica();
                std::cout << "Disminución en el precio de venta: " << disminucion << std::endl;
                std::cout << "---------------------------" << std::endl;
            }
        }
    }
}

void mostrarCumplimientoPlan() {
    double porcentajeMotores = (static_cast<double>(motoresProducidos) / planMotoresAnual) * 100;
    double porcentajeCarros = (static_cast<double>(carrosProducidos) / planCarrosAnual) * 100;

    std::cout << "Porcentaje de cumplimiento del plan de motores: " << porcentajeMotores << "%" << std::endl;
    std::cout << "Porcentaje de cumplimiento del plan de carros: " << porcentajeCarros << "%" << std::endl;
}

void mostrarGananciaTotal() {
    double gananciaFormula1 = 0;
    double gananciaOmnibus = 0;
    double gananciaSport = 0;
    double gananciaDeLujo = 0;

    for (const auto& carro : carrosEnsamblados) {
        double precioVenta = carro->calcularPrecioVenta();
        double costoMotor = carro->getMotor()->calcularCosto();

        if (Formula1* f1 = dynamic_cast<Formula1*>(carro)) {
            gananciaFormula1 += precioVenta - costoMotor;
        } else if (Omnibus* bus = dynamic_cast<Omnibus*>(carro)) {
            gananciaOmnibus += precioVenta - costoMotor;
        } else if (Sport* sport = dynamic_cast<Sport*>(carro)) {
            gananciaSport += precioVenta - costoMotor;
        } else if (DeLujo* lujo = dynamic_cast<DeLujo*>(carro)) {
            gananciaDeLujo += precioVenta - costoMotor;
        }
    }

    std::cout << "Ganancia total por tipo de carro:" << std::endl;
    std::cout << "Formula1: " << gananciaFormula1 << std::endl;
    std::cout << "Ómnibus: " << gananciaOmnibus << std::endl;
    std::cout << "Sport: " << gananciaSport << std::endl;
    std::cout << "De Lujo: " << gananciaDeLujo << std::endl;
}

void menuPrincipal() {
    int opcion = 0;
    do {
        std::cout << "\n----- Menú Principal -----" << std::endl;
        std::cout << "1. Agregar motor" << std::endl;
        std::cout << "2. Ensamblar carro" << std::endl;
        std::cout << "3. Mostrar motores disponibles" << std::endl;
        std::cout << "4. Mostrar carros de mayor velocidad" << std::endl;
        std::cout << "5. Mostrar ómnibus de mayor capacidad" << std::endl;
        std::cout << "6. Mostrar fichas técnicas de todos los carros" << std::endl;
        std::cout << "7. Dar de baja un carro que no pase la prueba" << std::endl;
        std::cout << "8. Mostrar carros con motores reensamblados" << std::endl;
        std::cout << "9. Mostrar porcentaje de cumplimiento del plan" << std::endl;
        std::cout << "10. Mostrar ganancia total" << std::endl;
        std::cout << "11. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarMotor();
                break;
            case 2:
                ensamblarCarro();
                break;
            case 3:
                mostrarMotoresDisponibles();
                break;
            case 4:
                mostrarCarrosAltaVelocidad();
                break;
            case 5:
                mostrarOmnibusMayorCapacidad();
                break;
            case 6:
                mostrarFichasTecnicasCarros();
                break;
            case 7:
                darDeBajaCarro();
                break;
            case 8:
                mostrarCarrosConMotoresReensamblados();
                break;
            case 9:
                mostrarCumplimientoPlan();
                break;
            case 10:
                mostrarGananciaTotal();
                break;
            case 11:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 11);

    // Liberar memoria antes de salir
    for (auto motor : motoresAltaDisponibles) {
        delete motor;
    }
    for (auto motor : motoresFuerzaDisponibles) {
        delete motor;
    }
    for (auto motor : motoresTrabajoDisponibles) {
        delete motor;
    }
    for (auto carro : carrosEnsamblados) {
        delete carro;
    }
}

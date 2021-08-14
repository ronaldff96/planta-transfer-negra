// Declaración de funciones

	//asumiendo que el puerto 8 es el que envia la señal de encendido a la planta
void encenderPlanta(){
	//Envia la señal de encendido a la planta
	digitalWrite(8, HIGH); //Se enciende la planta
	//si quieres que al encender la planta se hagan mas cosas ponlas aqui
}

void apagarPlanta(){
	//Envia la señal de apagado a la planta
	digitalWrite(8, LOW); //Se apaga la planta
	//si quieres que al aoagar la planta se hagan mas cosas ponlas aqui
}

// Declaracion de variables auxiliares
int intentosFallidos = 0 // cuenta los intentos fallidos, inicialmente 0

// Pseudo código del loop 

	// Leemos las entradas
int modoAuto = digitalread(X) // X representa el puerto en el que esta la señal de Modo. 1 == Auto, 0 == Manual
int controlManual = digitalread(Y) // Y representa el puerto en el que esta la señal de Control Manual. 1 == Encender planta, 0 == Apagar planta
int reset = digitalread(Z) // Z representa el puerto en el que esta la señal de Reset. 1 == Resetear contador de fallas, 0 == No hacer nada
int estadoPlanta = digitalread(A) // A representa el puerto en el que esta la señal del estado de la planta. 1 == la planta está encendida, 0 == La planta está apagada
int red = digitalread(B) // B representa el puerto en el que esta la señal de la red eléctrica. 1 == Hay electricidad, 0 == Mardito maduro

	// Empieza lo bueno
	// Primero revisamos si se ha enviado la señal de reset
	if (reset == 1) {
		intentosFallidos = 0 // si se envió la señal de reseteo, entonces reseteo el contador de intentos fallidos
	}
	// Luego reviso si hay demasiadas fallas
	if (intentos intentosFallidos > 5) {
		// Ejecuta aquí lo que quieras que pase cuando hay muchas fallas
	} else {
		// Revisamos en que modo está el transfer y tomamos decisiones en base a eso.
		if (modoAuto == 1) {
			// Si está en modo automático, comprobar la señal de la red eléctrica
			if (red == 1) {
				apagarPlanta() // Si hay señal en la red eléctrica, apagar la planta
			} else {
				encenderPlanta() // Si no hay señal en la red eléctrica, encender la planta
			}
		} else { // Si está en modo Manual, comprobar la señal del switch de control manual
			if (controlManual == 1) {
				encenderPlanta() // Si el control Manual está en On, encender la planta
			} else {
				apagarPlanta () // Si el control Manual está en Off, apagar la planta
			}
		}

		// Para comprobar que la planta encendió correctamente:
		delay(700) //Esperamos 0.7 segundos mientras se ejecuta el codigo de la planta
		if (estadoPlanta == 0) {
			// La planta no encendió correctamente, por lo tanto, ocurrió un intento fallido
			intentosFallidos += 1 // Aumento el contador de intentos fallidos
			apagarPlanta() // Dejo de enviar la señal de encendido de la planta 
			delay(700)	// Esperamos a que se ejecute el codigo de la planta	
		}  else {
			intentosFallidos = 0 // Si encendió correctamente, se resetea el contador de intentos fallidos
		}
	}

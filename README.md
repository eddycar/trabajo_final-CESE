# Sistema IoT para el monitoreo remoto de variables ambientales

## Director: Ing. Juan Manuel Cruz (UBA)
## Autor: Ing Edilberto Carvajal

El sistema propuesto consta de un sistema de monitoreo de variables ambientales basado en un nodo final IoT con el microcontrolador **STM32WL55** y el sensor **BME280**.


## Arquitectura del Sistema  
1. **Nodo final**: Captura datos de temperatura, humedad y presión con el BME280 y los transmite inalámbricamente mediante **LoRaWAN**.  
2. **Gateway**: Recibe los datos del nodo final y los reenvía a **The Things Stack**, que actúa como servidor de red LoRaWAN.  
3. **Servidor de red**: The Things Stack gestiona la comunicación y envía los datos a una **base de datos**.  
4. **Dashboard**: Una aplicación de usuario consulta la base de datos y muestra la información en tiempo real y con histórico.  

## Información del Repositorio

El repositorio contiene los siguientes proyectos que sirvieron como pruebas de desarrollo del firmware del nodo final:


- **I2C_BME280**: Implementa el driver del sensor BME280 y el código necesario para la adquisición de datos mediante I2C en modo *polling*.  
- **I2C_BME280_ComIT**: Implementa el driver del sensor BME280 y el código para la adquisición de datos mediante I2C utilizando interrupciones.  
- **I2C_BME280_ComDMA**: Implementa el driver del sensor BME280 y el código para la adquisición de datos mediante I2C con transferencia DMA.  
- **LPtimer_operation_test**: Configura el RTC como fuente de temporización para operar el microcontrolador en modo de bajo consumo.  
- **LPtimer_BME280_test**: Adquiere datos periódicamente del sensor BME280 utilizando el RTC como temporizador.  
- **End_Node**: Implementa la comunicación del microcontrolador con el gateway y la transmisión periódica de datos.  
- **LoRaWAN_End_Node_FreeRTOS**: Integra **FreeRTOS** para gestionar las tareas de adquisición de datos, manejo de eventos del protocolo **LoRaWAN**, enlace y transmisión de datos.  


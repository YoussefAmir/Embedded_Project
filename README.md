# Embedded_Project

This is an embedded project for Embedded systems course in AUC with Dr. Shalaan. The code is to read ECG signals using STM microcontroller, Heart Beat monitor, and ECG electrods. The project utilizes a simple GUI made by python to start the connection and plot the ECG signals.

------**Src Folder - Embedded C Code**------
Contains:

  main.c: 
    contains the main while(1) to transmit the read code over UART
  stm32f1xx_it.c:
    contains the Handlers for UART, ADC, Systick timer
    
------**Python GUI Folde - Python Coder**------
Contains:

  test.py
    contains the python GUI with the pyserial communication using UART
    Communication must be validated before starting using "Check connection button"

---------------------------------------------

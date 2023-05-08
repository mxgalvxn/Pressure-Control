import numpy as np
import control
from scipy import signal
import matplotlib.pyplot as plt
Kp = .0002
Ti = -.0002
Td = 0
###############
#opcion 1
numerador = np.array([5.861*(Kp * Ti * Td), 5.861*(Ti * Kp) + 1.631*(Kp
* Ti * Td), 1.631*(Ti * Kp) + 5.861*Kp ,1.631*(Kp)])
denominador = np.array([5.861*( Kp*Ti*Td) , (5.861*Kp*Ti)+
1.631*(Kp*Ti*Td) + 1.673*Ti, 1.631*(Kp*Ti) + 1.631*Ti + 5.861*Kp
,1.631*(Kp)])
#T = control.tf(numerador, denominador)
#opcion 2
s = control.TransferFunction.s
T = (Kp * Ti*s + Kp)/(Ti * s**2 + (Kp*Ti-Ti)*s + Kp)
# print( 'T(s)=', T)
###########
#Respuesta del sistema en lazo cerrado
#Entrada de referencia escalon unitario
lti = signal.lti( numerador, denominador)
t,y = signal.step(lti)
print(y)
#graficacion de la respuesta del sistema
plt.plot( t,y)
plt.title("Respuesta al escalon")
plt.xlabel("Tiempo ")
plt.ylabel("x(t)")
plt.grid()
plt.show()

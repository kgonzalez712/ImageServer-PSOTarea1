from PIL import Image,ImageFilter,ImageOps,ImageEnhance 
import os
import cv2
import base64
import struct
import scipy
import scipy.misc
import scipy.cluster
import numpy as np


    

#---------------------Covierte de base64 a imagen--------------------------------
def getImagen():
    #Leer txt en base64
    f = open ('Content.txt','r')
    #Quito el encabezado data:image/formatodeimagen;base64,
    for x in f:
        f = open ('Content.txt','w')
        jpeg = x.replace("data:image/jpeg;base64,","")
        jpg = jpeg.replace("data:image/jpg;base64,","")
        png = jpg.replace("data:image/png;base64,","")
        f.write(png)
        f.close()    
    f = open ('Content.txt','r')
    mensaje = f.read()
    f.close()
    #Convierto y guardo
    imgdata = base64.b64decode(mensaje)
    filename = 'Imagen_entrada.jpg'
    with open(filename, 'wb') as f:
        f.write(imgdata)


#----------------------Clasificar imágen-------------------------------------------

def clasificarImagen():
    imagen = cv2.imread('Imagen_entrada.jpg')
    hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
    colors, count = np.unique(hsv.reshape(-1, hsv.shape[-1]), axis=0, return_counts=True)
    #Lista de los bits más repetidos
    bit_mas_repetido = colors[np.argsort(-count)][:3]
    print(bit_mas_repetido)
    #Promedio de los bits más repetidos
    R_prom=(int(bit_mas_repetido[0][0])+ int(bit_mas_repetido[1][0]) + int(bit_mas_repetido[2][0]))/3
    V_prom=(int(bit_mas_repetido[0][1])+ int(bit_mas_repetido[1][1]) + int(bit_mas_repetido[2][1]))/3
    A_prom=(int(bit_mas_repetido[0][2])+ int(bit_mas_repetido[1][2]) + int(bit_mas_repetido[2][2]))/3
    print(R_prom)
    print(V_prom)
    print(A_prom)
    #Logica de selección de dirección
    if R_prom > V_prom:
        if R_prom > A_prom:
            image= cv2.imread("Imagen_entrada.jpg")
            path = "test/rojas"
            cv2.imwrite(os.path.join(path, "Imagen_clasificada.jpg"), image)
        else:
            image= cv2.imread("Imagen_entrada.jpg")
            path = "test/azules"
            cv2.imwrite(os.path.join(path, "Imagen_clasificada.jpg"), image)
    else:
        if V_prom > R_prom:
            if V_prom > A_prom:
                image= cv2.imread("Imagen_entrada.jpg")
                path = "test/verdes"
                cv2.imwrite(os.path.join(path, "Imagen_clasificada.jpg"), image)
            else:
                image= cv2.imread("Imagen_entrada.jpg")
                path = "test/azules"
                cv2.imwrite(os.path.join(path, "Imagen_clasificada.jpg"), image)
        else:
            image= cv2.imread("Imagen_entrada.jpg")
            path = "test/rojas"
            cv2.imwrite(os.path.join(path, "Imagen_clasificada.jpg"), image)



getImagen()
clasificarImagen()

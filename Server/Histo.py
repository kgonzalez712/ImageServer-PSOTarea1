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


#------------------Proceso imágen, mejora contraste--------------------------------
def procesarImagen():
    #Leer Imagen
    im = Image.open('Imagen_entrada.jpg') 
    
    enh = ImageEnhance.Contrast(im)  
    img = enh.enhance(1.8)
    img2 = img.show("30% more contrast")
    img.save("Imagen_procesada.jpg")


getImagen()
procesarImagen()


    




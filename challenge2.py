def lineSegment(x1, y1, x2, y2):
    lista = []
    pointt = []
    dx = x2 - x1
    dy = y2 - y1
    if dx == 0:
        m = 0
    else:
        m = dy / dx
    b = y1 - m*x1
    x = dx / 15
    y = dy / 15
    x0 = x1
    y0 = y1

    x_Ans = int(x0)
    y_Ans = int(y0)
    pointt.append(int(x0))
    pointt.append(int(y0))
    lista.append(pointt)
    pointt = []
    for i in range(15):
        x0 += x
        y0 += y
        if int(x0) != x_Ans or int(y0) != y_Ans:
            x_Ans = int(x0)
            y_Ans = int(y0)
            pointt.append(int(x0))
            pointt.append(int(y0))
            lista.append(pointt)
            pointt = []
    return lista
   

lista = lineSegment(1, 2, 100, 20)
lista2 = lineSegment(10, 200, 50, 10)
lista3 = lineSegment(300, 300, 10, 10)
lista4 = lineSegment(200, 300, 250, 50)
lista5 = lineSegment(350, 350, 100, 300)

#Drawing
size(400, 400);

def dibujar():
    background(255)
    stroke(0)
    strokeWeight(2)
    for i in range(len(lista)):
        point(lista[i][0], lista[i][1])
    for i in range(len(lista2)):
        point(lista2[i][0], lista2[i][1])
    for i in range(len(lista3)):
        point(lista3[i][0], lista3[i][1])
    for i in range(len(lista4)):
        point(lista4[i][0], lista4[i][1])
    for i in range(len(lista5)):
        point(lista5[i][0], lista5[i][1])

dibujar()
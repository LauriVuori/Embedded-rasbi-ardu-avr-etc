

def drawFromArray():
    sleepTime = 0.5
    test = [  
    "11111111",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"]
    for row in range(len(test)):
        for col in range(len(test[row])):
            if  (test[row][col] == 1):
                with canvas(device) as draw:
                    draw.point((1, 0), fill=color)
    
    time.sleep(sleepTime)

b = 0b11

for i in range(5):
    drawFromArray()
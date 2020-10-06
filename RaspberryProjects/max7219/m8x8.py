

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

    if  (test[0][0] == '1'):
        with canvas(device) as draw:
            draw.point((0, 0), fill=color)
    if (test[0][1] == '1'):
        with canvas(device) as draw:
            draw.point((0, 1), fill=color)
    if (test[0][2] == '1'):
        with canvas(device) as draw:
            draw.point((0, 2), fill=color)
    if (test[0][3] == '1'):
        with canvas(device) as draw:
            draw.point((0, 3), fill=color)
    if (test[0][4] == '1'):
        with canvas(device) as draw:
            draw.point((0, 4), fill=color)
    if (test[0][5] == '1'):
        with canvas(device) as draw:
            draw.point((0, 5), fill=color)
    if (test[0][6] == '1'):
        with canvas(device) as draw:
            draw.point((0, 6), fill=color)
    if (test[0][7] == '1'):
        with canvas(device) as draw:
            draw.point((0, 7), fill=color)
    time.sleep(sleepTime)


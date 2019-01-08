from context import Screen, ScreenContext
import atexit
import datetime
import time

ctx = ScreenContext("/dev/ttyUSB0")

# Make sure the cleanup routine is called to clear the screen
# when we close the script
atexit.register(ctx.cleanup)

# Wait 6 seconds for the screen to boot up before we start uploading anything
ctx.sleep(6).reset_lcd().set_rotation(1)
# Main loop
while True:
    ctx.fg_color(Screen.RED).write("").home()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.GREEN).write(" Multi-scale Integrated ").linebreak()
    ctx.fg_color(Screen.GREEN).write(" Sensing and Simulation ").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.BLUE).write ("  http://utdmints.info/  ").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.CYAN).write ("https://github.com/mi3nts").linebreak()
    ctx.fg_color(Screen.GREEN).write("-------------------------").linebreak()
    ctx.fg_color(Screen.WHITE).write("----------MINTS----------").linebreak()
    ctx.fg_color(Screen.GREEN).write("                         ").linebreak()
    ctx.fg_color(Screen.YELLOW).write(str(datetime.datetime.now())).linebreak()
    ctx.fg_color(Screen.WHITE).write("").home()
    time.sleep(5)

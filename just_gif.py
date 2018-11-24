import subprocess, sys, glob
import os, shutil
from PIL import Image
# read pngs to list
sorted_png = []
for infile in sorted(glob.glob('pics/*.png')):
    sorted_png.append(Image.open(infile))   

# and save it as a gif
sorted_png[0].save('gol.gif', save_all=True, append_images=sorted_png[1:850], duration=100, loop=0) 

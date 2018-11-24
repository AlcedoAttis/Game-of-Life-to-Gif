import subprocess, sys, glob
import os, shutil
from PIL import Image

# get command line arguments
size = sys.argv[1] 
time = sys.argv[2]

# offload the work to c++
subprocess.run('./gol_to_array {} {}'.format(size, time), shell=True)

# read pngs to list
sorted_png = []
for infile in sorted(glob.glob('pics/*.png')):
    sorted_png.append(Image.open(infile))   

# and save it as a gif
sorted_png[0].save('gol.gif', save_all=True, append_images=sorted_png[1:], duration=100, loop=0)

# cleanup after yourself
folder = './pics'
for the_file in os.listdir(folder):
    file_path = os.path.join(folder, the_file)
    try:
        if os.path.isfile(file_path):
            os.unlink(file_path)
        #elif os.path.isdir(file_path): shutil.rmtree(file_path)
    except Exception as e:
        print(e)
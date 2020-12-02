from shutil import copyfile

SRC_DIR = '../../gamelogic/VierGewinnt/'
DEST_DIR = './'


def copyCPP(file):
    copyfile(SRC_DIR + file, DEST_DIR + 'src/' + file)


def copyH(file):
    copyfile(SRC_DIR + file, DEST_DIR + 'include/' + file)


copyCPP('VierGewinnt.cpp')
copyCPP('Stein.cpp')
copyH('VierGewinnt.h')
copyH('Stein.h')

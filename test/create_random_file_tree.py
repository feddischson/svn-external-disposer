#!/usr/bin/python

#
# A small script to create a big file-tree with
#
# Usage:
#     python create_random_file_tree.py <tree>
#       
#       <tree> : Target directory, optional (default = '.')
#

from subprocess import call
import uuid
import random
import sys
import os
import errno

N_MIN_DIR =  3
N_MAX_DIR = 8
N_MIN_FILE =  5
N_MAX_FILE = 10
MAX_DEPTH = 7

all_dirs  = []
all_files = []

def get_random_name():
    return str( uuid.uuid4() )

def add_files( folder ):
    for i in range( 1, random.randint( N_MIN_FILE, N_MAX_FILE ) ):
        f = os.path.join( folder, get_random_name() ) 
        all_files.append( f )

def add_tree( base, depth ):

    #create toplevel dir
    for i in range( 1, random.randint( N_MIN_DIR, N_MAX_DIR ) ):
        d = os.path.join( base, get_random_name() ) 
        all_dirs.append( d )
        add_files( d )
        if random.randint( 0, 1 ) and depth < MAX_DEPTH:
            add_tree( d, depth+1 )

base = "."
if( len( sys.argv ) > 1 ):
    base  = os.path.abspath( sys.argv[1] )

all_dirs.append( base )
add_tree( base, 0 )

print( "Creating %d dirs " % len( all_dirs )  )

for d in all_dirs:
    try:
        os.mkdir( d )
    except OSError as exc: 
        if exc.errno == errno.EEXIST and os.path.isdir(d):
            pass
        else:
            raise

print( "Creating %d files " % len( all_files ) )
for f in all_files:
    open( f, 'a' ).close()

